#include "Goal.h"
#include <cassert>
#include "MatSet.h"
#include "easing.h"

void Goal::Initialize(Object3d* model) {
	//NULLポインタチェック
	assert(model);

	model_ = model;

	//共通の設定
	block_.create = true;
	block_.pos.Initialize();
	block_.pos.scale_ = { 2,2,2 };
	block_.pos.position_ = { 120 * blockSize - 50.0f,8 * -blockSize + 26.0f,-50.0f };
	block_.pos.UpdateMatrix();
	model_->SetWorldTransform(block_.pos);
	model_->Update();
	block_.cutted = false;
	block_.isCut = false;
	block_.timer.nowTime = 0;
	block_.timer.beginCount = false;
	block_.timer.slash = 0;

	input_ = Input::GetInstance();
}

void Goal::Update(Vector3 player, bool cutFlag) {
	MatSet2 matSet;
	if (cutFlag) {
		CheckPos(&player);
		//block[slash].translation_.y = -4.5f;
	}
	//#if _DEBUG
	//	//Rキーが押されたらリセット
	//	if (input_->TriggerKey(DIK_R)) {
	//		Reset();
	//	}
	//#endif

		//全ての足場の更新
	CheckIfCut();


	block_.pos.matWorld_ = matSet.MatIdentity(block_.pos);
	block_.pos.UpdateMatrix();// TransferMatrix();
	model_->SetWorldTransform(block_.pos);
	model_->Update();

}

void Goal::Draw(Vector3 playerPos) {
	const float drawingDistance = 100.0f;
	//3Dモデルを描画

	if (block_.create) {	//生成フラグが立っているものだけ描画(それ以外は見えないが存在はしている)
		float space = block_.pos.position_.x - playerPos.x;
		if (space < drawingDistance && space > -drawingDistance) {	//画面外のブロックは非表示にする（負荷軽減？）
			model_->Draw(block_.pos/*, viewProjection*/);
		}
	}

}

void Goal::CheckPos(Vector3* player) {
	float positionX[128];

	//プレイヤーを中心に範囲内にあるブロックを全て斬る
	if (player->x - range < block_.pos.position_.x && player->x + range > block_.pos.position_.x) {
		if (player->y - range < block_.pos.position_.y && player->y + range > block_.pos.position_.y) {
			block_.isCut = true;
			block_.timer.slash = true;
			block_.timer.beginCount = true;
		}
	}


}

void Goal::CheckIfCut() {
	//斬られたフラグがtrueかつ既に斬られているフラグがfalseかチェック
	if (block_.isCut && !block_.cutted) {
		//ずらす時間のカウントが始まっていればカウントを進める
		if (block_.timer.beginCount) {
			//経過時間が移動時間になるまで処理を続ける
			if (block_.timer.nowTime >= maxTime) {
				block_.cutted = true;
			}
			//イージング処理
			block_.pos.position_.y -= EASE::OutQuad(slippingNumbers, 0,
				maxTime, block_.timer.nowTime);
			//経過時間が移動時間を超すまでの間加算し続ける
			if (block_.timer.nowTime < maxTime) {
				block_.timer.nowTime++;
			}
		}

	}

}
