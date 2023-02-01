#pragma once
#include "Object3d.h"
//#include "DebugText.h"
#include "Input.h"
#include <memory>
#include <list>
#include <ViewProjection.h>

//���@�N���X�̑O���錾
class PlayerA;

class GameScene;

class Enemy {
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

	//�s���t�F�[�Y
	enum class Phase {
		Approach,//�ڋ߂���
		Leave,//���E����
	};
	
	bool Isdead() const { return isDead_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
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

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;

	void AccessPhaseUpdate();

	// ���E�t�F�[�Y�̍X�V
	void EliminationPhaseUpdate();

	////���L����
	//Player* player_ = nullptr;

	//�Q�[���V�[��
	GameScene* gameScene_ = nullptr;

	//�x�N�g��
	float Vector = 0.2;
	//���x
	int SpeedX = 7;
	//�d��
	float Gravity = 0;
	//���a
	const float radius_ = 1.0f;
	//�f�X�t���O
	bool isDead_ = false;
};