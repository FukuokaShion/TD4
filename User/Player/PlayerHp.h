/**
 * @file PlayerHp.h
 * @brief プレイヤーの体力管理
 */

#pragma once

class PlayerHp {
public:
	PlayerHp();
	~PlayerHp();

	/**
	 * @brief 初期化
	*/
	void Initialize();
	/**
	 * @brief 最大体力設定
	*/
	void SetMaxHp(int maxHp) { this->MaxHp_ = maxHp; };

	/**
	 * @brief 現在の体力取得
	*/
	int GetHp() { return hp_; };
	/**
	 * @brief 被ダメ前体力取得
	*/
	int GetOldHp() { return oldHp_; };
	/**
	 * @brief 生存フラグ
	*/
	bool IsLive() { return isLive_; };

	/**
	 * @brief ダメージを受ける
	*/
	void Damage(int damage);
	/**
	 * @brief 回復
	*/
	void Heal(int heal);

private:
	//最大HP
	int MaxHp_;
	//現在のHP
	int hp_;
	//ダメージを受ける前の体力
	int oldHp_;

	//生存フラグ
	bool isLive_;

};