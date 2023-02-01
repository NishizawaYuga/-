#include "Skydome.h"
#include <Function.h>
#include <cassert>

void Skydome::Initialize(Object3d* model)
{
	assert(model);
	model_ = model;

	worldtransform_.Initialize();
	//�X�P�[�����O�̐ݒ�
	worldtransform_.scale_ = { 250.0f, 250.0f, 250.0f };
	//worldtransform_.position_ = { 0,0,0 };
	worldtransform_.UpdateMatrix();
	//�X�P�[�����O�s��
	//worldtransform_.matWorld_ = CreateMatScale(worldtransform_.scale_);
	//�s��̓]��
	//worldtransform_.UpdateMatrix();
	model_->SetWorldTransform(worldtransform_);
	model_->Update();
}

void Skydome::Update()
{
}

void Skydome::Draw()
{
	//3D���f���`��
	model_->Draw(worldtransform_);
}
