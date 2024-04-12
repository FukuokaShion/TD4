/**
 * @file EnemyStrongBodyBlow.cpp
 * @brief 敵のジャンプ攻撃パターン
 */

#include"Enemy.h"
#include"EnemyStrongBodyBlow.h"
#include"EnemyStandby.h"

EnemyStrongBodyBlow::EnemyStrongBodyBlow() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "anticTime", 30);
	GlobalVariables::GetInstance()->AddItem(groupName_, "attackTime",35);
	GlobalVariables::GetInstance()->AddItem(groupName_, "attackDistance", { 0,0,-49 });
	GlobalVariables::GetInstance()->AddItem(groupName_, "power", 350);
	GlobalVariables::GetInstance()->AddItem(groupName_, "afterTime", 30);
	GlobalVariables::GetInstance()->AddItem(groupName_, "downTime", 60);
	GlobalVariables::GetInstance()->AddItem(groupName_, "colRad", 3.0f);
	ApplyGlobalVariables();
	action_ = Action::Antic;
	enemy_->AnimationChange(Enemy::ATTACK);

	attackCol_ = new BaseCollider;
	attackCol_->SetRad(colRad_);
	attackCol_->SetPower(power_);
	attackCol_->SetAttribute(Attribute::EnemyAttack);
}

void EnemyStrongBodyBlow::ApplyGlobalVariables() {
	anticTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "createTime");
	attackTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "attackTime");
	attackDistance_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "attackDistance");
	power_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "power");
	afterTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "afterTime");
	downTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "downTime");
	colRad_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "colRad");
}

EnemyStrongBodyBlow::~EnemyStrongBodyBlow() {
	enemy_->SetIsAttack(false);
	CollisionManager::GetInstance()->RemoveCollider(attackCol_);
}

//攻撃
void EnemyStrongBodyBlow::Update([[maybe_unused]] Vector3 playerPos) {
	timer++;

	Matrix4 enemyMat = enemy_->GetWtf().matWorld;
	//中心からの距離
	float distance = sqrt((enemy_->GetWtf().position.x * enemy_->GetWtf().position.x) + (enemy_->GetWtf().position.z * enemy_->GetWtf().position.z));
	const int limit = 49;

	switch (action_) {
	case Action::Antic:
		//予備動作
		//プレイヤーの方を向く
		float angle;
		angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
		enemy_->RotaY(angle);

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

		///終了
		//移動仕切った
		if (timer > attackTime_) {
			timer = 0;
			action_ = Action::Dwon;
			enemy_->SetIsAttack(false);
			CollisionManager::GetInstance()->RemoveCollider(attackCol_);
		}
		//フィールドの外に出た
		if (distance > limit) {
			timer = 0;
			action_ = Action::Dwon;
			enemy_->SetIsAttack(false);
			CollisionManager::GetInstance()->RemoveCollider(attackCol_);
		}

		//プレイヤーに攻撃が当たった
		if (attackCol_->GetIsHit().playerBody) {
			timer = 0;
			action_ = Action::After;
			enemy_->SetIsAttack(false);
			CollisionManager::GetInstance()->RemoveCollider(attackCol_);
		}


		break;
	case Action::After:
		//プレイヤーに当たった時の後隙
		if (timer > afterTime_) {
			enemy_->TransitionTo(new Standby);
		}
		break;

	case Action::Dwon:
		if (timer > downTime_) {
			enemy_->TransitionTo(new Standby);
		}

		break;
	}
}