#pragma once
#include"Sprite.h"
#include<memory>
class CountCoin
{
public:
	void Initialize();

	void Draw();
private:
	std::unique_ptr<Sprite> count;
};

