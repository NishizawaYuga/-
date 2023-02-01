#pragma once
#include <Enum.h>
#include "DirectXBasis.h"
#include "Input.h"
#include <Sprite.h>
#include "DrawBasis.h"

class TitleScene
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	Scene GetNextScene() { return nextScene_; }

	int GetChangeFlag() { return changeFlag_; }

private:
	//static DirectXBasis* dxBas_;
	Input* input = nullptr;
	Scene nextScene_ = Scene::TITLE;
	int changeFlag_ = false;
	//�X�v���C�g
	Sprite* spriteBG = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;

	static DrawBasis* drawBas_;
};
