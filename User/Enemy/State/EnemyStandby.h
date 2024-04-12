/**
 * @file EnemyStandby.h
 * @brief 敵の待機状態パターン
 *        各行動終了後にこの状態になる
 */

#pragma once
#include"EnemyState.h"

//待機
class Standby : public EnemyState {
public:
	Standby();
	~Standby();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "enemyStandby";
	//待機時間
	int limit_;

	//接近移行距離
	float approachDistance_;
};