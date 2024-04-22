#pragma once
#include <list>
#include <memory>
#include "Object3d.h"
using namespace MyEngine;

enum struct ObjectTag
{
	NONE,
	COIN,
	GOAL
};

class BaseFieldObject
{
public:
	bool isDelete = false;

	virtual ~BaseFieldObject() {}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void ManagerBaseFieldObject();
	static void Clear();

	std::unique_ptr<Object3d> object = nullptr;

	ObjectTag tag = ObjectTag::NONE;

	static const std::list<std::unique_ptr<BaseFieldObject>>& GetBaseFieldObjectList() { return manageBaseFieldObjectList; };

protected:

	static std::list<std::unique_ptr<BaseFieldObject>> manageBaseFieldObjectList;
};

