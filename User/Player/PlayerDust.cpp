/**
 * @file PlayerDust.cpp
 * @brief 砂埃
 */

#include"PlayerDust.h"

PlayerDust::PlayerDust() {
	//パーティクル生成
	particle_ = std::make_unique<ParticleManager>();
	particle_->Initialize();
}

PlayerDust::~PlayerDust() {}

void PlayerDust::Accrual(Vector3 pos) {
	for (int i = 0; i < 7; i++) {
		const float half = 0.5f;

		const float rnd_pos = 0.6f;
		Vector3 accrualPos = pos;
		accrualPos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;
		accrualPos.y = 0;
		accrualPos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos * half;

		//速度
		const float rnd_vel = 0.01f;
		Vector3 vel = { 0,0,0 };
		vel.y = (float)rand() / RAND_MAX * rnd_vel;

		//加速度
		const float rnd_acc = 0.00001f;
		Vector3 acc = { 0,0,0 };
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc * half;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc * half;
		//パーティクルサイズ
		const float start = 0.15f;
		const float end = 0.0f;

		//生存時間
		const int lifeTime = 15;

		//追加
		particle_->Add(lifeTime, accrualPos, vel, acc, start, end, { 0.444f,0.294f,0.196f,1 });
	}
}

void PlayerDust::Update() {
	particle_->Update();
}

void PlayerDust::Draw() {
	particle_->Draw();
}