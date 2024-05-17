#pragma once
#include <list>
#include <memory>
#include "CoinObject.h"
#include "Object3d.h"
#include "BaseFieldObject.h"
using namespace MyEngine;

class BaseFieldObjectManager
{
public:
	BaseFieldObjectManager();

	static BaseFieldObjectManager* GetInstance();

	static void CreateCoinObject(Model* Model, Vector3 Pos, Vector3 Scale);

	static void ManagerBaseFieldObject();
	static void Clear();

	static const std::list<std::unique_ptr<BaseFieldObject>>& GetBaseFieldObjectList() { return manageBaseFieldObjectList; };

protected:

	void Init();
	static std::list<std::unique_ptr<BaseFieldObject>> manageBaseFieldObjectList;

};
