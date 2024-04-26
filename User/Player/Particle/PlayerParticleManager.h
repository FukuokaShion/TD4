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

using namespace MyEngine;
using namespace std;

class PlayerParticleManager
{
public:
	PlayerParticleManager();
	~PlayerParticleManager();

	void Initialize();

	void Update(Vector3 PlayerPos);

	void Draw();

private:
	unique_ptr<Smoke> smoke_ = nullptr;

};

