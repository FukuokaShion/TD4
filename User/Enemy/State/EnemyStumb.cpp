/**
 * @file EnemyStumb.cpp
 * @brief 敵のスタンパターン
 */
#include"Enemy.h"
#include"EnemyStumb.h"
#include"EnemyStandby.h"

EnemyStumb::EnemyStumb() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "limit", 240);
	GlobalVariables::GetInstance()->AddItem(groupName_, "fallSpeed", 0.1f);
	ApplyGlobalVariables();
	timer = limit_;
	IsOnGround_ = false;
	enemy_->AnimationChange(Enemy::STUMB);
}

void EnemyStumb::ApplyGlobalVariables() {
	limit_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "limit");
	fallSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "fallSpeed");
}

EnemyStumb::~EnemyStumb() {}

void EnemyStumb::Update(Vector3 playerPos) {
	playerPos;
	//接地しているか
	if (enemy_->GetWtf().position.y <= 0) {
		IsOnGround_ = true;
	}
	
	if (!IsOnGround_) {
		//浮いているなら
		enemy_->Move({ 0,-fallSpeed_,0 });
	}else {
		//設置しているなら
		timer--;
		stumbGauge_ -= 200.0f / static_cast<float>(limit_);
		if (timer < 0) {
			isStumb_ = false;
			stumbGauge_ = 0;
			enemy_->TransitionTo(new Standby);
		}
	}
}