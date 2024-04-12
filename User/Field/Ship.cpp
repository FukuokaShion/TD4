/**
 * @file ship.cpp
 * @brief タイトルシーン
 */

#include"Ship.h"
#include"Easing.h"
#include"SpriteLoader.h"

void Ship::Initialize(Vector3 createPos) {
	shipMD_ = Model::LoadFromOBJ("ship");
	ship_ = Object3d::Create();
	ship_->SetModel(shipMD_.get());
	ship_->wtf.position = createPos;
	shipAngle_ = 0.04f * 3.141592f / 180.0f;
	shipSpeed_ = 0.3f;
	timer_ = 0;
	limit_ = 90;

	pushY_ = std::make_unique<Sprite>();
	pushY_->Initialize(SpriteCommon::GetInstance());
	pushY_->SetSize({ WinApp::window_width,WinApp::window_height });
	pushY_->SetTextureIndex(SpriteLoader::TUTORIAL_PUSHY);

	playerMD_ = Model::LoadFromOBJ("playerObj");
	player_ = Object3d::Create();
	player_->SetModel(playerMD_.get());
	player_->wtf.position = createPos;
	player_->wtf.position.y += 0.5f;

	isPlayerDraw_ = false;
}

Ship::~Ship() {
}

void Ship::Update() {
	pushY_->Update();
	const float shipRotaMax = 4 * 3.141592f / 180;
	if (abs(ship_->wtf.rotation.x) > shipRotaMax) {
		shipAngle_ *= -1;
	}
	ship_->wtf.rotation.x += shipAngle_;
	ship_->Update();

	player_->Update();

	if (isMoveShip_) {
		if (timer_ < limit_) {
			timer_++;
		}

		float t = static_cast<float>(timer_) / static_cast<float>(limit_);
		float add = Easing::OutQuad(0, shipSpeed_, t);

		ship_->wtf.position.z += add;
		player_->wtf.position.z += add;
	}
}

void Ship::Draw() {
	if (isPlayerDraw_) {
		player_->Draw();
	}
	ship_->Draw();
}

void Ship::SpriteDraw() {
	if (isSpriteDraw_) {
		pushY_->Draw();
	}
}

void Ship::CheckCol(Vector3 playerPos) {
	Vector2 distance = { playerPos.x - ship_->wtf.position.x,playerPos.z - ship_->wtf.position.z };
	if (drawDistance > distance.length()) {
		isSpriteDraw_ = true;
		if (Input::GetInstance()->PButtonTrigger(Y)) {
			isMoveShip_ = true;
			isPlayerDraw_ = true;
		}
	}
	else {
		isSpriteDraw_ = false;
	}
}