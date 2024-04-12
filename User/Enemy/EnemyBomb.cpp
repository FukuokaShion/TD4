/**
 * @file EnemyBomb.cpp
 * @brief 敵の爆弾
 */

#include "EnemyBomb.h"

std::unique_ptr<Model> EnemyBomb::model_ = nullptr;
std::unique_ptr<ParticleManager> EnemyBomb::particle_ = nullptr;

EnemyBomb::EnemyBomb() {
}

EnemyBomb::~EnemyBomb() {
}

void EnemyBomb::StaticInitialize() {
	model_ = Model::LoadFromOBJ("boll");
	particle_ = std::make_unique<ParticleManager>();
	particle_.get()->Initialize();
}

void EnemyBomb::StaticFinalize() {
}

void EnemyBomb::Initialize(Vector3 creatPos) {
	startRad_ = 0.5f;
	obj_ = Object3d::Create();
	obj_->SetModel(model_.get());
	obj_->wtf.scale = { startRad_ ,startRad_ ,startRad_ };
	obj_->wtf.position = creatPos;

	stayTime_ = 80;
	timer_ = 0;
	isFired_ = false;
	velocity_ = { 0,0,0 };
	explosionTime_ = 80;
	isExplosion_ = false;
	isDead_ = false;
	sizeChangeRate_ = 0.3f;
	maxRad_ = 6.0f;
	speed_ = 1.6f;

	sphere_ = new BaseCollider;
	sphere_->SetRad(startRad_);
	sphere_->SetCenter(obj_->wtf.position);
	const int power = 200;
	sphere_->SetPower(power);
	sphere_->SetAttribute(Attribute::EnemyBullet);

	CollisionManager::GetInstance()->AddCollider(sphere_);
	
	circleShadow_ = new CircleShadow();
	circleShadow_->SetActive(true);
	circleShadow_->SetDistanceCasterLight(-startRad_);
	LightGroup::GetInstance()->SetCircleShadow(circleShadow_);
}

void EnemyBomb::Update(Vector3 stayPos,Vector3 playerPos) {
	circleShadow_->SetCasterPos(obj_->wtf.position);
	timer_++;
	if (isFired_ == false) {
		obj_->wtf.position = stayPos;
		if (timer_ == stayTime_) {
			//時間経過で発射
			isFired_ = true;
			const Vector3 rocalTargetPos = { 0,-1.0f,0 };
			Vector3 targetPos = playerPos + rocalTargetPos;
			velocity_ = targetPos - obj_->wtf.position;
			velocity_.nomalize();
			velocity_ *= speed_;
		}
	}else if (isFired_ == true) {
		//地面に接触で移動停止
		if (obj_->wtf.position.y >= 0) {
			obj_->wtf.position += velocity_;
			CreateParticle();
			timer_ = 0;
		}
		else {
			//時間経過で爆発
			if (timer_ > explosionTime_) {
				isExplosion_ = true;
			}
			//爆発で広がる
			if (isExplosion_) {
				obj_->wtf.scale += {sizeChangeRate_, sizeChangeRate_, sizeChangeRate_};
				sphere_->SetRad(obj_->wtf.scale.x);
			}
			//一定のサイズに到達で消滅
			if (sphere_->GetRad() > maxRad_) {
				isDead_ = true;
			}
		}
	}

	if (sphere_->GetIsHit().playerBody == true || isDead_ == true) {
		LightGroup::GetInstance()->RemoveCircleShadow(circleShadow_);
		CollisionManager::GetInstance()->RemoveCollider(sphere_);
	}

	sphere_->SetCenter(obj_->wtf.position);
	obj_->Update();
}
void EnemyBomb::ParticleUpdate() {
	particle_->Update();
}

void EnemyBomb::Draw() {
	obj_->Draw();
}
void EnemyBomb::ParticleDraw() {
	particle_->Draw();
}

void EnemyBomb::CreateParticle() {
	const int accrualNum = 10;
	for (int i = 0; i < accrualNum; i++) {
		//生成位置
		Vector3 pos = obj_->wtf.position - (velocity_ / static_cast<float>(accrualNum) * static_cast<float>(i));
		//速度
		Vector3 vel = { 0,0,0 };
		//加速度
		Vector3 acc = { 0,0,0 };
		//パーティクルサイズ
		const float start = startRad_;
		const float end = 0.0f;
		//生存時間
		const int lifeTime = 30;
		//追加
		particle_->Add(lifeTime, pos, vel, acc, start, end, { 1,1,0.5f,1 });
	}
}