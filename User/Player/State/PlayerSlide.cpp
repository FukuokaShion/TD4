/**
 * @file PlayerSlide.cpp
 * @brief プレイヤーのスライドパターン
 */
#include"Input.h"

#include"PlayerSlide.h"
#include"Player.h"

using namespace Player;

Slide::Slide() {}

void Slide::Initialize() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	moveVector_ = { 0,0,0 };
	ApplyGlobalVariables();
}

void Slide::ApplyGlobalVariables() {
}

Slide::~Slide() {}

void Slide::Update(Main* player) {
	Rota();
	Move(player->GetWorldTransform());
	StateTransition();
}

void Slide::Rota() {
	rotaVector_ = { 0,0,0 };
	if (Input::GetInstance()->PushKey(DIK_A)) {
		rotaVector_ += {0, -rotaSpeed_, 0};
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		rotaVector_ += {0, rotaSpeed_, 0};
	}
}

void Slide::Move(Transform wtf) {
	Vector3 result;
	result = { 0,0,maxSpeed_ };
	moveVector_ = Matrix4::bVelocity(result, wtf.matWorld);
}

void Slide::StateTransition() {
}