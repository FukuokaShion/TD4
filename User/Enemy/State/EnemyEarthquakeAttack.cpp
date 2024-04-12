/**
 * @file EnemyEarthquakeAttack.cpp
 * @brief 敵の地震攻撃
 */

#include"EnemyEarthquakeAttack.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyEarthquakeAttack::EnemyEarthquakeAttack() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "attackTime", 70);
	GlobalVariables::GetInstance()->AddItem(groupName_, "finTime", 130);
	ApplyGlobalVariables();
	enemy_->AnimationChange(Enemy::EARTHQUAKE);
	timer = 0;
}

void EnemyEarthquakeAttack::ApplyGlobalVariables() {
	attackTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "attackTime");
	finTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "finTime");
}

EnemyEarthquakeAttack::~EnemyEarthquakeAttack() {}

void EnemyEarthquakeAttack::Update(Vector3 playerPos) {
	timer++;
	//プレイヤーの方を向く
	float angle;
	if (timer < attackTime_) {
		angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
		enemy_->RotaY(angle);
		enemy_->CreateBulletParticle(Enemy::footL, Enemy::LEG2_L, 8);
	}
	else if (timer == attackTime_) {
		enemy_->CreateEarthquake();
		enemy_->CreateEarthquakeParticle(100);
	}else if (timer == finTime_) {
		//状態移行
		enemy_->TransitionTo(new Standby);
	}
}