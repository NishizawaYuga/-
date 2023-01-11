#include "Enemy.h"
#include <cassert>
#include <Function.h>


void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("enemy.png");
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// �G�L�����̈ʒu
	worldtransform_.translation_ = { 55,3,0 };

	//���[���h�ϊ��̏�����
	worldtransform_.Initialize();

}

void Enemy::Update()
{
	
	if (input_->PushKey(DIK_R)) {
		// �G�L�����̈ʒu
		worldtransform_.translation_ = { 55,3,0 };
	}
	//�L�[�{�[�h���͂ɂ��ړ�����
	const float kMoveLimitX = 35;
	const float kMoveLimitMaxY = 3;
	const float kMoveLimitMinY = 10;

	//�͈͂𒴂��Ȃ�����
	worldtransform_.translation_.x = max(worldtransform_.translation_.x, -kMoveLimitX);
	worldtransform_.translation_.x = min(worldtransform_.translation_.x, +kMoveLimitX);
	worldtransform_.translation_.y = max(worldtransform_.translation_.y, kMoveLimitMaxY);
	worldtransform_.translation_.y = min(worldtransform_.translation_.y, +kMoveLimitMinY);

	//�s��X�V
	worldtransform_.matWorld_ = CreateMatIdentity();
	worldtransform_.matWorld_ *= CreateMatScale(worldtransform_.scale_);
	worldtransform_.matWorld_ *= CreateMatRotationX(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationY(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationZ(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatTranslation(worldtransform_.translation_);
	worldtransform_.TransferMatrix();


	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		AccessPhaseUpdate();
		break;

	case Enemy::Phase::Leave:
		EliminationPhaseUpdate();
		break;

	}
}

void Enemy::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);
}

Vector3 Enemy::GetWorldPosition() 
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::AccessPhaseUpdate()
{
	//assert(player_);
	//// ���@�L�����̃��[���h���W���擾
	//Vector3 playerPos = player_->GetWorldPosition();
	//// �G�L�����̃��[���h���W���擾
	//Vector3 enemyPos = this->GetWorldPosition();
	//// �G�L���������L�����̍����x�N�g�������߂�
	//Vector3 vector = playerPos;
	//vector -= enemyPos;
	//float length = (float)std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	//// �x�N�g���̐��K��
	//if (length != 0) {
	//	vector /= length;
	//}
	//// ���L�����̍��W���R�s�[
	//Vector3 position = worldtransform_.translation_;

	//�ړ��i�x�N�g�������Z�j
	worldtransform_.translation_ -= {0.05f, 0.0f, 0.0f};

	//�K��̈ʒu�ɓ��B�����痣�E
	if (worldtransform_.translation_.x < 10) {
		phase_ = Enemy::Phase::Leave;
	}
}

void Enemy::EliminationPhaseUpdate()
{
	//�ړ��i�x�N�g�������Z�j
	worldtransform_.translation_ -= {0.2f, 0.0f, 0.0f};
	//�W�����v
	worldtransform_.translation_.y += Vector;
	Vector -= Gravity;

	for (int i = 0; i < 10; i++) {
		Gravity += 0.00001;
	}
}

void Enemy::OnCollision(){}

float Enemy::GetRadius() { return radius_; }