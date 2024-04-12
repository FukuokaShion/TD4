/**
 * @file PlayerJump.cpp
 * @brief プレイヤーのジャンプパターン
 */

#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerJump.h"
#include"PlayerJumpAttack.h"
#include"Easing.h"

PlayerJump::PlayerJump() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "limit", 20);
	GlobalVariables::GetInstance()->AddItem(groupName_, "maxSpeed", 0.2f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "maxPos", 2.0f);
	ApplyGlobalVariables();

	player_->AnimationChange(Player::Animation::JUMP);
	timer_ = 0;
	groundPos = 0;
	up_ = true;
	player_->PlayWav("jump.wav");
	isPushRB_ = false;
}

void PlayerJump::ApplyGlobalVariables() {
	limit_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "limit");
	maxSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "maxSpeed");
	maxPos_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "maxPos");
}

void PlayerJump::Update() {
	stamina_->Update();
	if (up_ == true) {
		timer_++;
		if (timer_ > limit_) {
			up_ = false;
		}
	}
	else {
		timer_--;
	}

	if (Input::GetInstance()->ButtonInput(RB)) {
		isPushRB_ = true;
	}

	float t = static_cast<float>(timer_) / static_cast<float>(limit_);

	float newPos = Easing::OutQuad(groundPos, maxPos_, t);

	player_->SetPosY(newPos);

	Rota();
	Move();

	StateTransition();
}

void PlayerJump::Move() {
	//移動量
	Vector3 velocity = { 0,0,0 };
	float speed = 0.0f;

	//スティック入力
	if (Input::GetInstance()->LeftStickInput()) {
		speed = maxSpeed_;
	}
	float  sticAngle = atan2f(Input::GetInstance()->GetLeftStickVec().x, Input::GetInstance()->GetLeftStickVec().y);
	//カメラ角度
	float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);
	//カメラから見た時の移動方向に合わせる
	float worldAngle = sticAngle + camAngle;

	velocity = { sinf(worldAngle) * speed,0.0f,cosf(worldAngle) * speed };

	player_->Move(velocity);
}

void PlayerJump::Rota() {
	if (Input::GetInstance()->LeftStickInput()) {
		Vector2 stickVec = Input::GetInstance()->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));
		float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);

		player_->RotaY(theta + camAngle);
	}
}

void PlayerJump::StateTransition() {
	if (player_->GetWtf().position.y <= groundPos) {
		player_->PlayWav("landing.wav");
		player_->SetPosY(0);
		player_->TransitionTo(new PlayerStandby);
	}else {
		if (up_ == false && isPushRB_ == true) {
			if (stamina_->Use(staminaCost::JUMPATTACK)) {
				player_->TransitionTo(new PlayerJumpAttack);
			}
		}
	}
}