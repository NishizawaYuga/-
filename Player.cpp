#include "Player.h"
#include "MathUtility.h"
#include <cassert>
#include "WinApp.h"

using namespace MathUtility;

void Player::Initialize(Model* model, ViewProjection& viewProjection) {
	assert(model);
	assert(&viewProjection);

	model_ = model;
	modelRethicle_ = model;

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	viewProjection_ = viewProjection;

	worldTransform3DReticle_.Initialize();

	cutFlag = false;

	//レティクルのテクスチャ
	//uint32_t textureReticle = TextureManager::Load("cursor.png");

	////スプライト生成
	//sprite2DRethicle_.reset(
	//	Sprite::Create(textureReticle,
	//		Vector2(50.0f, 50.0f),
	//		Vector4(256.0f, 256.0f, 256.0f, 0.5f),
	//		Vector2(0.5f, 0.5f)
	//	)
	//);
	//sprite2DRethicle_->SetSize(Vector2(64, 64));
}

void Player::Update() {
	/*bullets_.remove_if([](
		std::unique_ptr<PlayerBullet>& bullet) {
			return bullet->IsDead();
		});*/

	Move();
	Reticle();
	Attack();

	/*for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}*/
}

void Player::Draw(ViewProjection* viewProjection) {

	//modelRethicle_->Draw(worldTransform3DReticle_, viewProjection_);

	model_->Draw(worldTransform_, *viewProjection);

	/*for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}*/
}

void Player::DrawUI() {
	sprite2DRethicle_->Draw();
}

void Player::Move() {
	XINPUT_STATE joyState;

	Vector2 speed;

	cutFlag = false;

	if (input_->GetJoystickState(0, joyState)) {
		speed.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 1;
		speed.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * 1;
	}
	else {
		if (input_->PushKey(DIK_D)) {
			speed.x = 1;
		}

		if (input_->PushKey(DIK_A)) {
			speed.x = -1;
		}

		if (input_->PushKey(DIK_W)) {
			speed.y = 1;
		}

		if (input_->PushKey(DIK_S)) {
			speed.y = -1;
		}
		if (input_->IsTriggerMouse(0)) {
			cutFlag = true;
		}
	}

	worldTransform_.translation_.x += speed.x;
	worldTransform_.translation_.y += speed.y;

	worldTransform_.matWorld_ = ReCalcMatWorld(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Attack() {
	XINPUT_STATE joyState;

	if (input_->GetJoystickState(0, joyState)) {}

	/*if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER){
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform3DReticle_.translation_);

		bullets_.push_back(std::move(newBullet));
	}

	if (input_->IsPressMouse(0)) {
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform3DReticle_.translation_);

		bullets_.push_back(std::move(newBullet));
	}*/

	debugText_->SetScale(1);
	debugText_->SetPos(10, 300);
}

void Player::Reticle() {
	XINPUT_STATE joyState;

	POINT mousePosition;
	//マウスの座標を取得
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換
	HWND hwnd =
		WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	//Vector2 spritePosition = sprite2DRethicle_->GetPosition();

	//if (input_->GetJoystickState(0, joyState)) {
	//	spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5;
	//	spritePosition.y += (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5;

	//	sprite2DRethicle_->SetPosition(spritePosition);
	//}
	//else {
	//	//マウス座標を代入
	//	sprite2DRethicle_->SetPosition(
	//		Vector2(mousePosition.x, mousePosition.y));
	//}

	//ビュープロジェクションビューポート合成行列
	Matrix4 matViewPort = Matrix4Identity();
	matViewPort.m[0][0] = static_cast<float>(WinApp::kWindowWidth) / 2;
	matViewPort.m[1][1] = static_cast<float>(-(WinApp::kWindowHeight)) / 2;
	matViewPort.m[3][0] = static_cast<float>(WinApp::kWindowWidth) / 2;
	matViewPort.m[3][1] = static_cast<float>(WinApp::kWindowHeight) / 2;

	Matrix4 matVPV = viewProjection_.matView
		* viewProjection_.matProjection
		* matViewPort;

	//上を逆行列化
	Matrix4 matInverseVPV = MathUtility::Matrix4Inverse(matVPV);

	////ニア
	//Vector3 posNear = Vector3(
	//	sprite2DRethicle_->GetPosition().x,
	//	sprite2DRethicle_->GetPosition().y,
	//	0);
	//posNear = Vector3TransformCoord(posNear, matInverseVPV);
	//ファー
	/*Vector3 posFar = Vector3(
		sprite2DRethicle_->GetPosition().x,
		sprite2DRethicle_->GetPosition().y,
		1);
	posFar = Vector3TransformCoord(posFar, matInverseVPV);*/
	
	//レイ
	//Vector3 rayDirection = posFar - posNear;

	const float kDistanceTestObject = 50;
	//ニア→レイ
	/*Vector3 offset = rayDirection - posNear;
	offset = Vector3Normalize(offset);*/

	//worldTransform3DReticle_.translation_ = offset * kDistanceTestObject;
	worldTransform3DReticle_.translation_.z -= 50;

	//再計算
	worldTransform3DReticle_.matWorld_ = ReCalcMatWorld(worldTransform3DReticle_);
	//転送
	worldTransform3DReticle_.TransferMatrix();

	debugText_->SetScale(1);
	/*debugText_->SetPos(10, 100);
	debugText_->Printf("2dRethicle: %f,%f", sprite2DRethicle_->GetPosition().x, sprite2DRethicle_->GetPosition().y);*/
	debugText_->SetPos(10, 120);
	debugText_->Printf("Mouse: %d,%d", mousePosition.x, mousePosition.y);
	debugText_->SetPos(10, 150);
	debugText_->Printf("3dRethicle: %f,%f,%f", worldTransform3DReticle_.translation_.x, worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	/*debugText_->SetPos(10, 180);
	debugText_->Printf("Near: %f,%f,%f", posNear.x, posNear.y, posNear.z);*/
	/*debugText_->SetPos(10, 210);
	debugText_->Printf("Far: %f,%f,%f", posFar.x, posFar.y, posFar.z);*/
	debugText_->SetPos(10, 500);
	debugText_->Printf("PlayerPos: %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}

Matrix4 Player::ReCalcMatWorld(WorldTransform worldTransform) {
	worldTransform.matWorld_ = Matrix4Identity();

	worldTransform.matWorld_ *=
		Matrix4Scaling(
			worldTransform.scale_.x,
			worldTransform.scale_.y,
			worldTransform.scale_.z);

	worldTransform.matWorld_ *=
		Matrix4RotationY(worldTransform.rotation_.y);
	worldTransform.matWorld_ *=
		Matrix4RotationX(worldTransform.rotation_.z);
	worldTransform.matWorld_ *=
		Matrix4RotationZ(worldTransform.rotation_.x);

	worldTransform.matWorld_ *=
		Matrix4Translation(
			worldTransform.translation_.x,
			worldTransform.translation_.y,
			worldTransform.translation_.z);

	return worldTransform.matWorld_;
}