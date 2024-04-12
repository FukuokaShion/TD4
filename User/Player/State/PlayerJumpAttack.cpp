/**
 * @file PlayerJumpAttack.cpp
 * @brief プレイヤーのジャンプ攻撃パターン
 */

#include"Player.h"
#include"PlayerJumpAttack.h"
#include"PlayerStandby.h"
#include"CollisionManager.h"

PlayerJumpAttack::PlayerJumpAttack() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "attackFallSpeed", -0.2f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "power", 100);
	GlobalVariables::GetInstance()->AddItem(groupName_, "afterTime", 40);
	GlobalVariables::GetInstance()->AddItem(groupName_, "animationSpeed", 1.5f);
	ApplyGlobalVariables();

	player_->PlayWav("jumpAttack.wav");
	player_->AnimationChange(Player::Animation::JUMPATTACK, animationSpeed_);
	action_ = Action::Attack;
	timer_ = 0;

	sowrd_ = new BaseCollider;
	sowrd_->SetAttribute(Attribute::PlayerAttack);
	sowrd_->SetRad(0.3f);
	sowrd_->SetPower(power_);
	CollisionManager::GetInstance()->AddCollider(sowrd_);

	float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);
	if (player_->IsRockOn()) {
		player_->RotaY(camAngle);
	}
}

void PlayerJumpAttack::ApplyGlobalVariables() {
	attackFallSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "attackFallSpeed");
	power_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "power");
	afterTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "afterTime");
	animationSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "animationSpeed");
}

PlayerJumpAttack::~PlayerJumpAttack() {
	isAttack_ = false;
	CollisionManager::GetInstance()->RemoveCollider(sowrd_);
}

//攻撃
void PlayerJumpAttack::Update() {
	Vector3 velocity;
	const float groundY = 0;

	switch (action_) {
	case Action::Attack:
		velocity = { 0,attackFallSpeed_,0 };
		player_->Move(velocity);
		//パーティクル
		player_->CreateParticle();
		//攻撃判定
		sowrd_->SetCenter(player_->GetSwordPos(0.3f));
		isAttack_ = true;
		power_ = power_;

		if (player_->GetWtf().position.y <= groundY) {
			player_->SetPosY(groundY);
			action_ = Action::After;
			CollisionManager::GetInstance()->RemoveCollider(sowrd_);
		}
		break;
	case Action::After:
		timer_++;
		isAttack_ = false;
		if (timer_ > afterTime_) {
			StateTransition();
		}
		break;
	}

}

void PlayerJumpAttack::StateTransition() {
	player_->PlayWav("landing.wav");
	player_->TransitionTo(new PlayerStandby);
}