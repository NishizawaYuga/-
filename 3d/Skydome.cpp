#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Object3d* model)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	object = model;

	worldtransform_.Initialize();
	worldtransform_.position_ = { 0,0,0 };
	worldtransform_.scale_ = { 250.0f, 250.0f, 250.0f };
	object->SetWorldTransform(worldtransform_);
	//�X�P�[�����O�̐ݒ�
	object->SetScale({ 5, 5, 5 });
	////�X�P�[�����O�s��
	//worldtransform_.matWorld_ = CreateMatScale(worldtransform_.scale_);
	
	//�s��̓]��
	worldtransform_.UpdateMatrix();
	object->Update();
}

void Skydome::Update()
{
}

void Skydome::Draw()
{
	//3D���f���`��
	object->Draw(worldtransform_);
}