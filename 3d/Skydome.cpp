#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Object3d* model)
{
	//NULLポインタチェック
	assert(model);

	object = model;

	worldtransform_.Initialize();
	worldtransform_.position_ = { 0,0,0 };
	worldtransform_.scale_ = { 250.0f, 250.0f, 250.0f };
	object->SetWorldTransform(worldtransform_);
	//スケーリングの設定
	object->SetScale({ 5, 5, 5 });
	////スケーリング行列
	//worldtransform_.matWorld_ = CreateMatScale(worldtransform_.scale_);
	
	//行列の転送
	worldtransform_.UpdateMatrix();
	object->Update();
}

void Skydome::Update()
{
}

void Skydome::Draw()
{
	//3Dモデル描画
	object->Draw(worldtransform_);
}