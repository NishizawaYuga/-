#include "GameMain.h"
#include "GamePlayScene.h"

Input* GameMain::input_ = Input::GetInstance();

void GameMain::Initialize() {
	Framework::Initialize();
	scene_ = new GamePlayScene();
	scene_->Initialize();
}

void GameMain::Update() {
	Framework::Update();

	scene_->Update();
}

void GameMain::Draw() {
	//描画前処理
	Framework::GetDirectXBasis()->PreDraw();
	scene_->Draw();
	//描画後処理
	Framework::GetDirectXBasis()->PostDraw();
}

void GameMain::Finalize() {
	scene_->Finalize();
	delete scene_;
	Framework::Finalize();
}