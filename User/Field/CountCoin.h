#pragma once
#include"Sprite.h"
#include<memory>
class CountCoin
{
public:
	void Initialize();

	void Draw();
	static int32_t num;
private:
	const int32_t digit = 2;
	std::unique_ptr<Sprite> count[2];
	char strNum[3];
};

