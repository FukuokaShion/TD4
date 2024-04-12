/**
 * @file Scarecrow.cpp
 * @brief チュートリアル用丸太
 */
#include"Scarecrow.h"

Scarecrow::Scarecrow(){}
Scarecrow::~Scarecrow(){}

void Scarecrow::Initialize() {
	//丸太
	model_ = Model::LoadFromOBJ("wood");
	obj_ = Object3d::Create();
	obj_->SetModel(model_.get());
	obj_->wtf.position = { 0,0,8 };
	targetLocalPos_ = { 0,3,0 };
	targetPos_ = obj_->wtf.position + targetLocalPos_;

	sphere_ = new BaseCollider;
	sphere_->SetRad(1.0f);
	sphere_->SetCenter(GetTargetPos());
	sphere_->SetAttribute(Attribute::EnemyBody);
	sphere_->SetRad(0.7f);
	CollisionManager::GetInstance()->AddCollider(sphere_);

	isHit_ = false;
}

void Scarecrow::SetPos(Vector3 newPos) {
	obj_->wtf.position = newPos;
	targetPos_ = obj_->wtf.position + targetLocalPos_;
	sphere_->SetCenter(GetTargetPos());
};

void Scarecrow::Update() {
	OnCollision();
	obj_->Update();
}

void Scarecrow::OnCollision() {
	//ヒット判定
	if (sphere_->GetIsHit().playerAttack) {
		isHit_ = true;
		hitTimer_ = 0;
		sphere_->RemoveHit(Attribute::PlayerAttack);
	}

	//ヒット時処理
	if (isHit_) {
		hitTimer_++;
		
		//シェイク
		float shakeSpeed = 0.05f;
		if (hitTimer_ < limit_ / 12) {
			obj_->wtf.position.x += shakeSpeed;
		}else if (hitTimer_ < 3 * limit_ / 12) {
			obj_->wtf.position.x -= shakeSpeed;
		}else if (hitTimer_ < 5 * limit_ / 12) {
			obj_->wtf.position.x += shakeSpeed;
		}else if (hitTimer_ < 7 * limit_ / 12) {
			obj_->wtf.position.x -= shakeSpeed;
		}else if (hitTimer_ < 9 * limit_ / 12) {
			obj_->wtf.position.x += shakeSpeed;
		}else if (hitTimer_ < 11 * limit_ / 12) {
			obj_->wtf.position.x -= shakeSpeed;
		}else if (hitTimer_ <= limit_) {
			obj_->wtf.position.x += shakeSpeed;
		}

		//処理終了
		if (hitTimer_ > limit_) {
			isHit_ = false;
		}
	}
}

void Scarecrow::Draw() {
	obj_->Draw();
}