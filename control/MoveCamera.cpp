#include "MoveCamera.h"

ViewProjection MoveCamera::Move(ViewProjection viewProjection, Vector3 position) {
	viewProjection.camera_.eye_ = position;
	return viewProjection;
}