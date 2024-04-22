/**
 * @file Player.cpp
 * @brief プレイヤー本体
 */

#include"Player.h"
#include"PlayerDash.h"

using namespace Player;

Main::Main(){}
Main::~Main(){}

void Main::Initialize() {
	//モデル生成
	bodyModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	body_ = std::make_unique<FBXObject3d>();
	body_->Initialize();
	body_->SetModel(bodyModel_.get());
	body_->PlayAnimation(DASH, 3.0f);
	//ステート
	state_ = std::make_unique<Dash>();
	state_->Initialize();
}

void Main::Update() {
	state_->Update();
	body_->wtf.position += {0, 0, 1.0f};
	body_->Update();
}

void Main::FbxDraw() {
	body_->Draw(); }

const Vector3& Player::Main::GetPos() const { return body_->wtf.position; }
