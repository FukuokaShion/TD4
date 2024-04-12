/**
 * @file PlayerStumb.cpp
 * @brief プレイヤーのよろけ
 */

#include"Player.h"
#include"PlayerStumb.h"
#include"PlayerStandby.h"

PlayerStumb::PlayerStumb() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "limit", 50);
	GlobalVariables::GetInstance()->AddItem(groupName_, "fallSpeed", 0.1f);
	ApplyGlobalVariables();
	timer_ = limit_;
	IsOnGround_ = false;
	player_->AnimationChange(Player::Animation::STUMB);
}

void PlayerStumb::ApplyGlobalVariables() {
	limit_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "limit");
	fallSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "fallSpeed");
}

void PlayerStumb::Update() {
	stamina_->Update();
	if (player_->GetWtf().position.y <= 0) {
		IsOnGround_ = true;
	}

	if (!IsOnGround_) {
		//浮いているなら
		player_->Move({ 0,-fallSpeed_,0 });
	}else {
		//設置しているなら
		timer_--;
		if (timer_ < 0) {
			StateTransition();
		}
	}
}

void PlayerStumb::StateTransition() {
	player_->TransitionTo(new PlayerStandby);
}