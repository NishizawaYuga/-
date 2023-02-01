#include "Enemy.h"
#include <cassert>
#include <Function.h>


void Enemy::Initialize(Object3d* model)
{
	//NULLポインタチェック
	assert(model);

	model_ = model;
	//textureHandle_ = textureHandle;
	// テクスチャ読み込み
	//textureHandle_ = TextureManager::Load("enemy.png");
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	//debugText_ = DebugText::GetInstance();

	// 敵キャラの位置
	worldtransform_.position_ = { 55,-11,0 };

	//ワールド変換の初期化
	worldtransform_.Initialize();

}

void Enemy::Update()
{

	if (input_->PressKey(DIK_R)) {
		// 敵キャラの位置
		worldtransform_.position_ = { 55,-11,0 };
	}
	//キーボード入力による移動処理
	/*const float kMoveLimitX = 35;*/
	const float kMoveLimitMaxY = -11;
	const float kMoveLimitMinY = 15;

	//範囲を超えない処理
	/*worldtransform_.position_.x = max(worldtransform_.position_.x, -kMoveLimitX);
	worldtransform_.position_.x = min(worldtransform_.position_.x, +kMoveLimitX);*/
	worldtransform_.position_.y = max(worldtransform_.position_.y, kMoveLimitMaxY);
	worldtransform_.position_.y = min(worldtransform_.position_.y, +kMoveLimitMinY);

	//行列更新
	worldtransform_.matWorld_ = CreateMatIdentity();
	worldtransform_.matWorld_ *= CreateMatScale(worldtransform_.scale_);
	worldtransform_.matWorld_ *= CreateMatRotationX(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationY(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationZ(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatTranslation(worldtransform_.position_);
	worldtransform_.UpdateMatrix();


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

void Enemy::Draw()
{
	model_->Draw(worldtransform_);
}

Vector3 Enemy::GetWorldPosition() 
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::AccessPhaseUpdate()
{
	//assert(player_);
	//// 自機キャラのワールド座標を取得
	//Vector3 playerPos = player_->GetWorldPosition();
	//// 敵キャラのワールド座標を取得
	//Vector3 enemyPos = this->GetWorldPosition();
	//// 敵キャラ→自キャラの差分ベクトルを求める
	//Vector3 vector = playerPos;
	//vector -= enemyPos;
	//float length = (float)std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	//// ベクトルの正規化
	//if (length != 0) {
	//	vector /= length;
	//}
	//// 自キャラの座標をコピー
	//Vector3 position = worldtransform_.position_;

	//移動（ベクトルを加算）
	worldtransform_.position_ -= {0.05f, 0.0f, 0.0f};

	//規定の位置に到達したら離脱
	if (worldtransform_.position_.x < 10) {
		phase_ = Enemy::Phase::Leave;
	}
}

void Enemy::EliminationPhaseUpdate()
{
	//移動（ベクトルを加算）
	worldtransform_.position_ -= {0.2f, 0.0f, 0.0f};
	//ジャンプ
	worldtransform_.position_.y += Vector;
	Vector -= Gravity;

	for (int i = 0; i < 10; i++) {
		Gravity += 0.00001;
	}
}

void Enemy::OnCollision()
{
	worldtransform_.position_ = { 55,-11,0 };
	/*isDead_ = true;*/
}

float Enemy::GetRadius() { return radius_; }