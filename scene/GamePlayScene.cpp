#include "GamePlayScene.h"
#include "SafeDelete.h"

DirectXBasis* GamePlayScene::dxBas_ = DirectXBasis::GetInstance();
Input* GamePlayScene::input_ = Input::GetInstance();
DrawBasis* GamePlayScene::drawBas_ = DrawBasis::GetInstance();

void GamePlayScene::Initialize() {
	//ステージデータコピー（仮配置）
	/*data->copyData(stageData, 0);*/
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
	playerModel_ = Model::LoadFromOBJ("plane");
	playerObject_ = Object3d::Create();
	playerObject_->SetModel(playerModel_);

	blockModel_ = Model::LoadFromOBJ("floorblock");
	blockObject_ = Object3d::Create();
	blockObject_->SetModel(blockModel_);

	reticleModel_ = Model::LoadFromOBJ("sphere");
	reticleObject_ = Object3d::Create();
	reticleObject_->SetModel(reticleModel_);

	enemyModel_ = Model::LoadFromOBJ("cube");
	enemyObject_ = Object3d::Create();
	enemyObject_->SetModel(enemyModel_);

	skyModel_ = Model::LoadFromOBJ("skydome");
	skyObject_ = Object3d::Create();
	skyObject_->SetModel(skyModel_);

	player_ = new Player();
	player_->Initialize(playerObject_,reticleObject_,reticleSprite_);

	stage_ = new Stage();
	stage_->Initialize(blockObject_,stageData);

	skydome_ = new Skydome();
	skydome_->Initialize(skyObject_);

	/*enemy_ = new Enemy();
	enemy_->Initialize(enemyObject_);*/
}

void GamePlayScene::Initialize2d() {
	drawBas_->LoadTexture(0, "cursor.png");

	reticleSprite_ = new Sprite();
	reticleSprite_->Initialize(drawBas_,0);
	reticleSprite_->SetAnchorPoint({ 0.5f, 0.5f });
}

void GamePlayScene::Update3d() {
	stage_->Update(player_->GetPos(), player_->GetFlag());
	player_->Update();
	blockObject_->SetCameraMoveVector(player_->GetPos());
	
	//enemy_->Update();
	
}

void GamePlayScene::Update2d() {
}

void GamePlayScene::Draw3d() {
	stage_->Draw(player_->GetPos());
	player_->Draw(/*playerObject_,playerObject_*/);
	skydome_->Draw();
	//enemy_->Draw();
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
	SafeDelete(reticleModel_);
	SafeDelete(reticleObject_);

	SafeDelete(player_);
	SafeDelete(stage_);
}