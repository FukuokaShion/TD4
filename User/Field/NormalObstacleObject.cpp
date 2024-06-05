#include "NormalObstacleObject.h"

NormalObstacleObject::NormalObstacleObject(Model* Model, Vector3 Pos, Vector3 Scale, Vector3 Rotation)
{
	object = Object3d::Create();
	object->SetModel(Model);

	object->wtf.position = Pos;
	object->wtf.scale = Scale;
	object->wtf.rotation = Rotation;

	sphere = new BaseCollider;

	//半径セット
	sphere->SetRad(Scale.x);
	//中心座標
	sphere->SetCenter(Pos);
	//属性付与*1
	sphere->SetAttribute(Attribute::NormalObstacle);
	//当たり判定をマネージャにセット
	CollisionManager::GetInstance()->AddCollider(sphere);

	animationTimer = 0;
}

void NormalObstacleObject::Update()
{
	if (sphere->GetIsHit().playerBody) {
		animated = true;
	}

	if (animated)
	{
		object->wtf.rotation.x += 3.0f;
		object->wtf.position += Vector3(0, 0.3f, 0.3f);
		if (animationTimer > animationTime)
		{
			isDelete = true;
		}
		animationTimer++;
	}

	object->Update();
}

void NormalObstacleObject::Draw()
{
	object->Draw();
}
