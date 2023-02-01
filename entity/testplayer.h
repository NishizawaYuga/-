#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "MatSet.h"
#include <Object3d.h>

class TestPlayer {//�X�e�[�W�̓���e�X�g�p�ɏ㉺���E�ɂ���������v���C���[

public:
	//�R���X�g���N�^
	TestPlayer();
	//�f�X�g���N�^
	~TestPlayer();

	//������
	void Initialize(Object3d* model_);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//���W�̃Q�b�^�[
	Vector3 GetPos() { return worldTransform_.position_; }
private:
	//�L�[����
	Input* input_ = nullptr;;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;
	//3D���f��
	Object3d* model_ = nullptr;
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//�ړ����x
	const float speed = 3.0f;
};
