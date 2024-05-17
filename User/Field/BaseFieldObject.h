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

	
	std::unique_ptr<Object3d> object = nullptr;

	ObjectTag tag = ObjectTag::NONE;

};



