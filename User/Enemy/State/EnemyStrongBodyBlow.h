/**
 * @file EnemyStrongBodyBlow.h
 * @brief 敵のジャンプ攻撃パターン
 */

#pragma once
#include"EnemyState.h"

 //攻撃
class EnemyStrongBodyBlow : public EnemyState {
public:
	EnemyStrongBodyBlow();
	~EnemyStrongBodyBlow();

	/**
	 * @brief 更新
	*/
	void Update([[maybe_unused]] Vector3 playerPos) override;

	/**
	 * @brief 調整項目の適用
	*/
	void ApplyGlobalVariables() override;
private:
	const char* groupName_ = "enemyStrongBlow";
	enum class Action {
		Antic,
		Attack,
		After,
		Dwon,
	};
	Action action_;

	///予備動作
	//時間
	int anticTime_;
	
	///攻撃
	//時間
	int attackTime_;
	//移動距離
	Vector3 attackDistance_;
	//攻撃力
	int power_;

	///プレイヤーに当たった時の後隙
	int afterTime_;

	///回避された時の後隙
	int downTime_;

	//当たり判定
	BaseCollider* attackCol_;
	float colRad_;
};