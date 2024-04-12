/**
 * @file PlayerAttack.cpp
 * @brief プレイヤーの攻撃パターン
 */

#include"Player.h"
#include"PlayerAttack.h"
#include"PlayerStandby.h"
#include"CollisionManager.h"

PlayerAttack::PlayerAttack() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "anticTime", 16);
	GlobalVariables::GetInstance()->AddItem(groupName_, "anticDistance", { 0,0,1 });
	GlobalVariables::GetInstance()->AddItem(groupName_, "attackTime", 11);
	GlobalVariables::GetInstance()->AddItem(groupName_, "attackDistance", { 0,0,1 });
	GlobalVariables::GetInstance()->AddItem(groupName_, "sowrdPower", 60);
	GlobalVariables::GetInstance()->AddItem(groupName_, "afterTime", 6);
	GlobalVariables::GetInstance()->AddItem(groupName_, "animationSpeed", 1.5f);
	ApplyGlobalVariables();

	player_->PlayWav("attack.wav");
	action_ = Action::Antic;
	timer_ = 0;
	player_->AnimationChange(Player::Animation::ATTACK, animationSpeed_);
	
	sowrd_ = new BaseCollider;
	sowrd_->SetAttribute(Attribute::PlayerAttack);
	sowrd_->SetRad(0.3f);
	sowrd_->SetPower(sowrdPower_);
}

void PlayerAttack::ApplyGlobalVariables() {
	anticTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "anticTime");
	anticDistance_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "anticDistance");
	attackTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "attackTime");
	attackDistance_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "attackDistance");
	sowrdPower_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "sowrdPower");
	afterTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "afterTime");
	animationSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "animationSpeed");
}

PlayerAttack::~PlayerAttack() {
	isAttack_ = false;
	CollisionManager::GetInstance()->RemoveCollider(sowrd_);
}

//攻撃
void PlayerAttack::Update() {
	stamina_->Update();
	timer_++;
	Transform playerWtf = player_->GetWtf();
	float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);

	switch (action_) {
	case Action::Antic:
		//予備動作
		speed_ = anticDistance_ / static_cast<float>(anticTime_);
		velocity_ = Matrix4::bVelocity(speed_, playerWtf.matWorld);
		if (player_->IsRockOn()) {
			player_->RotaY(camAngle);
		}
		player_->Move(velocity_);

		if (timer_ > anticTime_) {
			timer_ = 0;
			CollisionManager::GetInstance()->AddCollider(sowrd_);
			action_ = Action::Attack;
		}
		break;
	case Action::Attack:
		//攻撃
		//移動
		speed_ = attackDistance_ / static_cast<float>(attackTime_);
		velocity_ = Matrix4::bVelocity(speed_, playerWtf.matWorld);
		player_->Move(velocity_);

		//パーティクル
		player_->CreateParticle();

		//攻撃判定
		sowrd_->SetCenter(player_->GetSwordPos(0.3f));
		isAttack_ = true;
		power_ = sowrdPower_;

		if (timer_ > attackTime_) {
			timer_ = 0;
			CollisionManager::GetInstance()->RemoveCollider(sowrd_);
			action_ = Action::After;
		}
		break;
	case Action::After:
		//後隙
		if (timer_ > afterTime_) {
			isAttack_ = false;
			player_->TransitionTo(new PlayerStandby);
		}
		break;
	}
}

void PlayerAttack::StateTransition() {
	player_->TransitionTo(new PlayerStandby);
}