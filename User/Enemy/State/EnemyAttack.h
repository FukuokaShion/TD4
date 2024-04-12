/**
 * @file EnemyAttack.h
 * @brief 敵の突進攻撃パターン
 */

#pragma once
#include"EnemyState.h"

//攻撃
class Attack : public EnemyState {
public:
	Attack();
	~Attack();

	/**
	 * @brief 更新
	*/
	void Update([[maybe_unused]]Vector3 playerPos) override;
	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;

private:
	const char* groupName_ = "enemyAttack";
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action_;

	///予備動作
	//時間
	int anticTime_;
	//移動距離
	Vector3 anticDistance_;

	///攻撃
	//時間
	int attackTime_;
	//移動距離
	Vector3 attackDistance_;
	//攻撃力
	int power_;

	///後隙
	int afterTime_;

	//当たり判定
	BaseCollider* attackCol_;
	float colRad_;
};