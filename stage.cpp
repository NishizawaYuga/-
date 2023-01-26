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
	for (int i = 0; i < blockNum; i++) {
		model_[i] = model;
	}

	

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
		block_[i].pos.Initialize();
		block_[i].pos.scale_ = { 2,2,2 };
		block_[i].pos.position_ = { i * 4.0f - 50.0f,anyPosY,-50.0f };
		block_[i].pos.UpdateMatrix();
		model_[i]->SetWorldTransform(block_[i].pos);
		model_[i]->Update();
		block_[i].cutted = false;
		block_[i].isCut = false;
		block_[i].timer.nowTime = 0;
		block_[i].timer.beginCount = false;
		block_[i].timer.slash = 0;
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
			block_[i].pos.scale_ = { 2,2,2 };
			block_[i].pos.position_ = { i * 4.0f - 50.0f,resetPosY,0.0f };
			model_[i]->SetWorldTransform(block_[i].pos);
			block_[i].cutted = false;
			block_[i].isCut = false;
			block_[i].timer.nowTime = 0;
			block_[i].timer.beginCount = false;
			block_[i].timer.slash = 0;
		}
	}

	//�S�Ă̑���̍X�V
	CheckIfCut();

	for (int i = 0; i < blockNum; i++) {
		block_[i].pos.matWorld_ = matSet.MatIdentity(block_[i].pos);
		block_[i].pos.UpdateMatrix();// TransferMatrix();
		model_[i]->SetWorldTransform(block_[i].pos);
		model_[i]->Update();
	}
}

void Stage::Draw(/*ViewProjection viewProjection*/) {
	//3D���f����`��
	for (int i = 0; i < blockNum; i++) {
		model_[i]->Draw(block_[i].pos/*, viewProjection*/);
	}
}

void Stage::CheckPos(Vector3* player) {
	float positionX[32];
	float range = 100000.0f;
	for (int i = 0; i < blockNum; i++) {
		//�v���C���[�Ƒ���̋�����v�Z����
		positionX[i] = block_[i].pos.position_.x - player->x;
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
			if (player->y - 10 < block_[i].pos.position_.y && player->y + 10 > block_[i].pos.position_.y) {
				//�a��ꂽ�t���O�̃I��(�O2�u���b�N��܂Ƃ߂�)
				for (int j = i - 1; j < i + 1; j++) {
					//-1��blockNum��荂�����l���o�Ă��܂�����e��
					if (j <= blockNum && j >= 0) {
						block_[j].isCut = true;
						block_[j].timer.slash = j;
						block_[j].timer.beginCount = true;
					}
				}
			}
		}
	}
}

void Stage::CheckIfCut() {
	for (int i = 0; i < blockNum; i++) {
		//�a��ꂽ�t���O��true�����Ɏa���Ă���t���O��false���`�F�b�N
		if (block_[i].isCut && !block_[i].cutted) {
			//���炷���Ԃ̃J�E���g���n�܂��Ă���΃J�E���g��i�߂�
			if (block_[i].timer.beginCount) {
				//�o�ߎ��Ԃ��ړ����ԂɂȂ�܂ŏ����𑱂���
				if (block_[i].timer.nowTime >= maxTime) {
					//block[block[i].timer.slash].timer.nowTime = 0;
					block_[block_[i].timer.slash].cutted = true;
				}
				//�C�[�W���O����
				block_[i].pos.position_.y -= EASE::OutQuad(slippingNumbers, block_[i].pos.position_.y,
					maxTime, block_[i].timer.nowTime);
				//�o�ߎ��Ԃ��ړ����Ԃ𒴂��܂ł̊ԉ��Z��������
				if (block_[i].timer.nowTime < maxTime) {
					block_[i].timer.nowTime++;
				}
			}

		}
	}
}