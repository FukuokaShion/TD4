/**
 * @file PlayerStamina.cpp
 * @brief プレイヤーのスタミナ
 */

#include"PlayerStamina.h"

PlayerStamina::PlayerStamina() {
	staminaMax_ = 1000;
	stamina_ = staminaMax_;
	recovery_ = 10;
	limit_ = 60;
	extraLimit_ = 60;
	timer_ = 0;
}
PlayerStamina::~PlayerStamina() {}

void PlayerStamina::Update() {
	if (timer_ > 0) {
		timer_--;
	}else {
		stamina_ += recovery_;
		if (stamina_ > staminaMax_) {
			stamina_ = staminaMax_;
		}
	}
}

bool PlayerStamina::Use(int cost) {
	if (stamina_ > 0) {
		stamina_ -= cost;
		timer_ = limit_;
		if (stamina_ < 0) {
			stamina_ = 0;
			timer_ += extraLimit_;
		}
		return true;
	}
	return false;
}