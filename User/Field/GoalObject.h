#pragma once
#include "BaseFieldObject.h"
class GoalObject : public BaseFieldObject
{
public:

	GoalObject(Model* Model, Vector3 Pos, Vector3 Scale, Vector3 Rotation);

	void Update() override;

	void Draw() override;
};

