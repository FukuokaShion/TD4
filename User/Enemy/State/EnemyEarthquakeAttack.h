/**
 * @file EnemyEarthquakeAttack.h
 * @brief 敵の地震攻撃
 */

#pragma once
#include"EnemyState.h"
#include"EnemyBomb.h"

 //射撃
class EnemyEarthquakeAttack : public EnemyState {
public:
	EnemyEarthquakeAttack();
	~EnemyEarthquakeAttack();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "EnemyEarthquakeAttack";
	int attackTime_;
	int finTime_;
};