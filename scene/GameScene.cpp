#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <Function.h>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	//モデル初期化
	//model_->CreateFromOBJ("cube",true);
	model_ = Model::Create();

	//仮プレイヤーの初期化
	player_ = new Player();
	player_->Initialize(model_, viewProjection_);

	//ステージの初期化
	stage_ = new Stage();
	stage_->Initialize(model_,0.0f);

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//自キャラの生成
	playera_ = new PlayerA();

	//自キャラの初期化
	playera_->Initialize(model_, textureHandle_);

	//敵キャラの生成
	enemy_ = new Enemy();

	//敵キャラの初期化
	enemy_->Initialize(model_, textureHandle_);

}

void GameScene::Update() {
	player_->Update();
	stage_->Update(player_->GetPos(), player_->GetFlag());

	//自キャラの更新
	playera_->Update();

	//自キャラの更新
	enemy_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//仮プレイヤー描画
	player_->Draw(&viewProjection_);

	//足場描画
	stage_->Draw(viewProjection_);

	//敵キャラの描画
	enemy_->Draw(viewProjection_);
	//自キャラの描画
	playera_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions(){

		//判定対象AとBの座標
		Vector3 posA, posB;

#pragma region 自キャラと敵弾の当たり判定
		////自キャラの座標
		//posA = playera_->GetWorldPosition();
		////敵弾の座標
		//posB = enemy_->GetWorldPosition();

		////AとBの距離を求める
		//Vector3 len = Vector3sub(posA, posB);
		//float distance = length(len);

		////自キャラ敵キャラの半径
		//float radius = playera_->GetRadius() + enemy_->GetRadius();

		////自キャラと敵弾の交差判定
		//if (distance <= radius) {
		//	//自キャラの衝突時コールバックを呼び出す
		//	playera_->OnCollision();
		//	//敵弾の衝突時コールバックを呼び出す
		//	enemy_->OnCollision();
		//}
		
#pragma endregion

}
