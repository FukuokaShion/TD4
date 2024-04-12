/**
 * @file PlayerAvoid.h
 * @brief プレイヤーの回避パターン
 */

#pragma once
#include"PlayerState.h"

//待機
class PlayerAvoid : public PlayerState {
public:
	PlayerAvoid();
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
	const char* groupName_ = "playerAvoid";
	int limit_;
	int timer_;

	Vector3 speed_;
	Vector3 velocity_;

	float animationSpeed_;
};