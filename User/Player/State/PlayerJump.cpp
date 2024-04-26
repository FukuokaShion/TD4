/**
 * @file PlayerJump.cpp
 * @brief プレイヤーのジャンプパターン
 */
#include"Input.h"

#include"PlayerJump.h"
#include"Player.h"

using namespace Player;

Jump::Jump() {}

void Jump::Initialize() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	moveVector_ = { 0,0,0 };
	ApplyGlobalVariables();
}

void Jump::ApplyGlobalVariables() {
}

Jump::~Jump() {}

void Jump::Update(Main* player) {
	Rota();
	Move(player->GetWorldTransform());
	StateTransition(player);
}

void Jump::Rota() {
	rotaVector_ = { 0,0,0 };
	if (Input::GetInstance()->PushKey(DIK_A)) {
		rotaVector_ += {0, -rotaSpeed_, 0};
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		rotaVector_ += {0, rotaSpeed_, 0};
	}
}

void Jump::Move(Transform wtf) {
	Vector3 result;
	result = { 0,0,maxSpeed_ };
	moveVector_ = Matrix4::bVelocity(result, wtf.matWorld);
}

void Jump::StateTransition(Main* player) {
	player->AnimationChange(Main::Animation::DASH);
}