#include "NormalObstacleObject.h"

NormalObstacleObject::NormalObstacleObject(Model* Model, Vector3 Pos, Vector3 Scale, Vector3 Rotation)
{
	object = Object3d::Create();
	object->SetModel(Model);

	object->wtf.position = Pos;
	object->wtf.scale = Scale;
	object->wtf.rotation = Rotation;

	//sphere = new BaseCollider;

	////半径セット
	//sphere->SetRad(Scale.x);
	////中心座標
	//sphere->SetCenter(Pos);
	////属性付与*1
	////sphere->SetAttribute(Attribute::Goal);
	////当たり判定をマネージャにセット
	//CollisionManager::GetInstance()->AddCollider(sphere);
}

void NormalObstacleObject::Update()
{
	if (sphere->GetIsHit().playerBody) {
		isDelete = true;
	}

	object->Update();
}

void NormalObstacleObject::Draw()
{
	object->Draw();
}
