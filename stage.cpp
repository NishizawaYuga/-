#include "stage.h"
#include <cassert>
#include "MatSet.h"
#include "easing.h"

void Stage::Initialize(Object3d* model, float anyPosY) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//���Z�b�g����Y���W�擾
	resetPosY = anyPosY;

	//�����Ƃ��Ď󂯎�����f�[�^������o�ϐ��ɋL�^����
	this->model = model;
	//��O���Y����Ɖ���S�ăY���邷��悤�ɂ���ݒ���@
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
	for (int i = 0; i < blockNum; i++) {
		block[i].pos.scale_ = { 2,2,2 };
		block[i].pos.position_ = { i * 4.0f - 50.0f,anyPosY,0.0f };
		block[i].pos.Initialize();
		block[i].cutted = false;
		block[i].isCut = false;
		block[i].timer.nowTime = 0;
		block[i].timer.beginCount = false;
		block[i].timer.slash = 0;
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
	if (input_->TriggerKey(DIK_R)) {
		for (int i = 0; i < blockNum; i++) {
			block[i].pos.scale_ = { 2,2,2 };
			block[i].pos.position_ = { i * 4.0f - 50.0f,resetPosY,0.0f };
			block[i].cutted = false;
			block[i].isCut = false;
			block[i].timer.nowTime = 0;
			block[i].timer.beginCount = false;
			block[i].timer.slash = 0;
		}
	}

	//�S�Ă̑���̍X�V
	CheckIfCut();
	for (int i = 0; i < blockNum; i++) {
		block[i].pos.matWorld_ = matSet.MatIdentity(block[i].pos);
		block[i].pos.UpdateMatrix();// TransferMatrix();
	}
}

void Stage::Draw(ViewProjection viewProjection) {
	//3D���f����`��
	for (int i = 0; i < blockNum; i++) {
		model->Draw(/*block[i].pos, viewProjection*/);
	}

}

void Stage::CheckPos(Vector3* player) {
	float positionX[32];
	float range = 100000.0f;
	for (int i = 0; i < blockNum; i++) {
		//�v���C���[�Ƒ���̋�����v�Z����
		positionX[i] = block[i].pos.position_.x - player->x;
		//�v���C���[�����ɂ���Ȃ�-1������Đ��̐��ɖ߂�
		if (positionX[i] < 0) {
			positionX[i] *= -1.0f;
		}
		//�������Z���u���b�N��T��
		if (range > positionX[i]) {
			range = positionX[i];
		}
	}
	//�ł�������Z�������u���b�N�̔ԍ����������
	for (int i = 0; i < blockNum; i++) {
		if (range == positionX[i]) {
			//�����I�Ɏ˒��͈͊O��������e��
			if (player->y - 10 < block[i].pos.position_.y && player->y + 10 > block[i].pos.position_.y) {
				//�a��ꂽ�t���O�̃I��(�O2�u���b�N��܂Ƃ߂�)
				for (int j = i - 1; j < i + 1; j++) {
					//-1��blockNum��荂�����l���o�Ă��܂�����e��
					if (j <= blockNum && j >= 0) {
						block[j].isCut = true;
						block[j].timer.slash = j;
						block[j].timer.beginCount = true;
					}
				}
			}
		}
	}
}

void Stage::CheckIfCut() {
	for (int i = 0; i < blockNum; i++) {
		//�a��ꂽ�t���O��true�����Ɏa���Ă���t���O��false���`�F�b�N
		if (block[i].isCut && !block[i].cutted) {
			//���炷���Ԃ̃J�E���g���n�܂��Ă���΃J�E���g��i�߂�
			if (block[i].timer.beginCount) {
				//�o�ߎ��Ԃ��ړ����ԂɂȂ�܂ŏ����𑱂���
				if (block[i].timer.nowTime >= maxTime) {
					//block[block[i].timer.slash].timer.nowTime = 0;
					block[block[i].timer.slash].cutted = true;
				}
				//�C�[�W���O����
				block[i].pos.position_.y -= EASE::OutQuad(slippingNumbers, block[i].pos.position_.y,
					maxTime, block[i].timer.nowTime);
				//�o�ߎ��Ԃ��ړ����Ԃ𒴂��܂ł̊ԉ��Z��������
				if (block[i].timer.nowTime < maxTime) {
					block[i].timer.nowTime++;
				}
			}

		}
	}
}