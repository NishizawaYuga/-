#include "GamePlayScene.h"
#include "SafeDelete.h"

DirectXBasis* GamePlayScene::dxBas_ = DirectXBasis::GetInstance();
Input* GamePlayScene::input_ = Input::GetInstance();
DrawBasis* GamePlayScene::drawBas_ = DrawBasis::GetInstance();

void GamePlayScene::Initialize() {
	Initialize2d();
	Initialize3d();
}

void GamePlayScene::Update() {
	input_->Update();

	Update3d();
	Update2d();
}

void GamePlayScene::Draw() {
	Object3d::PreDraw(dxBas_->GetCommandList().Get());
	Draw3d();
	Object3d::PostDraw();

	drawBas_->PreDraw();
	Draw2d();
	drawBas_->PostDraw();
}

void GamePlayScene::Initialize3d() {
	playerModel_ = Model::LoadFromOBJ("chr_sword");
	playerObject_ = Object3d::Create();
	playerObject_->SetModel(playerModel_);

	blockModel_ = Model::LoadFromOBJ("cube");
	blockObject_ = Object3d::Create();
	blockObject_->SetModel(blockModel_);

	player_ = new Player();
	player_->Initialize(playerObject_,reticleSprite_);

	stage_ = new Stage();
	stage_->Initialize(blockObject_, 0.0f);
}

void GamePlayScene::Initialize2d() {
	drawBas_->LoadTexture(0, "cursor.png");

	reticleSprite_ = new Sprite();
	reticleSprite_->Initialize(drawBas_,0);
}

void GamePlayScene::Update3d() {
	player_->Update();
	stage_->Update(player_->GetPos(), player_->GetFlag());
}

void GamePlayScene::Update2d() {
}

void GamePlayScene::Draw3d() {
	stage_->Draw();
	player_->Draw(/*playerObject_,playerObject_*/);
}

void GamePlayScene::Draw2d() {
	player_->DrawUI();
}

void GamePlayScene::Finalize() {
	SafeDelete(playerModel_);
	SafeDelete(playerObject_);

	SafeDelete(blockModel_);
	SafeDelete(blockObject_);

	SafeDelete(reticleSprite_);

	SafeDelete(player_);
	SafeDelete(stage_);
}