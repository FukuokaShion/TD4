/**
 * @file EnemyRoundShooting.h
 * @brief 敵の弾を5つ展開する射撃パターン
 */

#pragma once
#include"EnemyState.h"

//射撃
class EnemyRoundShooting : public EnemyState {
public:
	EnemyRoundShooting();
	~EnemyRoundShooting();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "enemyRoundShooting";
	int interval_;
	int shotTimer_;

	int shotMax_;
	int shotNum_;

	int bulletLiveLimit_;
	float speed_;
};