#include "PlayerA.h"
#include "Function.h"
#include <cassert>

/// <summary>
/// ������
/// �������烂�f���f�[�^�ƃe�N�X�`���f�[�^���󂯎��
/// </summary>
/// <param name="model"></param>
/// <param name="textureHandle"></param>
void PlayerA::Initialize(Model* model, uint32_t textureHandle){

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("player.png");
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// �v���C���[�̈ʒu
	worldtransform_.translation_ = { -40,-5,0 };

	worldtransform_.Initialize();
	//3D���e�B�N���̏�����
	worldtransform3DReticle_.Initialize();
}

void PlayerA::Update()
{

	if (input_->PushKey(DIK_R)) {
		worldtransform_.translation_ = { -40,-5,0 };
	}

	Vector3 move = { 0,0,0 };

	//�L�����N�^�[�̈ړ��̑���
	const float kCharacterSpeed = 0.2f;
	const float kCharacterJumpSpeed = 0.6f;
	const float gravitySpeed = 0.15f;

	//��ɏd�͂𑫂��Ă�
	move.y -= gravitySpeed;
	//�v���C���[�̈ړ�
	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}
	/*if (input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	}*/
	//�W�����v
	if (input_->TriggerKey(DIK_SPACE)) {
		if (jumpFlg == 0) {
			jumpFlg = 1;
		}
	}
	if (jumpFlg == 1) {
		jumpTimer--;
	}
	if (jumpTimer <= 25 && jumpTimer >= 1) {
		move.y += kCharacterJumpSpeed;
	}
	if (jumpTimer <= -80) {
		jumpFlg = 0;
		jumpTimer = 26;
	}
	
	//�L�[�{�[�h���͂ɂ��ړ�����
	const float kMoveLimitX = 35;
	const float kMoveLimitMaxY = 3;
	const float kMoveLimitMinY = 15;

	//�͈͂𒴂��Ȃ�����
	worldtransform_.translation_.x = max(worldtransform_.translation_.x, -kMoveLimitX);
	worldtransform_.translation_.x = min(worldtransform_.translation_.x, +kMoveLimitX);
	worldtransform_.translation_.y = max(worldtransform_.translation_.y, kMoveLimitMaxY);
	worldtransform_.translation_.y = min(worldtransform_.translation_.y, +kMoveLimitMinY);


	worldtransform_.translation_ += move;

	//�s��X�V
	worldtransform_.matWorld_ = CreateMatIdentity();
	worldtransform_.matWorld_ *= CreateMatScale(worldtransform_.scale_);
	worldtransform_.matWorld_ *= CreateMatRotationX(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationY(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationZ(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatTranslation(worldtransform_.translation_);
	worldtransform_.TransferMatrix();

	//���@�̃��[���h���W����3D���e�B�N���̃��[���h���W���v�Z

	//���@����3D���e�B�N���ւ̋���
	/*const float kDistancePlayerTo3DReticle = 60.0f;*/
	//���@����3D���e�B�N���ւ̃I�t�Z�b�g(Z+����)
	/*Vector3 offset = { 0, 0, 1.0f };*/
	//���@�̃��[���h���W�̉�]�𔽉f

}

void PlayerA::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);

}

Vector3  PlayerA::GetWorldPosition() {
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];
	return worldPos;
}

// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
void PlayerA::OnCollision() {}

float PlayerA::GetRadius() { return radius_; }