/**
 * @file EnemyBomb.h
 * @brief 敵の爆弾
 */

#pragma once
#include "Object3d.h"
#include "Model.h"
#include"CollisionPrimitive.h"
#include"CollisionManager.h"
#include"ParticleManager.h"

using namespace MyEngine;

class EnemyBomb{
public:
	EnemyBomb();
	~EnemyBomb();

	/**
	 * @brief 静的初期化
	*/
	static void StaticInitialize();

	/**
	 * @brief 静的破棄
	*/
	static void StaticFinalize();

	/**
	 * @brief 初期化
	*/
	void Initialize(Vector3 creatPos);

	/**
	 * @brief 更新
	*/
	void Update(Vector3 stayPos, Vector3 playerPos);
	/**
	 * @brief 更新
	*/
	static void ParticleUpdate();

	/**
	 * @brief 描画
	*/
	void Draw();

	/**
	 * @brief パーティクル描画
	*/
	static void ParticleDraw();

	/**
	 * @brief 更新
	*/
	bool IsDead() { return isDead_; };

private:
	/**
	 * @brief パーティクル生成
	*/
	void CreateParticle();

private:
	//モデル
	std::unique_ptr<Object3d> obj_ = nullptr;
	static std::unique_ptr<Model> model_;
	BaseCollider* sphere_;
	CircleShadow* circleShadow_;

	//待機
	int stayTime_;
	float startRad_;

	//移動
	Vector3 velocity_;
	float speed_;

	//爆発
	int explosionTime_;
	bool isExplosion_;
	float maxRad_;
	float sizeChangeRate_;

	//全体
	int timer_;
	bool isFired_;
	int liveTimer_;
	bool isDead_;

	static std::unique_ptr<ParticleManager> particle_;
};