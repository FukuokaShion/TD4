/**
 * @file PlayerMove.h
 * @brief プレイヤーの移動パターン
 */

#pragma once
#include"PlayerState.h"

//待機
class PlayerMove : public PlayerState {
public:
	PlayerMove();
	~PlayerMove();
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
	const char* groupName_= "playerMove";
	
	int timer_;
	int limit_;

	int speedTimer_;
	int speedMaxTime_;
	float walkMaxSpeed_;
	float dashMaxSpeed_;
	bool isDash_;
	int pushBTimer_;
	int avoidSwitchTime_;
	bool isChangeAvoid_;
};