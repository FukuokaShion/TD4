/**
 * @file PlayerDust.h
 * @brief 砂埃
 */

#pragma once
#include "ParticleManager.h"

using namespace MyEngine;

class PlayerDust {
public:
	PlayerDust();
	~PlayerDust();

	/**
	 * @brief 発生
	*/
	void Accrual(Vector3 pos);

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief 描画
	*/
	void Draw();

public:
	//パーティクル
	std::unique_ptr<ParticleManager> particle_;
};