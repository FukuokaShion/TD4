/**
 * @file EnemyUI.h
 * @brief エネミーのUI管理クラス
 */
#pragma once
#include"Sprite.h"

class EnemyUI {
public:
	~EnemyUI();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update(int hp, float stumb);

	/**
	 * @brief スプライト描画
	*/
	void Draw();

private:
	Sprite* enemyHpGauge_;
	Sprite* stumbGauge_;
	Sprite* base_;

	const Vector2 hpGaugeSize = { 671,11 };
	const float hpGaugeOneSize = 0.671f;

	Vector2 stumbGaugePos = { 640,600 };
	const Vector2 stumbGaugeSize = { 0,8 };
	const float stumbGaugeOneSize = 1.0f;
};