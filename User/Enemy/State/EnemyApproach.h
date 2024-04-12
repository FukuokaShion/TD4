/**
 * @file EnemyApproach.h
 * @brief 敵の接近パターン
 */

#pragma once
#include"EnemyState.h"

class Approach : public EnemyState {
public:
	Approach();
	~Approach();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "enemyApproach";
	//移動速度
	float speed_;
	//最終的な距離
	float distance_;
	//
	int limit_;
	int timer_;
};