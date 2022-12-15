#include "stage.h"
#include <cassert>
#include "MatSet.h"
#include "easing.h"

void Stage::Initialize(Model* model, float anyPosY) {
	//NULLポインタチェック
	assert(model);

	//リセット時のY座標取得
	resetPosY = anyPosY;

	//引数として受け取ったデータをメンバ変数に記録する
	this->model = model;
	//手前がズレると奥も全てズレるするようにする設定方法
	/* {//親限定の設定
		block[0].pos.scale_ = { 3,3,3 };
		block[0].pos.translation_ = { -50.0f,0,0 };
		block[0].pos.Initialize();
		//子限定の設定
		for (int i = 1; i < blockNum; i++) {
			block[i].pos.translation_ = { 2.0f,0,0 };
			//親の登録
			block[i].pos.parent_ = &block[i - 1].pos;
			block[i].pos.Initialize();
		}
		//共通の設定
		for (int i = 0; i < blockNum; i++) {
			block[i].cutted = false;
			block[i].isCut = false;
			block[i].timer.nowTime = 0;
			block[i].timer.beginCount = false;
			block[i].timer.slash = 0;
		}
	}*/
	//周囲のみがズレるようにする設定方法
	for (int i = 0; i < blockNum; i++) {
		block[i].pos.scale_ = { 2,2,2 };
		block[i].pos.translation_ = { i * 4.0f - 50.0f,anyPosY,0.0f };
		block[i].pos.Initialize();
		block[i].cutted = false;
		block[i].isCut = false;
		block[i].timer.nowTime = 0;
		block[i].timer.beginCount = false;
		block[i].timer.slash = 0;
	}

	input_ = Input::GetInstance();
}

void Stage::Update(Vector3 player, bool cutFlag) {
	MatSet2 matSet;
	if (cutFlag) {
		CheckPos(&player);
		//block[slash].translation_.y = -4.5f;
	}
	//Rキーが押されたらリセット
	if (input_->TriggerKey(DIK_R)) {
		for (int i = 0; i < blockNum; i++) {
			block[i].pos.scale_ = { 2,2,2 };
			block[i].pos.translation_ = { i * 4.0f - 50.0f,resetPosY,0.0f };
			block[i].cutted = false;
			block[i].isCut = false;
			block[i].timer.nowTime = 0;
			block[i].timer.beginCount = false;
			block[i].timer.slash = 0;
		}
	}

	//全ての足場の更新
	CheckIfCut();
	for (int i = 0; i < blockNum; i++) {
		block[i].pos.matWorld_ = matSet.MatIdentity(block[i].pos);
		block[i].pos.TransferMatrix();
	}
}

void Stage::Draw(ViewProjection viewProjection) {
	//3Dモデルを描画
	for (int i = 0; i < blockNum; i++) {
		model->Draw(block[i].pos, viewProjection);
	}

}

void Stage::CheckPos(Vector3* player) {
	float positionX[32];
	float range = 100000.0f;
	for (int i = 0; i < blockNum; i++) {
		//プレイヤーと足場の距離を計算する
		positionX[i] = block[i].pos.translation_.x - player->x;
		//プレイヤーより後ろにあるなら-1をかけて正の数に戻す
		if (positionX[i] < 0) {
			positionX[i] *= -1.0f;
		}
		//距離が短いブロックを探す
		if (range > positionX[i]) {
			range = positionX[i];
		}
	}
	//最も距離が短かったブロックの番号を検索する
	for (int i = 0; i < blockNum; i++) {
		if (range == positionX[i]) {
			//高さ的に射程範囲外だったら弾く
			if (player->y - 10 < block[i].pos.translation_.y && player->y + 10 > block[i].pos.translation_.y) {
				//斬られたフラグのオン(前2ブロックもまとめて)
				for (int j = i - 1; j < i + 1; j++) {
					//-1やblockNumより高い数値が出てしまったら弾く
					if (j <= blockNum && j >= 0) {
						block[j].isCut = true;
						block[j].timer.slash = j;
						block[j].timer.beginCount = true;
					}
				}
			}
		}
	}
}

void Stage::CheckIfCut() {
	for (int i = 0; i < blockNum; i++) {
		//斬られたフラグがtrueかつ既に斬られているフラグがfalseかチェック
		if (block[i].isCut && !block[i].cutted) {
			//ずらす時間のカウントが始まっていればカウントを進める
			if (block[i].timer.beginCount) {
				//経過時間が移動時間になるまで処理を続ける
				if (block[i].timer.nowTime >= maxTime) {
					//block[block[i].timer.slash].timer.nowTime = 0;
					block[block[i].timer.slash].cutted = true;
				}
				//イージング処理
				block[i].pos.translation_.y -= EASE::OutQuad(slippingNumbers, block[i].pos.translation_.y,
					maxTime, block[i].timer.nowTime);
				//経過時間が移動時間を超すまでの間加算し続ける
				if (block[i].timer.nowTime < maxTime) {
					block[i].timer.nowTime++;
				}
			}

		}
	}
}