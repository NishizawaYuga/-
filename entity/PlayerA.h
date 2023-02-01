#pragma once
#include <WorldTransform.h>
#include <Object3d.h>
//#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"

/// <summary>
/// ���L����
/// </summary>

class PlayerA {
public:
	/// <summary>
	///������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Object3d* model);

	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	///�`��
	/// </summary>
	void Draw();

	// ���[���h���W���擾
	Vector3 GetWorldPosition();
	
	bool IsDead() const { return isDead_; }
	//�R�[���o�b�N
	void OnCollision();
	float GetRadius();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Object3d* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	//DebugText* debugText_ = nullptr;

	//3D���e�B�N���p���[���h�g�����X�t�H�[��
	WorldTransform worldtransform3DReticle_;
	//�W�����v
	int jumpFlg = 0;
	int jumpTimer = 26;
	const float radius_ = 1.0f;

	// �f�X�t���O
	bool isDead_ = false;
};