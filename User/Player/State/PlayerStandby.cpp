/**
 * @file PlayerStandby.cpp
 * @brief プレイヤーの待機パターン
 *        各行動後この状態になる
 */

#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"
#include"PlayerJump.h"

PlayerStandby::PlayerStandby() {
	player_->AnimationChange(Player::Animation::STAND);
}

void PlayerStandby::ApplyGlobalVariables() {

}

//待機
void PlayerStandby::Update() {
	stamina_->Update();
	StateTransition();
}

void PlayerStandby::StateTransition() {
	//ジャンプ
	if (Input::GetInstance()->PButtonTrigger(A)) {
		if(stamina_->Use(staminaCost::JUMP)) {
			player_->TransitionTo(new PlayerJump);
		}
	}
	//攻撃
	if (Input::GetInstance()->PButtonTrigger(RB)) {
		if (stamina_->Use(staminaCost::ATTACK)) {
			player_->TransitionTo(new PlayerAttack);
		}
	}
	//移動
	if (Input::GetInstance()->LeftStickInput()) {
		player_->TransitionTo(new PlayerMove);
	}
}