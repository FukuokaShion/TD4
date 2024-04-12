/**
 * @file PlayerAttack.h
 * @brief プレイヤーの攻撃パターン
 */

#pragma once
#include"PlayerState.h"

//攻撃
class PlayerAttack : public PlayerState {
public:
	PlayerAttack();
	~PlayerAttack();
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

private:
	const char* groupName_ = "playerAttack";
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action_;

	Vector3 speed_;
	Vector3 velocity_;

	int timer_;

	///予備動作
	//時間
	int anticTime_ = 16;
	//移動距離
	Vector3 anticDistance_ = { 0,0,1 };

	///攻撃
	//時間
	int attackTime_ = 11;
	//移動距離
	Vector3 attackDistance_ = { 0,0,1 };
	//攻撃力
	int sowrdPower_ = 60;

	///後隙
	int afterTime_ = 6;

	//当たり判定
	BaseCollider* sowrd_;

	//アニメーションスピード
	float animationSpeed_ = 1.5f;
};