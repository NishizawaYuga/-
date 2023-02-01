#pragma once
#include <WorldTransform.h>
#include <Model.h>
#include <ViewProjection.h>
#include "Object3d.h"

class Skydome
{
public:

	void Initialize(Object3d* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection_);
	
private:

	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Object3d* model_ = nullptr;

};

