#pragma once
#include <3d/Model.h>
#include "DebugText.h"
#include "Input.h"

//自機クラスの前方宣言
class PlayerA;

class GameScene;

class Enemy {
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

	//行動フェーズ
	enum class Phase {
		Approach,//接近する
		Leave,//離脱する
	};

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;

	//フェーズ
	Phase phase_ = Phase::Approach;

	void AccessPhaseUpdate();

	// 離脱フェーズの更新
	void EliminationPhaseUpdate();

	//コールバック
	void OnCollision();

	float GetRadius();
	////自キャラ
	//Player* player_ = nullptr;

	//ゲームシーン
	GameScene* gameScene_ = nullptr;

	//ベクトル
	float Vector = 0.2;
	//速度
	int SpeedX = 7;
	//重力
	float Gravity = 0;

	const float radius_ = 1.0f;
};