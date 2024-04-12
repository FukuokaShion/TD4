/**
 * @file EnemyParticle.cpp
 * @brief 敵のヒット時エフェクト
 */

#include"EnemyParticle.h"

EnemyParticle::EnemyParticle() {
	//パーティクル生成
	DamageParticle_ = std::make_unique<ParticleManager>();
	DamageParticle_.get()->Initialize();
}

EnemyParticle::~EnemyParticle() {
}

void EnemyParticle::OnColision(Vector3 hitPos) {
	for (int i = 0; i < 50; i++) {
		const float half = 0.5f;

		const float rnd_pos = 0.3f;
		Vector3 pos = hitPos;
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;

		//速度
		const float rnd_vel = 0.1f;
		Vector3 vel = { 0,0,0 };
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel * half;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel * half;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel * half;

		//加速度
		const float rnd_acc = 0.00001f;
		Vector3 acc = { 0,0,0 };
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc * half;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc * half;
		//パーティクルサイズ
		const float start = 0.15f;
		const float end = 0.0f;

		//生存時間
		const int lifeTime = 30;

		//追加
		DamageParticle_->Add(lifeTime, pos, vel, acc, start, end, { 1,0.1f,0.1f,1 });
	}
}

void EnemyParticle::Update() {
	DamageParticle_->Update();
}

void EnemyParticle::Draw() {
	DamageParticle_->Draw();
}