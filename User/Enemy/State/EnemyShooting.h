/**
 * @file EnemyShooting.h
 * @brief 敵の3点バースト射撃パターン
 */

#pragma once
#include"EnemyState.h"

//射撃
class EnemyShooting : public EnemyState {
public:
	EnemyShooting();
	~EnemyShooting();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "enemyShooting";
	int interval_;
	int shotTimer_;

	int shotMax_;
	int shotNum_;

	int bulletLiveLimit_;
	float speed_;

	int afterTime_;
};