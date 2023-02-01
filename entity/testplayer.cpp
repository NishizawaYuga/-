#include "testplayer.h"

TestPlayer::TestPlayer() {}
TestPlayer::~TestPlayer(){
	delete model_;
}

void TestPlayer::Initialize(Object3d* model) {
	input_ = Input::GetInstance();
	//ファイル名を指定してテクスチャの読み込み
	//textureHandle_ = TextureManager::Load("uvChecker.png");
	//3Dモデル生成
	model_ = model;
	model_ = Object3d::Create();
	//ワールドトランスフォーム初期化
	worldTransform_.position_ = { 0,0,0 };
}

void TestPlayer::Update() {
	//キャラの移動ベクトル
	Vector3 move = { 0,0,0 };
	//位置更新用
	MatSet2 matset;
	if (input_->PressKey(DIK_W)) {
		move.y -= speed;
	}
	if (input_->PressKey(DIK_A)) {
		move.x -= speed;
	}
	if (input_->PressKey(DIK_S)) {
		move.y += speed;
	}
	if (input_->PressKey(DIK_D)) {
		move.x += speed;
	}
	//移動ベクトルをワールドトランスフォームに加算
	worldTransform_.position_ += move;
	//更新
	worldTransform_.matWorld_ = matset.MatIdentity(worldTransform_);
	worldTransform_.UpdateMatrix();
}

void TestPlayer::Draw() {
	//モデルを描画
	model_->Draw(worldTransform_);
}