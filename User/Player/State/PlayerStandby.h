/**
 * @file PlayerStandby.h
 * @brief プレイヤーの待機パターン
 *        各行動後この状態になる
 */

#pragma once
#include"PlayerState.h"

//待機
class PlayerStandby : public PlayerState {
public:
	PlayerStandby();
	
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

};