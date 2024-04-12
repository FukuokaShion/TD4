/**
 * @file EnemyDeathParticle.h
 * @brief　敵の死亡時エフェクト
 */

#pragma once
#include "ParticleManager.h"

using namespace MyEngine;

class EnemyDeathParticle {
public:
	EnemyDeathParticle();
	~EnemyDeathParticle();

	/**
	 * @brief 発生
	*/
	void Accrual(Vector3 centerPos);

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