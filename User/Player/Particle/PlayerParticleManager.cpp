#include "PlayerParticleManager.h"


PlayerParticleManager::PlayerParticleManager()
{
}

PlayerParticleManager::~PlayerParticleManager()
{
}

void PlayerParticleManager::Initialize()
{
	smoke_ = make_unique<Smoke>();
	smoke_->Initialize();

	backBoost_ = make_unique<BackBoost>();
	backBoost_->Initialize();

}

void PlayerParticleManager::Update()
{
	smoke_->Update();
	backBoost_->Update();
}

void PlayerParticleManager::Draw()
{
	smoke_->Draw();
	backBoost_->Draw();
}

void PlayerParticleManager::ParticleCreate(uint32_t particleType, Vector3 createPos) {
	if (particleType == SMOKE) {
		smoke_->EffSummary(createPos);
	}else if (particleType == BACKBOOST) {
		backBoost_->EffSummary(createPos);
	}
}