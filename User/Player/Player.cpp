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
	body_->Update();
	//ステート
	state_ = std::make_unique<Dash>();
	state_->Initialize();
}

void Main::Update() {
	state_->Update(this);
	body_->wtf.rotation += state_->GetRotaVector();
	body_->wtf.position += state_->GetMoveVector();
	body_->Update();
}

void Main::FbxDraw() {
	body_->Draw();
}
