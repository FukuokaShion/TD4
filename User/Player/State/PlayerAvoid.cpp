/**
 * @file PlayerAvoid.cpp
 * @brief プレイヤーの回避パターン
 */

#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAvoid.h"

#include"Easing.h"

PlayerAvoid::PlayerAvoid() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "limit", 42);
	GlobalVariables::GetInstance()->AddItem(groupName_, "speed", { 0,0,0.6f });
	GlobalVariables::GetInstance()->AddItem(groupName_, "animationSpeed", 1.7f);
	ApplyGlobalVariables();

	player_->PlayWav("avoid.wav");
	player_->AnimationChange(Player::Animation::AVOID, animationSpeed_);
	Matrix4 playerMat = player_->GetWtf().matWorld;
	velocity_ = Matrix4::bVelocity(speed_, playerMat);
	timer_ = limit_;
	player_->SetInvincible(true);
}

void PlayerAvoid::ApplyGlobalVariables() {
	limit_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "limit");
	speed_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "speed");
	animationSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "animationSpeed");
}

//待機
void PlayerAvoid::Update() {
	stamina_->Update();
	player_->AccrualDust(player_->GetWtf().position);
	timer_--;

	float t = static_cast<float>(timer_) / static_cast<float>(limit_);

	Vector3 add = Easing::OutQuadVec3({ 0,0,0 }, velocity_, t);

	player_->Move(add);

	if (timer_ < 0) {
		StateTransition();
	}
}

void PlayerAvoid::StateTransition() {
	player_->SetInvincible(false);
	player_->TransitionTo(new PlayerStandby);
}