/**
 * @file EnemyDeathParticle.cpp
 * @brief 敵の死亡時エフェクト
 */

#include"EnemyDeathParticle.h"

EnemyDeathParticle::EnemyDeathParticle() {
	//パーティクル生成
	particle_ = std::make_unique<ParticleManager>();
	particle_.get()->Initialize();
}

EnemyDeathParticle::~EnemyDeathParticle() {
}

void EnemyDeathParticle::Accrual(Vector3 centerPos) {
	const int accrualNum = 10;
	for (int i = 0; i < accrualNum; i++) {
		const float half = 0.5f;

		//生成位置
		const float rnd_pos = 3.0f;
		const float enemySizeY = 4.0f;
		Vector3 pos = centerPos;

		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;
		pos.y += (float)rand() / RAND_MAX * enemySizeY;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;

		//速度
		Vector3 vel = { 0,0,0 };
		const float speed = 0.02f;
		const float zSpeed = 0.05f;
	
		vel.x = (float)rand() / RAND_MAX * speed - speed * half;
		vel.y = (float)rand() / RAND_MAX * speed - speed * half;
		vel.z = (float)rand() / RAND_MAX * zSpeed;

		//加速度
		Vector3 acc = { 0,0,0 };

		//パーティクルサイズ
		const float start = 0.1f;
		const float end = 0.0f;

		//生存時間
		const int lifeTime = 90;

		//追加
		particle_->Add(lifeTime, pos, vel, acc, start, end,{1,1,0.5f,1});
	}
}

void EnemyDeathParticle::Update() {
	particle_->Update();
}

void EnemyDeathParticle::Draw() {
	particle_->Draw();
}