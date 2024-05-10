#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "DirectXCommon.h"
#include "Matrix4.h"
#include "ParticleManager.h"
#include "Input.h"

#include"GameCamera.h"
#include "TGameCamera.h"
#include"CollisionManager.h"

#include "Smoke.h"
#include "BackBoost.h"

using namespace MyEngine;
using namespace std;

class PlayerParticleManager
{
public :
	enum : uint32_t{
		SMOKE,
		BACKBOOST
	};
public:
	PlayerParticleManager();
	~PlayerParticleManager();

	void Initialize();

	void Update(Vector3 PlayerPos);

	void Draw();

	void ParticleCreate(uint32_t particleType,Vector3 createPos);

private:
	unique_ptr<Smoke> smoke_ = nullptr;
	unique_ptr<BackBoost> backBoost_ = nullptr;

};

