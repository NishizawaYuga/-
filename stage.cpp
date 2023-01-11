#include "stage.h"
#include <cassert>
#include "MatSet.h"
#include "easing.h"

void Stage::Initialize(Model* model, float anyPosY) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//���Z�b�g����Y���W�擾
	//resetPosY = anyPosY;

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model = model;
	//��O���Y����Ɖ����S�ăY���邷��悤�ɂ���ݒ���@
	/* {//�e����̐ݒ�
		block[0].pos.scale_ = { 3,3,3 };
		block[0].pos.translation_ = { -50.0f,0,0 };
		block[0].pos.Initialize();
		//�q����̐ݒ�
		for (int i = 1; i < blockNum; i++) {
			block[i].pos.translation_ = { 2.0f,0,0 };
			//�e�̓o�^
			block[i].pos.parent_ = &block[i - 1].pos;
			block[i].pos.Initialize();
		}
		//���ʂ̐ݒ�
		for (int i = 0; i < blockNum; i++) {
			block[i].cutted = false;
			block[i].isCut = false;
			block[i].timer.nowTime = 0;
			block[i].timer.beginCount = false;
			block[i].timer.slash = 0;
		}
	}*/
	//���݂͂̂��Y����悤�ɂ���ݒ���@
	for (int y = 0; y < blockNum; y++) {	//i,j��{���g�������o�I�ɂ킩��₷�����邽��x,y���g�p
		for (int x = 0; x < blockNum; x++) {
			block[y][x].pos.scale_ = { 2,2,2 };
			block[y][x].pos.translation_ = { x * 4.0f - 50.0f,y * 4.0f - 50.0f,0.0f };
			block[y][x].pos.Initialize();
			block[y][x].cutted = false;
			block[y][x].isCut = false;
			block[y][x].timer.nowTime = 0;
			block[y][x].timer.beginCount = false;
			block[y][x].timer.slash = 0;
		}
		resetPosY[y] = y * 4.0f - 50.0f;
	}

	input_ = Input::GetInstance();
}

void Stage::Update(Vector3 player, bool cutFlag) {
	MatSet2 matSet;
	if (cutFlag) {
		CheckPos(&player);
		//block[slash].translation_.y = -4.5f;
	}
	//R�L�[�������ꂽ�烊�Z�b�g
	/*if (input_->TriggerKey(DIK_R)) {
		for (int i = 0; i < blockNum; i++) {
			block[i].pos.scale_ = { 2,2,2 };
			block[i].pos.translation_ = { i * 4.0f - 50.0f,resetPosY,0.0f };
			block[i].cutted = false;
			block[i].isCut = false;
			block[i].timer.nowTime = 0;
			block[i].timer.beginCount = false;
			block[i].timer.slash = 0;
		}
	}*/

	//�S�Ă̑���̍X�V
	CheckIfCut();
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			block[y][x].pos.matWorld_ = matSet.MatIdentity(block[y][x].pos);
			block[y][x].pos.TransferMatrix();
		}
	}
}

void Stage::Draw(ViewProjection viewProjection) {
	//3D���f����`��
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			if (block[y][x].create) {	//�����t���O�������Ă�����̂����`��(����ȊO�͌����Ȃ������݂͂��Ă���)
				model->Draw(block[y][x].pos, viewProjection);
			}
		}
	}

}

void Stage::CheckPos(Vector3* player) {
	float positionX[32];
	float range = 100000.0f;
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			//�v���C���[�Ƒ���̋������v�Z����
			positionX[x] = block[y][x].pos.translation_.x - player->x;
			//�v���C���[�����ɂ���Ȃ�-1�������Đ��̐��ɖ߂�
			if (positionX[x] < 0) {
				positionX[x] *= -1.0f;
			}
			//�������Z���u���b�N��T��
			if (range > positionX[x]) {
				range = positionX[x];
			}
		}
	}
	//�ł��������Z�������u���b�N�̔ԍ�����������
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			if (range == positionX[x]) {
				//�����I�Ɏ˒��͈͊O��������e��
				if (player->y - 10 < block[y][x].pos.translation_.y && player->y + 10 > block[y][x].pos.translation_.y) {
					//�a��ꂽ�t���O�̃I��(�O2�u���b�N���܂Ƃ߂�)
					for (int j = x - 1; j < x + 1; j++) {
						//-1��blockNum��荂�����l���o�Ă��܂�����e��
						if (j <= blockNum && j >= 0) {
							block[y][j].isCut = true;
							block[y][j].timer.slash = j;
							block[y][j].timer.beginCount = true;
						}
					}
				}
			}
		}
	}
}

void Stage::CheckIfCut() {
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			//�a��ꂽ�t���O��true�����Ɏa���Ă���t���O��false���`�F�b�N
			if (block[y][x].isCut && !block[y][x].cutted) {
				//���炷���Ԃ̃J�E���g���n�܂��Ă���΃J�E���g��i�߂�
				if (block[y][x].timer.beginCount) {
					//�o�ߎ��Ԃ��ړ����ԂɂȂ�܂ŏ����𑱂���
					if (block[y][x].timer.nowTime >= maxTime) {
						//block[block[i].timer.slash].timer.nowTime = 0;
						block[y][block[y][x].timer.slash].cutted = true;
					}
					//�C�[�W���O����
					block[y][x].pos.translation_.y -= EASE::OutQuad(slippingNumbers, 0,
						maxTime, block[y][x].timer.nowTime);
					//�o�ߎ��Ԃ��ړ����Ԃ𒴂��܂ł̊ԉ��Z��������
					if (block[y][x].timer.nowTime < maxTime) {
						block[y][x].timer.nowTime++;
					}
				}


			}
		}
	}
}