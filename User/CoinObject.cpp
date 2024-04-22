#include "CoinObject.h"

CoinObject::CoinObject(Model* Model, Vector3 Pos, Vector3 Scale)
{
	object = Object3d::Create();
	object->SetModel(Model);

	object->wtf.position = Pos;
	object->wtf.scale = Scale;
}

void CoinObject::Update()
{

	object->wtf.rotation.y += 0.5f;

	object->Update();
}

void CoinObject::Draw()
{
	object->Draw();
}

void CoinObject::Spawn(Model* Model, Vector3 Pos, Vector3 Scale)
{
	manageBaseFieldObjectList.emplace_back(std::make_unique<CoinObject>(Model, Pos, Scale));
}
