#pragma once
#include "BaseFieldObject.h"
#include "Model.h"
#include "Vector3.h"
using namespace MyEngine;
class CoinObject: public BaseFieldObject
{
public:

	CoinObject(Model* Model, Vector3 Pos, Vector3 Scale);

	void Update() override;

	void Draw() override;

	static void Spawn(Model* Model, Vector3 Pos, Vector3 Scale);

};

