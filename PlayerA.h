#pragma once
#include <WorldTransform.h>
#include <Model.h>
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"

/// <summary>
/// 自キャラ
/// </summary>

class PlayerA {
public:
	/// <summary>
	///初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ViewProjection viewProjection_);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }

	//コールバック
	void OnCollision();
	float GetRadius();
private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;

	//3Dレティクル用ワールドトランスフォーム
	WorldTransform worldtransform3DReticle_;
	//ジャンプ
	int jumpFlg = 0;
	int jumpTimer = 26;
	const float radius_ = 1.0f;

	// デスフラグ
	bool isDead_ = false;
};