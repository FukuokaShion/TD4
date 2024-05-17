#include "GoalObject.h"

GoalObject::GoalObject(Model* Model, Vector3 Pos, Vector3 Scale, Vector3 Rotation)
{
	object = Object3d::Create();
	object->SetModel(Model);

	object->wtf.position = Pos;
	object->wtf.scale = Scale;
	object->wtf.rotation = Rotation;

	tag = ObjectTag::GOAL;
}

void GoalObject::Update()
{
	object->Update();
}

void GoalObject::Draw()
{
	object->Draw();
}
