#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "MatSet.h"

class TestPlayer {//ステージの動作テスト用に上下左右にだけ動けるプレイヤー

public:
	//コンストラクタ
	TestPlayer();
	//デストラクタ
	~TestPlayer();

	//初期化
	void Initialize(Model* model_);
	//更新
	void Update();
	//描画
	void Draw(ViewProjection viewProjection_);
	//座標のゲッター
	Vector3 GetPos() { return worldTransform_.translation_; }
private:
	//キー入力
	Input* input_ = nullptr;;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//3Dモデル
	Model* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//移動速度
	const float speed = 3.0f;
};
