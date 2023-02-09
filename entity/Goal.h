#pragma once
#include "DirectXBasis.h"
#include "Object3d.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

class Goal {
public:
	struct Timer {	//イージング用データ
		float nowTime;	//経過時間
		bool beginCount;	//カウント開始のフラグ
		bool slash;	//斬られた番号
	};

	struct Block {	//実際に処理で使う足場のデータ
		WorldTransform pos;	//自身の座標
		bool isCut;	//自身が斬られたかどうかのフラグ
		bool cutted;	//斬られ終わったフラグ
		Timer timer;
		bool create;	//生成されてるかのフラグ
	};

public:
	//初期化
	void Initialize(Object3d* model);
	//更新
	void Update(Vector3 player,bool cutFlag);
	//描画
	void Draw(Vector3 playerPos);

	//プレイヤーとの距離確認
	void CheckPos(Vector3* player);

	//今斬られたなら
	void CheckIfCut();

	Object3d* SetModel(Object3d* model){ model_ = model; }

private:
	Block block_;

	//ブロックサイズ
	const float blockSize = 4.0f;
	Object3d* model_ = nullptr;
	//ズレる位置(疑似的だが2ブロック分ズレる)
	const double slippingNumbers = 0.39;

	//移動時間
	const float maxTime = 30;
	//debug用(リセット)
	Input* input_ = nullptr;
	float resetPosY[17];

	//射程
	const float range = 6.0f;
};