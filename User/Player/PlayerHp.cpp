/**
 * @file PlayerHp.cpp
 * @brief プレイヤーの体力管理
 */

#include"PlayerHp.h"

PlayerHp::PlayerHp() {
	MaxHp_ = 1000;
	hp_ = MaxHp_;
	oldHp_ = MaxHp_;
	isLive_ = true;
}

PlayerHp::~PlayerHp() {
}

void PlayerHp::Initialize() {
	hp_ = MaxHp_;
	oldHp_ = MaxHp_;
	isLive_ = true;
}

void PlayerHp::Damage(int damage) {
	oldHp_ = hp_;
	hp_ -= damage;
	if (hp_ <= 0) {
		isLive_ = false;
	}
}

void PlayerHp::Heal(int heal) {
	hp_ += heal;
	if (hp_ > MaxHp_) {
		hp_ = MaxHp_;
	}
}