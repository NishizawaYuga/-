#pragma once
#include "Input.h"
//#include "DebugText.h"
#include "Model.h"
#include "WorldTransform.h"
#include "Sprite.h"
#include "SafeDelete.h"
#include <memory>
#include <list>
#include "ViewProjection.h"

//#include "PlayerBullet.h"

class Player {
public:
	void Initialize(Model* model, ViewProjection& viewProjection);
	void Update();
	void Draw(ViewProjection* viewProjection);
	void DrawUI();

	//座標ゲッター
	Vector3 GetPos() { return worldTransform_.position_; }
	//フラグゲッター
	bool GetFlag() { return cutFlag; }
private:
	void Move();
	void Attack();
	void Reticle();

	Matrix4 ReCalcMatWorld(WorldTransform worldTransform);
public:
private:
	Input* input_ = nullptr;
	//DebugText* debugText_ = nullptr;
	Model* model_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	//デバッグ弾
	//std::list<std::unique_ptr<PlayerBullet>> bullets_;

	//レティクル用
	WorldTransform worldTransform3DReticle_;
	std::unique_ptr<Sprite> sprite2DRethicle_;
	Model* modelRethicle_ = nullptr;

	//斬ったフラグ
	bool cutFlag;
};