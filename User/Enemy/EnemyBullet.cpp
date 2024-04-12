/**
 * @file EnemyBullet.cpp
 * @brief 敵の弾
 */

#include "EnemyBullet.h"

std::unique_ptr<Model> EnemyBullet::model_ = nullptr;
std::unique_ptr<ParticleManager> EnemyBullet::particle_ = nullptr;

EnemyBullet::EnemyBullet() {
}

EnemyBullet::~EnemyBullet() {
	LightGroup::GetInstance()->RemoveCircleShadow(circleShadow_);
}

void EnemyBullet::StaticInitialize() {
	model_ = Model::LoadFromOBJ("boll");
	particle_ = std::make_unique<ParticleManager>();
	particle_.get()->Initialize();
}
void EnemyBullet::StaticFinalize() {
}

void EnemyBullet::Initialize(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime) {
	obj_ = Object3d::Create();
	obj_->SetModel(model_.get());
	const float rad = 0.5f;
	obj_->wtf.scale = { rad,rad,rad };
	obj_->wtf.position = pos;
	velocity_ = velocity;

	liveTimer_ = liveLimit;
	stayTime_ = stayTime;
	isDead_ = false;

	sphere_ = new BaseCollider;
	sphere_->SetRad(rad);
	sphere_->SetCenter(pos);
	const int power = 60;
	sphere_->SetPower(power);
	sphere_->SetAttribute(Attribute::EnemyBullet);

	CollisionManager::GetInstance()->AddCollider(sphere_);
	circleShadow_ = new CircleShadow();
	circleShadow_->SetActive(true);
	circleShadow_->SetDistanceCasterLight(-rad);
	LightGroup::GetInstance()->SetCircleShadow(circleShadow_);
}

void EnemyBullet::Update() {
	circleShadow_->SetCasterPos(obj_->wtf.position);
	if (stayTime_ < 0) {
		liveTimer_--;
		if (liveTimer_ < 0) {
			isDead_ = true;
			CollisionManager::GetInstance()->RemoveCollider(sphere_);
			LightGroup::GetInstance()->RemoveCircleShadow(circleShadow_);
		}
		CreateParticle();
		obj_->wtf.position += velocity_;
	}
	else {
		stayTime_--;
	}

	if (sphere_->GetIsHit().playerBody == true) {
		isDead_ = true;
		CollisionManager::GetInstance()->RemoveCollider(sphere_);
		LightGroup::GetInstance()->RemoveCircleShadow(circleShadow_);
	}
	sphere_->SetCenter(obj_->wtf.position);
	obj_->Update();
}

void EnemyBullet::ParticleUpdate() {
	particle_->Update();
}

void EnemyBullet::Draw() {
	obj_->Draw();
}

void EnemyBullet::ParticleDraw() {
	particle_->Draw();
}

void EnemyBullet::CreateParticle() {
	const int accrualNum = 10;
	for (int i = 0; i < accrualNum; i++) {
		//生成位置
		Vector3 pos = obj_->wtf.position - (velocity_ / static_cast<float>(accrualNum) * static_cast<float>(i));
		//速度
		Vector3 vel = { 0,0,0 };
		//加速度
		Vector3 acc = { 0,0,0 };
		//パーティクルサイズ
		const float start = 1.0f;
		const float end = 0.0f;
		//生存時間
		const int lifeTime = 15;
		//追加
		particle_->Add(lifeTime, pos, vel, acc, start, end, { 1,1,0.5f,1 });
	}
}