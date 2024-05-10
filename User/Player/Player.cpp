/**
 * @file Player.cpp
 * @brief プレイヤー本体
 */

#include"imgui.h"
#include"CollisionManager.h"
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
	body_->PlayAnimation(DASH, 1.0f);
	body_->Update();
	//ステート
	state_ = std::make_unique<Dash>();
	state_->Initialize();
	rotaMax_ = 3.141592f / 8.0f;
	//当たり判定
	colliderRad_ = 0.7f;
	spineBoneNum_ = bodyModel_->GetBoneNum("mixamorig:Spine3");
	bodyCollider_ = new BaseCollider();
	bodyCollider_->SetAttribute(Attribute::PlyerBody);
	bodyCollider_->SetRad(colliderRad_);
	CollisionManager::GetInstance()->AddCollider(bodyCollider_);
}

void Main::Update() {
	body_->wtf.rotation += state_->GetRotaVector();
	//回転に制限
	if (body_->wtf.rotation.y > rotaMax_) {
		body_->wtf.rotation.y = rotaMax_;
	}else if (body_->wtf.rotation.y < -rotaMax_) {
		body_->wtf.rotation.y = -rotaMax_;
	}
	body_->wtf.position += state_->GetMoveVector();
	bodyCollider_->SetCenter(body_->GetBonWorldPos(spineBoneNum_));
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