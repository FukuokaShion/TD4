/**
 * @file PlayerMove.cpp
 * @brief プレイヤーの移動パターン
 */
#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"
#include"PlayerJump.h"
#include<cmath>

PlayerMove::PlayerMove() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "walkMaxSpeed", 0.3f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "dashMaxSpeed", 0.5f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "speedMaxTime", 15);
	GlobalVariables::GetInstance()->AddItem(groupName_, "avoidSwitchTime", 8);

	player_->AnimationChange(Player::Animation::DASH,0.75f);
	limit_ = 600;
	timer_ = 0;
	speedTimer_ = 0;
	pushBTimer_ = 0;

	isDash_ = false;
	player_->PlayWav("run.wav");
	isChangeAvoid_ = false;
	ApplyGlobalVariables();
}

PlayerMove::~PlayerMove() {
	player_->StopWav();
}

void PlayerMove::ApplyGlobalVariables() {
	walkMaxSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "walkMaxSpeed");
	dashMaxSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "dashMaxSpeed");
	speedMaxTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "speedMaxTime");
	avoidSwitchTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "avoidSwitchTime");
}


void PlayerMove::Update() {
	stamina_->Update();
	Move();
	Rota();
	StateTransition();
}

void PlayerMove::Move() {
	stamina_->Update();
	player_->AccrualDust(player_->GetWtf().position);

	if (Input::GetInstance()->PButtonTrigger(B)) {
		isDash_ = true;
	}

	if (isDash_) {
		pushBTimer_++;
		if (stamina_->Use(staminaCost::DASH) == false) {
			isDash_ = false;
			pushBTimer_ = 0;
		}
		if (Input::GetInstance()->ButtonInput(B) == false) {
			isDash_ = false;
			if (pushBTimer_ <= avoidSwitchTime_) {
				isChangeAvoid_ = true;
			}
			pushBTimer_ = 0;
		}
	}

	timer_++;
	if (timer_ > limit_) {
		timer_ = 0;
		player_->StopWav();
		player_->PlayWav("run.wav");
	}

	//移動量
	Vector3 velocity = { 0,0,0 };
	//移動速度
	float nowSpeed;
	if (isDash_) {
		nowSpeed = std::lerp(0.0f, dashMaxSpeed_, static_cast<float>(speedTimer_) / static_cast<float>(speedMaxTime_));
	}else {
		nowSpeed = std::lerp(0.0f, walkMaxSpeed_, static_cast<float>(speedTimer_) / static_cast<float>(speedMaxTime_));
	}

	if (speedTimer_ < speedMaxTime_) {
		speedTimer_++;
	}

	//スティック入力角度
	float  sticAngle = atan2f(Input::GetInstance()->GetLeftStickVec().x, Input::GetInstance()->GetLeftStickVec().y);
	//カメラ角度
	float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);
	//カメラから見た時の移動方向に合わせる
	float worldAngle = sticAngle + camAngle;

	velocity = { sinf(worldAngle) * nowSpeed,0.0f,cosf(worldAngle) * nowSpeed };

	player_->Move(velocity);
}

void PlayerMove::Rota() {
	if (Input::GetInstance()->LeftStickInput()) {
		Vector2 stickVec = Input::GetInstance()->GetLeftStickVec();
		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));
		float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);

		player_->RotaY(theta + camAngle);
	}
}

void PlayerMove::StateTransition() {
	//待機状態
	if (Input::GetInstance()->LeftStickInput() == false) {
		player_->TransitionTo(new PlayerStandby);
		player_->StopWav();
	}
	//ジャンプ
	if (Input::GetInstance()->PButtonTrigger(A)) {
		if (stamina_->Use(staminaCost::JUMP)) {
			player_->TransitionTo(new PlayerJump);
		}
	}
	//回避
	if (isChangeAvoid_ == true) {
		if (stamina_->Use(staminaCost::AVOID)) {
			player_->TransitionTo(new PlayerAvoid);
		}
	}
	//攻撃
	if (Input::GetInstance()->PButtonTrigger(RB)) {
		if (stamina_->Use(staminaCost::ATTACK)) {
			player_->TransitionTo(new PlayerAttack);
		}
	}
}