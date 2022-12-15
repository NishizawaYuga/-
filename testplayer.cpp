#include "testplayer.h"

TestPlayer::TestPlayer() {}
TestPlayer::~TestPlayer(){
	delete model_;
}

void TestPlayer::Initialize(Model* model) {
	input_ = Input::GetInstance();
	//�t�@�C�������w�肵�ăe�N�X�`���̓ǂݍ���
	textureHandle_ = TextureManager::Load("uvChecker.png");
	//3D���f������
	model_ = model;
	model_ = Model::Create();
	//���[���h�g�����X�t�H�[��������
	worldTransform_.translation_ = { 0,0,0 };
}

void TestPlayer::Update() {
	//�L�����̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };
	//�ʒu�X�V�p
	MatSet2 matset;
	if (input_->PushKey(DIK_W)) {
		move.y -= speed;
	}
	if (input_->PushKey(DIK_A)) {
		move.x -= speed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y += speed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += speed;
	}
	//�ړ��x�N�g�������[���h�g�����X�t�H�[���ɉ��Z
	worldTransform_.translation_ += move;
	//�X�V
	worldTransform_.matWorld_ = matset.MatIdentity(worldTransform_);
	worldTransform_.TransferMatrix();
}

void TestPlayer::Draw(ViewProjection viewProjection_) {
	//���f����`��
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}