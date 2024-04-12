/**
 * @file PlayerUI.cpp
 * @brief プレイヤーのUI管理クラス
 */

#include"PlayerUI.h"
#include"SpriteLoader.h"

void PlayerUI::Initialize() {
	//スプライト
	base_ = new Sprite();
	base_->Initialize(SpriteCommon::GetInstance());
	base_->SetSize({ WinApp::window_width,WinApp::window_height });

	hpGauge_ = new Sprite();
	hpGauge_->Initialize(SpriteCommon::GetInstance());
	hpGauge_->SetPozition(hpGaugePos_);
	hpGauge_->SetSize({ hpGaugeSize_ });
	hpGauge_->SetColor(hpColor_);

	damageGauge_ = new Sprite();
	damageGauge_->Initialize(SpriteCommon::GetInstance());
	damageGauge_->SetPozition(hpGaugePos_);
	damageGauge_->SetSize({ hpGaugeSize_ });
	damageGauge_->SetColor(damageColor_);

	staminaGauge_ = new Sprite();
	staminaGauge_->Initialize(SpriteCommon::GetInstance());
	staminaGauge_->SetPozition(staminaGaugePos_);
	staminaGauge_->SetSize({ staminaGaugeSize_ });
	staminaGauge_->SetColor(staminaColor_);

	base_->SetTextureIndex(SpriteLoader::PLAYERUI);
	hpGauge_->SetTextureIndex(SpriteLoader::WHITE);
	damageGauge_->SetTextureIndex(SpriteLoader::WHITE);
	staminaGauge_->SetTextureIndex(SpriteLoader::WHITE);
}

PlayerUI::~PlayerUI() {
	delete hpGauge_;
	delete damageGauge_;
	delete base_;
	delete staminaGauge_;
}

void PlayerUI::Update(int damage, int hp,int stamina) {
	base_->Update();
	damageGauge_->SetSize({ static_cast<float>(hpGaugeOneSize_ * damage), hpGaugeSize_.y });
	hpGauge_->SetSize({ static_cast<float>(hpGaugeOneSize_ * hp), hpGaugeSize_.y });
	staminaGauge_->SetSize({ static_cast<float>(staminaGaugeOneSize_ * stamina), staminaGaugeSize_.y });
}

void PlayerUI::Draw() {
	base_->Draw();
	damageGauge_->Draw();
	hpGauge_->Draw();
	staminaGauge_->Draw();
}