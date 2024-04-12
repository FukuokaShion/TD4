/**
 * @file EnemyShootingParticle.cpp
 * @brief 敵のヒット時エフェクト
 */

#include"EnemyShootingParticle.h"

EnemyShootingParticle::EnemyShootingParticle() {
	//パーティクル生成
	shootingParticle_ = std::make_unique<ParticleManager>();
	shootingParticle_.get()->Initialize();
}

EnemyShootingParticle::~EnemyShootingParticle() {
}

void EnemyShootingParticle::Create(Vector3 centerPos, int num) {
	for (int i = 0; i < num; i++) {
		const float half = 0.5f;

		Vector3 pos = centerPos;
		const float rnd_pos = 0.4f;
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;

		//速度
		const float rnd_vel = 0.02f;
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
		const float start = 0.2f;
		const float end = 0.0f;

		//生存時間
		const int lifeTime = 40;

		//追加
		shootingParticle_->Add(lifeTime, pos, vel, acc, start, end, { 1,1,0.5f,1 });
	}
}


void EnemyShootingParticle::Create(Vector3 startPos, Vector3 endPos, int num) {
	const float half = 0.5f;
	for (int i = 0; i < num; i++) {
		Vector3 pos = startPos;
		Vector3 velocity = endPos - startPos;
		pos += velocity * ((float)rand() / RAND_MAX);

		const float rnd_pos = 0.4f;
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;

		//速度
		const float rnd_vel = 0.02f;
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
		const float start = 0.2f;
		const float end = 0.0f;

		//生存時間
		const int lifeTime = 40;

		//追加
		shootingParticle_->Add(lifeTime, pos, vel, acc, start, end, { 1,1,0.5f,1 });
	}
}

void EnemyShootingParticle::EarthquakeCreate(Vector3 centerPos, int num) {
	const float half = 0.5f;
	for (int i = 0; i < num; i++) {
		Vector3 pos = centerPos;
		const float height = 2.0f;
		pos.y += (float)rand() / RAND_MAX * height;
		const float diameter = 16.0f;
		pos.x += (float)rand() / RAND_MAX * diameter - diameter * half;
		pos.z += (float)rand() / RAND_MAX * diameter - diameter * half;

		//速度
		const float rnd_vel = 0.06f;
		Vector3 vel = { 0,0,0 };
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel * half;
		vel.y = (float)rand() / RAND_MAX * rnd_vel;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel * half;

		//加速度
		Vector3 acc = { 0,0,0 };

		//パーティクルサイズ
		const float start = 0.4f;
		const float end = 0.0f;

		//生存時間
		const int lifeTime = 80;

		//追加
		shootingParticle_->Add(lifeTime, pos, vel, acc, start, end, { 1,1,0.5f,1 });
	}
}

void EnemyShootingParticle::Update() {
	shootingParticle_->Update();
}

void EnemyShootingParticle::Draw() {
	shootingParticle_->Draw();
}