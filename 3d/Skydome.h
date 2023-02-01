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
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection& viewProjection_);
	
private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Object3d* model_ = nullptr;

};

