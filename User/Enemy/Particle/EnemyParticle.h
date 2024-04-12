/**
 * @file EnemyParticle.h
 * @brief　敵のヒット時エフェクト
 */

#pragma once
#include "ParticleManager.h"

using namespace MyEngine;

class EnemyParticle {
public:
	EnemyParticle();
	~EnemyParticle();

	/**
	 * @brief 発生
	*/
	void OnColision(Vector3 hitPos);

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
	std::unique_ptr<ParticleManager> DamageParticle_;
};