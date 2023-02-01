#include "Skydome.h"
#include <Function.h>
#include <cassert>

void Skydome::Initialize(Object3d* model)
{
	assert(model);

	worldtransform_.Initialize();
	//�X�P�[�����O�̐ݒ�
	worldtransform_.scale_ = { 250.0f, 250.0f, 250.0f };
	//�X�P�[�����O�s��
	worldtransform_.matWorld_ = CreateMatScale(worldtransform_.scale_);
	//�s��̓]��
	worldtransform_.UpdateMatrix();

	model_ = model;
}

void Skydome::Update()
{
}

void Skydome::Draw(ViewProjection& viewProjection_)
{
	//3D���f���`��
	model_->Draw(worldtransform_);
}
