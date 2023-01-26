#pragma once
#include "BaseScene.h"

#include "Input.h"
#include "DrawBasis.h"
#include "Model.h"
#include "Sprite.h"
#include "Object3d.h"

#include "Player.h"
#include "stage.h"


#include <memory>
#include <List>

class GamePlayScene : public BaseScene {
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	void Initialize3d();
	void Initialize2d();

	void Update3d();
	void Update2d();

	void Draw3d();
	void Draw2d();
public:

private:
	//基盤
	static DirectXBasis* dxBas_;
	static Input* input_;
	static DrawBasis* drawBas_;

	/// <summary>
	/// オブジェクト
	/// </summary>
	
	Player* player_ = nullptr;
	Object3d* playerObject_ = nullptr;
	Model* playerModel_ = nullptr;

	Stage* stage_ = nullptr;
	Object3d* blockObject_ = nullptr;
	Model* blockModel_ = nullptr;

	/// <summary>
	/// スプライト
	/// </summary>
	Sprite* reticleSprite_ = nullptr;
};