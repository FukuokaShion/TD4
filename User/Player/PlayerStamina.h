/**
 * @file PlayerStamina.h
 * @brief プレイヤーのスタミナ
 */

#pragma once

class PlayerStamina {
public:
	PlayerStamina();
	~PlayerStamina();

	/**
	 * @brief スタミナ消費
	*/
	void Update();

	/**
	 * @brief スタミナ消費
	*/
	bool Use(int cost);

	int GetStamina() { return stamina_; };

private:
	int stamina_;
	int staminaMax_;
	int recovery_;

	int timer_;
	int limit_;
	int extraLimit_;
};