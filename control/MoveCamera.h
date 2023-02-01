#pragma once
#include <ViewProjection.h>
#include <Vector3.h>

class MoveCamera {
public:
	//カメラを動かす処理
	//ViewProjectionに動かしたいカメラ、Vector3はカメラを合わせたいモデルの座標
	ViewProjection Move(ViewProjection viewProjection, Vector3 position);
};
