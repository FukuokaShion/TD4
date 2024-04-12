/**
 * @file EnemyShooting.cpp
 * @brief 敵の3点バースト射撃パターン
 */

#include"EnemyShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyShooting::EnemyShooting() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "interval", 25);
	GlobalVariables::GetInstance()->AddItem(groupName_, "shotMax", 3);
	GlobalVariables::GetInstance()->AddItem(groupName_, "bulletLiveLimit", 60);
	GlobalVariables::GetInstance()->AddItem(groupName_, "speed", 2.0f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "afterTime", 15);
	ApplyGlobalVariables();

	enemy_->AnimationChange(Enemy::SHOOT);
	shotTimer_ = interval_;
	shotNum_ = 0;
	timer = 0;
}

void EnemyShooting::ApplyGlobalVariables() {
	interval_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "interval");
	shotMax_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "shotMax");
	bulletLiveLimit_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "bulletLiveLimit");
	speed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "speed");
	afterTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "afterTime");
}

EnemyShooting::~EnemyShooting() {}

void EnemyShooting::Update(Vector3 playerPos) {
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);
	if (shotNum_ < shotMax_) {
		enemy_->CreateBulletParticle(Enemy::HAND_R,4);
		shotTimer_--;
		if (shotTimer_ < 0) {
			enemy_->PlayWave("fire.wav");
			//弾生成
			Vector3 createPos = enemy_->GetRightHandPos();
			createPos.y -= 1.0f;

			//速度設定
			Vector3 rocalTargetPos = { 0,2,0 };
			Vector3 targetPos = playerPos + rocalTargetPos;
			Vector3 vec = targetPos - createPos;
			velocity_ = vec.nomalize() * speed_;

			enemy_->CreatBullet(createPos, velocity_, bulletLiveLimit_);

			//次の発射までの時間
			shotTimer_ = interval_;

			//発射数
			shotNum_++;
		}
	}
	//状態移行
	else if (shotNum_ >= shotMax_) {
		timer++;
		if (timer > afterTime_) {
			enemy_->TransitionTo(new Standby);
		}
	}
}