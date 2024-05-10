/**
 * @file Player.cpp
 * @brief プレイヤー本体
 */

#include"Player.h"
#include"PlayerDash.h"
#include"PlayerJump.h"
#include"PlayerSlide.h"

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
	body_->wtf.rotation += state_->GetRotaVector();
	body_->wtf.position += state_->GetMoveVector();
	body_->Update();
	state_->Update(this);
}

void Main::FbxDraw() {
	body_->Draw(); 
}

void Main::TransitionTo(StateNum nextState) {
	if (nextState==StateNum::DASH_STATE) {
		state_ = std::make_unique<Dash>();
		AnimationChange(Main::Animation::DASH);
	}else if (nextState == StateNum::JUMP_STATE) {
		state_ = std::make_unique<Jump>();
	}else if (nextState == StateNum::SLIDE_STATE) {
		state_ = std::make_unique<Slide>();
		AnimationChange(Main::Animation::SLIDE);
	}
	state_->Initialize();
}