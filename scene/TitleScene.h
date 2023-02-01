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
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Scene GetNextScene() { return nextScene_; }

	int GetChangeFlag() { return changeFlag_; }

private:
	//static DirectXBasis* dxBas_;
	Input* input = nullptr;
	Scene nextScene_ = Scene::TITLE;
	int changeFlag_ = false;
	//スプライト
	Sprite* spriteBG = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	static DrawBasis* drawBas_;
};
