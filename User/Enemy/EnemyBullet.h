/**
 * @file EnemyBullet.h
 * @brief 敵の弾
 */

#pragma once
#include "Object3d.h"
#include "Model.h"
#include"CollisionPrimitive.h"
#include"CollisionManager.h"
#include"ParticleManager.h"

using namespace MyEngine;

class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();

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
	void Initialize(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime = 0);

	/**
	 * @brief 更新
	*/
	void Update();
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
	std::unique_ptr<Object3d> obj_ = nullptr;
	static std::unique_ptr<Model> model_;
	CircleShadow* circleShadow_;

	int liveTimer_;
	Vector3 velocity_;
	int stayTime_;
	bool isDead_;

	BaseCollider* sphere_;

	//パーティクル
	static std::unique_ptr<ParticleManager> particle_;
};