#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "DirectXCommon.h"
#include "Matrix4.h"
#include "ParticleManager.h"
#include "Input.h"

using namespace MyEngine;
using namespace std;

class Smoke
{
private:
	

public:

	void Initialize();

	void Update(Vector3 PlayerPos);

	void Draw();

	void ApplyGlobalVariables();

	void EffSummary(Vector3 pos);

private:
	unique_ptr<ParticleManager> smokeParticle_;
	int smokeEffTimer_ = 0;
	bool isSmokeEffFlag_ = true;

	const float rnd_posGas = 0.0f;
	const float rnd_velGasz = 0.02f;
	const float rnd_accGas = 0.000001f;

	//グループ名、jsonファイル名になる
	const char * groupName_ = "smokeParticle";
	//調整項目例
	float randPos;
	float randVel;
	float randVelY;
	float startScale;
	float endScale;

};