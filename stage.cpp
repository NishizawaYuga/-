#include "stage.h"
#include <cassert>
#include "MatSet.h"
#include "easing.h"

void Stage::Initialize(Model* model, float anyPosY) {
	//NULLポインタチェック
	assert(model);

	//リセット時のY座標取得
	//resetPosY = anyPosY;

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
	for (int y = 0; y < blockNum; y++) {	//i,jを本来使うが視覚的にわかりやすくするためx,yを使用
		for (int x = 0; x < blockNum; x++) {
			block[y][x].pos.scale_ = { 2,2,2 };
			block[y][x].pos.translation_ = { x * 4.0f - 50.0f,y * 4.0f - 50.0f,0.0f };
			block[y][x].pos.Initialize();
			block[y][x].cutted = false;
			block[y][x].isCut = false;
			block[y][x].timer.nowTime = 0;
			block[y][x].timer.beginCount = false;
			block[y][x].timer.slash = 0;
		}
		resetPosY[y] = y * 4.0f - 50.0f;
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
	/*if (input_->TriggerKey(DIK_R)) {
		for (int i = 0; i < blockNum; i++) {
			block[i].pos.scale_ = { 2,2,2 };
			block[i].pos.translation_ = { i * 4.0f - 50.0f,resetPosY,0.0f };
			block[i].cutted = false;
			block[i].isCut = false;
			block[i].timer.nowTime = 0;
			block[i].timer.beginCount = false;
			block[i].timer.slash = 0;
		}
	}*/

	//全ての足場の更新
	CheckIfCut();
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			block[y][x].pos.matWorld_ = matSet.MatIdentity(block[y][x].pos);
			block[y][x].pos.TransferMatrix();
		}
	}
}

void Stage::Draw(ViewProjection viewProjection) {
	//3Dモデルを描画
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			if (block[y][x].create) {	//生成フラグが立っているものだけ描画(それ以外は見えないが存在はしている)
				model->Draw(block[y][x].pos, viewProjection);
			}
		}
	}

}

void Stage::CheckPos(Vector3* player) {
	float positionX[32];
	float range = 100000.0f;
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			//プレイヤーと足場の距離を計算する
			positionX[x] = block[y][x].pos.translation_.x - player->x;
			//プレイヤーより後ろにあるなら-1をかけて正の数に戻す
			if (positionX[x] < 0) {
				positionX[x] *= -1.0f;
			}
			//距離が短いブロックを探す
			if (range > positionX[x]) {
				range = positionX[x];
			}
		}
	}
	//最も距離が短かったブロックの番号を検索する
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			if (range == positionX[x]) {
				//高さ的に射程範囲外だったら弾く
				if (player->y - 10 < block[y][x].pos.translation_.y && player->y + 10 > block[y][x].pos.translation_.y) {
					//斬られたフラグのオン(前2ブロックもまとめて)
					for (int j = x - 1; j < x + 1; j++) {
						//-1やblockNumより高い数値が出てしまったら弾く
						if (j <= blockNum && j >= 0) {
							block[y][j].isCut = true;
							block[y][j].timer.slash = j;
							block[y][j].timer.beginCount = true;
						}
					}
				}
			}
		}
	}
}

void Stage::CheckIfCut() {
	for (int y = 0; y < blockNum; y++) {
		for (int x = 0; x < blockNum; x++) {
			//斬られたフラグがtrueかつ既に斬られているフラグがfalseかチェック
			if (block[y][x].isCut && !block[y][x].cutted) {
				//ずらす時間のカウントが始まっていればカウントを進める
				if (block[y][x].timer.beginCount) {
					//経過時間が移動時間になるまで処理を続ける
					if (block[y][x].timer.nowTime >= maxTime) {
						//block[block[i].timer.slash].timer.nowTime = 0;
						block[y][block[y][x].timer.slash].cutted = true;
					}
					//イージング処理
					block[y][x].pos.translation_.y -= EASE::OutQuad(slippingNumbers, 0,
						maxTime, block[y][x].timer.nowTime);
					//経過時間が移動時間を超すまでの間加算し続ける
					if (block[y][x].timer.nowTime < maxTime) {
						block[y][x].timer.nowTime++;
					}
				}


			}
		}
	}
}