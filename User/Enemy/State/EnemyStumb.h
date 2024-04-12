/**
 * @file EnemyStumb.h
 * @brief 敵のスタンパターン
 */
#pragma once
#include"EnemyState.h"

class EnemyStumb : public EnemyState {
public:
	EnemyStumb();
	~EnemyStumb();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "enemyStumb";

	int limit_;

	//落下
	bool IsOnGround_;
	float fallSpeed_;
	
};