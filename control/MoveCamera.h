#pragma once
#include <ViewProjection.h>
#include <Vector3.h>

class MoveCamera {
public:
	//�J�����𓮂�������
	//ViewProjection�ɓ����������J�����AVector3�̓J���������킹�������f���̍��W
	ViewProjection Move(ViewProjection viewProjection, Vector3 position);
};
