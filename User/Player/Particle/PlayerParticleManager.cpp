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

	
}

void PlayerParticleManager::Update(Vector3 PlayerPos)
{
	smoke_->Update(PlayerPos);
	
}

void PlayerParticleManager::Draw()
{
	smoke_->Draw();
	
}
