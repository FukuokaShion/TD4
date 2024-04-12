/**
 * @file EnemyLeave.cpp
 * @brief 敵の離脱パターン
 */

#include"Enemy.h"
#include"EnemyLeave.h"
#include"EnemyStandby.h"

Leave::Leave() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "limit", 10);
	GlobalVariables::GetInstance()->AddItem(groupName_, "distance", { 0,0,10 });
	ApplyGlobalVariables();
}

void Leave::ApplyGlobalVariables() {
	limit_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "limit");
	distance_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "distance");
}

Leave::~Leave() {}

	void Leave::Update([[maybe_unused]]Vector3 playerPos) {
	timer++;

	speed_ = distance_ / static_cast<float>(limit_);
	Matrix4 enemyMat = enemy_->GetWtf().matWorld;
	velocity_ = Matrix4::bVelocity(speed_, enemyMat);

	//座標に足す
	enemy_->Move(velocity_);

	if (timer > limit_) {
		//待機状態に戻る
		enemy_->TransitionTo(new Standby);
	}
}