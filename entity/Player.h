#pragma once
#include "Input.h"
//#include "DebugText.h"
//#include "Model.h"
#include "Object3d.h"
#include "WorldTransform.h"
#include "Sprite.h"
#include "SafeDelete.h"
#include <memory>
#include <list>
#include "ViewProjection.h"

//#include "PlayerBullet.h"

class Player {
public:
	void Initialize(Object3d* model,Object3d* model2,Sprite* sprite/*, ViewProjection& viewProjection*/);
	void Update();	//クリックワープのためにマウス側のオブジェクト座標が必要
	void Draw(/*Object3d* object,Object3d* objectReticle*//*ViewProjection* viewProjection*/);
	void DrawUI();

	//座標ゲッター
	Vector3 GetPos() { return worldTransform_.position_; }
	//フラグゲッター
	bool GetFlag() { return cutFlag; }
private:
	void Move();
	void Attack();
	void Reticle();
	//クリックした位置に飛ぶ
	void ClickWarp();

	Matrix4 ReCalcMatWorld(WorldTransform worldTransform);
public:
private:
	Input* input_ = nullptr;
	//DebugText* debugText_ = nullptr;
	Object3d* object_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	//デバッグ弾
	//std::list<std::unique_ptr<PlayerBullet>> bullets_;

	//レティクル用
	WorldTransform worldTransform3DReticle_;
	//std::unique_ptr<Sprite> sprite2DRethicle_;
	Sprite* sprite2DRethicle_ = nullptr;
	Object3d* objectReticle_ = nullptr;

	//斬ったフラグ
	bool cutFlag;

	//初期位置から移動した距離
	float movingDistanceX = 0;
	float movingDistanceY = 0;

	//float differenceX = 0;
};