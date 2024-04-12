/**
 * @file PlayerJumpAttack.h
 * @brief プレイヤーのジャンプ攻撃パターン
 */

#pragma once
#include"PlayerState.h"

//攻撃
class PlayerJumpAttack : public PlayerState {
public:
	PlayerJumpAttack();
	~PlayerJumpAttack();
	/**
	 * @brief 更新
	*/
	void Update() override;

private:
	/**
	 * @brief 状態移行
	*/
	void StateTransition() override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "playerJumpAttack";
	enum class Action {
		Attack,
		After,
	};
	Action action_;
	int timer_;

	//攻撃時
	float attackFallSpeed_;
	int power_;

	//後隙
	int afterTime_;

	//当たり判定
	BaseCollider* sowrd_;

	float animationSpeed_;
};