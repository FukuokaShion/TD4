/**
 * @file EnemyState.cpp
 * @brief 敵のステートパターン基底クラス
 */

#include"EnemyState.h"
#include"Enemy.h"
#include"EnemyStumb.h"

Enemy* EnemyState::enemy_ = nullptr;
float EnemyState::stumbGauge_ = 0;
float EnemyState::stumbGaugeMax_ = 200;
float EnemyState::stumbGaugeDecrease_ = 0.2f;
bool EnemyState::isStumb_ = false;

EnemyState::EnemyState() {
	timer = 0;
	speed_ = { 0,0,0 };
	velocity_ = { 0,0,0 };
}

void EnemyState::StumbGaugeUpdate() {
	if (stumbGauge_ > 0 && isStumb_ == false) {
		stumbGauge_ -= stumbGaugeDecrease_;
		if (stumbGauge_ < 0) {
			stumbGauge_ = 0.0f;
		}
	}
}

void EnemyState::StumbGaugeIncrease(int damage) {
	if (!isStumb_) {
		stumbGauge_ += static_cast<float>(damage) * 0.8f;
		if (stumbGauge_ > stumbGaugeMax_) {
			enemy_->TransitionTo(new EnemyStumb);
			isStumb_ = true;
		}
	}
}