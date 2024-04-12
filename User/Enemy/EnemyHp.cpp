/**
 * @file EnemyHp.cpp
 * @brief 敵の体力を管理する
 */

#include"EnemyHp.h"

EnemyHp::EnemyHp() {
	MaxHp_ = 1000;
	hp_ = MaxHp_;
	isLive_ = true;
	isDeadNow_ = false;
}

EnemyHp::~EnemyHp() {
}

void EnemyHp::Initialize() {
	hp_ = MaxHp_;
	oldHp_ = hp_;
	isLive_ = true;
}

void EnemyHp::Damage(int damage) {
	oldHp_ = hp_;
	hp_ -= damage;
	if (hp_ <= 0 && oldHp_ > 0) {
		isDeadNow_ = true;
		isLive_ = false;
	}
}

bool EnemyHp::IsDeadNow() {
	if (isDeadNow_) {
		isDeadNow_ = false;
		return true;
	}
	return false;
}

void EnemyHp::Heal(int heal) {
	hp_ += heal;
	if (hp_ > MaxHp_) {
		hp_ = MaxHp_;
	}
}