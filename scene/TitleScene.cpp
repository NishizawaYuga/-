#include "TitleScene.h"
#include <cassert>

void TitleScene::Initialize()
{
	
	nextScene_ = Scene::TITLE;

	//ファイル名を指定してテクスチャを読み込む
	drawBas_->LoadTexture(0, "Title.png");
	
	spriteBG = new Sprite();
	spriteBG->Initialize(drawBas_, 0);
	spriteBG->SetAnchorPoint({ 0.0f, 0.0f });

	// 背景スプライト生成
	//spriteBG = Sprite::Create(1, { 0.0f,0.0f });
}

void TitleScene::Update()
{
	changeFlag_ = false;
	/*if (input->TriggerKey(DIK_SPACE)) {*/
		changeFlag_ = true;
		nextScene_ = Scene::GAME;
	}
//}

void TitleScene::Draw()
{
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	drawBas_->PreDraw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	spriteBG->Draw();

	// スプライト描画後処理
	drawBas_->PostDraw;
	// 深度バッファクリア
	//dxBas_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	//Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 3Dモデル描画 

	// 3Dオブジェクト描画後処理
	//Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	drawBas_->PreDraw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	// スプライト描画後処理
	drawBas_->PostDraw;

#pragma endregion

}
