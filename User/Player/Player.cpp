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
	body_->PlayAnimation(DASH, 3.0f);
	body_->Update();
	rocalWtf_.Initialize();
	//ステート
	state_ = std::make_unique<Dash>();
	state_->Initialize();
	rotaMax_ = 3.141592f / 8.0f;
	moveMax_ = 6.0f;
	//当たり判定
	colliderRad_ = 0.7f;
	spineBoneNum_ = bodyModel_->GetBoneNum("mixamorig:Spine3");
	bodyCollider_ = new BaseCollider();
	bodyCollider_->SetAttribute(Attribute::PlyerBody);
	bodyCollider_->SetRad(colliderRad_);
	CollisionManager::GetInstance()->AddCollider(bodyCollider_);
}

void Main::Update(const Transform& parentWTF) {
	parentWTF.matWorld;
	if (state_->GetRotaVector().y != 0) {
		rocalWtf_.rotation += state_->GetRotaVector();
	}else {
		rocalWtf_.rotation = {0, 0, 0};
	}
	//回転に制限
	if (rocalWtf_.rotation.y > rotaMax_) {
		rocalWtf_.rotation.y = rotaMax_;
	}else if (rocalWtf_.rotation.y < -rotaMax_) {
		rocalWtf_.rotation.y = -rotaMax_;
	}
	rocalWtf_.position += state_->GetMoveVector();
	//幅に制限
	if (rocalWtf_.position.x > moveMax_) {
		rocalWtf_.position.x = moveMax_;
	}
	else if (rocalWtf_.position.x < -moveMax_) {
		rocalWtf_.position.x = -moveMax_;
	}

	rocalWtf_.UpdateMat();

	body_->wtf.position = rocalWtf_.position * parentWTF.matWorld;
	body_->wtf.rotation.y = rocalWtf_.rotation.y + parentWTF.rotation.y;
	
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
		AnimationChange(Main::Animation::DASH, 3.0f);
	}else if (nextState == StateNum::JUMP_STATE) {
		state_ = std::make_unique<Jump>();
	}else if (nextState == StateNum::SLIDE_STATE) {
		state_ = std::make_unique<Slide>();
		AnimationChange(Main::Animation::SLIDE);
	}
	state_->Initialize();
}