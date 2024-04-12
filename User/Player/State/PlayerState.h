/**
 * @file PlayerState.h
 * @brief プレイヤーのステートパターン基底
 */

#pragma once
#include"Transform.h"
#include"Input.h"
#include"GlobalVariables.h"
#include"PlayerStamina.h"

class Player;

class PlayerState {
public:
	PlayerState();
	virtual ~PlayerState() {};

	/**
	 * @brief プレイヤー本体をセット
	*/
	void SetPlayer(Player* player) { player_ = player; };
	
	/**
	 * @brief プレイヤーが攻撃常態かチェック
	*/
	bool GetIsAttack() { return isAttack_; };
	int GetPower() { return power_; };
	int GetStamina() { return stamina_->GetStamina(); };
	/**
	 * @brief 更新
	*/
	virtual void Update() = 0;

protected:
	/**
	 * @brief 状態移行
	*/
	virtual void StateTransition() = 0;
	/**
	 * @brief 調整項目の適用
	*/
	virtual void ApplyGlobalVariables() = 0;

protected:
	static Player* player_;
	static PlayerStamina* stamina_;

	//攻撃判定
	bool isAttack_;
	int power_;

	//スタミナ消費量
	enum staminaCost {
		AVOID = 300,
		ATTACK = 100,
		DASH = 1,
		JUMP = 100,
		JUMPATTACK = 150,
	};
};