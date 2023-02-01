#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "MatSet.h"
#include <Object3d.h>

class TestPlayer {//ステージの動作テスト用に上下左右にだけ動けるプレイヤー

public:
	//コンストラクタ
	TestPlayer();
	//デストラクタ
	~TestPlayer();

	//初期化
	void Initialize(Object3d* model_);
	//更新
	void Update();
	//描画
	void Draw();
	//座標のゲッター
	Vector3 GetPos() { return worldTransform_.position_; }
private:
	//キー入力
	Input* input_ = nullptr;;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//3Dモデル
	Object3d* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//移動速度
	const float speed = 3.0f;
};
