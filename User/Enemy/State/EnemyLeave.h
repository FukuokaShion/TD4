/**
 * @file EnemyLeave.h
 * @brief 敵の離脱パターン
 */

#pragma once
#include"EnemyState.h"

//接近
class Leave : public EnemyState {
public:
	Leave();
	~Leave();
	/**
	 * @brief 更新
	*/
	void Update([[maybe_unused]]Vector3 playerPos) override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "enemyLeave";
	//時間
	int limit_ = 10;
	//移動距離
	Vector3 distance_ = { 0,0,10 };
};