#include "Skydome.h"
#include <Function.h>
#include <cassert>

void Skydome::Initialize(Object3d* model)
{
	assert(model);

	worldtransform_.Initialize();
	//スケーリングの設定
	worldtransform_.scale_ = { 250.0f, 250.0f, 250.0f };
	//スケーリング行列
	worldtransform_.matWorld_ = CreateMatScale(worldtransform_.scale_);
	//行列の転送
	worldtransform_.UpdateMatrix();

	model_ = model;
}

void Skydome::Update()
{
}

void Skydome::Draw(ViewProjection& viewProjection_)
{
	//3Dモデル描画
	model_->Draw(worldtransform_);
}
