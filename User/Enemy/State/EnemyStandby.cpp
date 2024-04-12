/**
 * @file EnemyStandby.cpp
 * @brief 敵の待機状態パターン
 *        各行動終了後にこの状態になる
 */

#include"Enemy.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyApproach.h"
#include"EnemyLeave.h"
#include"EnemyShooting.h"
#include"EnemyRoundShooting.h"
#include"EnemyStrongBodyBlow.h"
#include"EnemyBombShooting.h"
#include"EnemyEarthquakeAttack.h"
#include"EnemyStumb.h"

Standby::Standby() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "limit", 60);
	GlobalVariables::GetInstance()->AddItem(groupName_, "approachDistance", 5.0f);
	ApplyGlobalVariables();

	enemy_->AnimationChange(Enemy::STAND);
}

void Standby::ApplyGlobalVariables() {
	limit_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "limit");
	approachDistance_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "approachDistance");
}

Standby::~Standby() {}

//待機
void Standby::Update(Vector3 playerPos) {
	if (playerPos != Vector3{0,0,0}) {
		timer++;
		playerPos;
		//状態切り替え
		if (timer > limit_) {
			int randNum = rand() % 100 + 1;//1から100の範囲になる
			//遠い場合
			if (Vector3::Distance(enemy_->GetWtf().position, playerPos) > approachDistance_) {
				if (0 < randNum && randNum <= 20) {
					enemy_->TransitionTo(new Approach);
				}
				else if (20 < randNum && randNum <= 55) {
					enemy_->TransitionTo(new EnemyShooting);
				}
				else if (55 < randNum && randNum <= 75) {
					enemy_->TransitionTo(new EnemyRoundShooting);
				}
				else {
					enemy_->TransitionTo(new EnemyBombShooting);
				}
			}
			//近い場合
			else {
				if (0 < randNum && randNum <= 37) {
					enemy_->TransitionTo(new Attack);
				}
				else if (37 < randNum && randNum <= 74) {
					enemy_->TransitionTo(new EnemyEarthquakeAttack);
				}
				else {
					enemy_->TransitionTo(new Leave);
				}
			}
		}
	}
}