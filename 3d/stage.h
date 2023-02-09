#pragma once
#include "DirectXBasis.h"
#include "Object3d.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Goal.h"

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
	bool create;	//生成されてるかのフラグ
};

class Stage {
public:
	//初期化
	void Initialize(Object3d* model, Object3d* goalModel, int stageData[17][128]);
	//更新
	void Update(Vector3 player,bool cutFlag);
	//描画
	void Draw(Vector3 playerPos);

	Stage() = default;
	~Stage();
private:
	//どの足場がプレイヤーと一番近いかチェック
	void CheckPos(Vector3* player);
	//前のブロックも斬られていたら自分もズレる関数
	void CheckIfCut();
	//ブロックの位置リセット（debug用）
	void Reset();
private:
	//ワールド座標
	//ブロックの数拡張
	Block block[17][128];
	//ブロック数
	const int blockNumX = 128;
	const int blockNumY = 17;
	//ブロックサイズ
	const float blockSize = 4.0f;
	//Model* model = nullptr;
	Object3d* model_[17][128] = {nullptr};
	//ズレる位置(疑似的だが2ブロック分ズレる)
	const double slippingNumbers = 0.39;
	//移動時間
	const float maxTime = 30;

	//debug用(リセット)
	Input* input_ = nullptr;
	float resetPosY[17];

	//射程
	const float range = 6.0f;

	Goal* goal_ = nullptr;
};
