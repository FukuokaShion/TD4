/**
 * @file EnemyHp.h
 * @brief 敵の体力を管理する
 */

#pragma once

class EnemyHp {
public:
	EnemyHp();
	~EnemyHp();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 体力上限セッター
	*/
	void SetMaxHp(int maxHp) { this->MaxHp_ = maxHp; };

	/**
	 * @brief 現在の体力取得
	*/
	int GetHp() { return hp_; };
	
	/**
	 * @brief 生存フラグ
	*/
	bool IsLive() { return isLive_; };
	
	/**
	 * @brief 死んだ瞬間
	*/
	bool IsDeadNow();

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
	//直前の体力
	int oldHp_;
	//生存フラグ
	bool isLive_;
	//死んだ瞬間フラグ
	bool isDeadNow_;
};