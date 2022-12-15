#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

struct Timer {	//イージング用データ
	float nowTime;	//経過時間
	bool beginCount;	//カウント開始のフラグ
	int slash;	//斬られた番号
};

struct Block {	//実際に処理で使う足場のデータ
	WorldTransform pos;	//自身の座標
	bool isCut;	//自身が斬られたかどうかのフラグ
	bool cutted;	//斬られ終わったフラグ
	Timer timer;
};

class Stage {
public:
	//初期化
	void Initialize(Model* model,float anyPosY);
	//更新
	void Update(Vector3 player,bool cutFlag);
	//テスト用更新
	void UpdateTest();
	//描画
	void Draw(ViewProjection viewProjection);
private:
	//どの足場がプレイヤーと一番近いかチェック
	void CheckPos(Vector3* player);
	//前のブロックも斬られていたら自分もズレる関数
	void CheckIfCut();
private:
	//ワールド座標
	Block block[32];
	//ブロック数
	const int blockNum = 32;
	//モデル
	Model* model = nullptr;
	//ズレる位置
	const double slippingNumbers = 10.0;
	//移動時間
	const float maxTime = 30;

	//debug用(リセット)
	Input* input_ = nullptr;
	float resetPosY;
};
