/**
 * @file EnemyBombShooting.cpp
 * @brief 敵の爆弾投下行動
 */

#include"EnemyBombShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyBombShooting::EnemyBombShooting() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "createTime", 20);
	GlobalVariables::GetInstance()->AddItem(groupName_, "finTime", 140);
	ApplyGlobalVariables();
	enemy_->AnimationChange(Enemy::BOMBSHOOT);
	timer = 0;
}

void EnemyBombShooting::ApplyGlobalVariables() {
	createTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "createTime");
	finTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "finTime");
}

EnemyBombShooting::~EnemyBombShooting() {}

void EnemyBombShooting::Update(Vector3 playerPos) {
	enemy_->CreateBulletParticle(Enemy::HAND_R,7);
	timer++;
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);

	if (timer == createTime_) {
		enemy_->CreateBomb();
	}

	if (timer == finTime_) {
		//状態移行
		enemy_->TransitionTo(new Standby);
	}
}