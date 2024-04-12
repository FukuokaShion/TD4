/**
 * @file EnemyAttack.cpp
 * @brief 敵の突進攻撃パターン
 */

#include"Enemy.h"
#include"EnemyAttack.h"
#include"EnemyStandby.h"

Attack::Attack() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "anticTime", 45);
	GlobalVariables::GetInstance()->AddItem(groupName_, "anticDistance", { 0,0,1 });
	GlobalVariables::GetInstance()->AddItem(groupName_, "attackTime", 15);
	GlobalVariables::GetInstance()->AddItem(groupName_, "attackDistance", { 0,0,-3 });
	GlobalVariables::GetInstance()->AddItem(groupName_, "power", 220);
	GlobalVariables::GetInstance()->AddItem(groupName_, "afterTime", 45);
	GlobalVariables::GetInstance()->AddItem(groupName_, "colRad", 3.0f);
	ApplyGlobalVariables();
	
	action_ = Action::Antic;
	enemy_->AnimationChange(Enemy::ATTACK);

	attackCol_ = new BaseCollider;
	attackCol_->SetRad(colRad_);
	attackCol_->SetPower(power_);
	attackCol_->SetAttribute(Attribute::EnemyAttack);
}

void Attack::ApplyGlobalVariables() {
	anticTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "anticTime");
	anticDistance_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "anticDistance");
	attackTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "attackTime");
	attackDistance_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "attackDistance");
	power_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "power");
	afterTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "afterTime");
	colRad_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "colRad");
}

Attack::~Attack() {
	enemy_->SetIsAttack(false);
	CollisionManager::GetInstance()->RemoveCollider(attackCol_);
}

	//攻撃
void Attack::Update([[maybe_unused]] Vector3 playerPos) {
	timer++;

	Matrix4 enemyMat = enemy_->GetWtf().matWorld;

	switch (action_) {
	case Action::Antic:
		//予備動作
		speed_ = anticDistance_ / static_cast<float>(anticTime_);
		velocity_ = Matrix4::bVelocity(speed_, enemyMat);
		enemy_->Move(velocity_);

		if (timer > anticTime_) {
			timer = 0;
			action_ = Action::Attack;
			enemy_->SetIsAttack(true);
			CollisionManager::GetInstance()->AddCollider(attackCol_);
		}
		break;
	case Action::Attack:
		//攻撃
		enemy_->PlayWave("enemyat.wav");
		speed_ = attackDistance_ / static_cast<float>(attackTime_);
		velocity_ = Matrix4::bVelocity(speed_, enemyMat);
		enemy_->Move(velocity_);

		attackCol_->SetCenter(enemy_->GetCenterPos());

		enemy_->setPower(power_);

		if (timer > attackTime_) {
			timer = 0;
			action_ = Action::After;
			enemy_->SetIsAttack(false);
			CollisionManager::GetInstance()->RemoveCollider(attackCol_);
		}
		break;
	case Action::After:
		//後隙
		if (timer > afterTime_) {
			enemy_->TransitionTo(new Standby);
		}
		break;
	}
}