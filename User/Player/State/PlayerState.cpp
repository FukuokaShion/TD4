/**
 * @file PlayerState.cpp
 * @brief プレイヤーのステートパターン基底
 */

#include"PlayerState.h"
#include"Player.h"

Player* PlayerState::player_ = nullptr;
PlayerStamina* PlayerState::stamina_ = new PlayerStamina;

PlayerState::PlayerState() {
	isAttack_ = false;
	power_ = Player::Power::ZERO;
}