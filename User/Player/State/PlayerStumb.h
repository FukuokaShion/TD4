/**
 * @file PlayerStumb.h
 * @brief プレイヤーのよろけ
 */

#pragma once
#include"PlayerState.h"

 //待機
class PlayerStumb : public PlayerState {
public:
	PlayerStumb();

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
	const char* groupName_ = "playerStumb";
	int limit_;
	int timer_;

	//落下
	bool IsOnGround_;
	float fallSpeed_;
};