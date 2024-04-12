/**
 * @file PlayerJump.h
 * @brief プレイヤーのジャンプパターン
 */

#pragma once
#include"PlayerState.h"

class PlayerJump : public PlayerState {
public:
	PlayerJump();
	/**
	 * @brief 更新
	*/
	void Update() override;

private:
	/**
	 * @brief 移動
	*/
	void Move();
	/**
	 * @brief 回転
	*/
	void Rota();

	/**
	 * @brief 状態移行
	*/
	void StateTransition() override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "playerJump";

	int timer_;
	int limit_;

	bool up_;

	float maxSpeed_;

	float maxPos_;
	float groundPos;

	bool isPushRB_;
};