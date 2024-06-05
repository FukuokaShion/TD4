#include "CountCoin.h"
#include"SpriteLoader.h"
#include<stdio.h>
#include"Input.h"
using namespace MyEngine;

int32_t CountCoin::num = 99;

void CountCoin::Initialize()
{
	for (size_t i = 0; i < digit; i++)
	{
		count[i] = std::make_unique<Sprite>();
		count[i]->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("nums.png"));
		count[i]->SetPozition({ 20.0f+(40.0f*i), 50.0f});
		count[i]->SetTexSize({ 64.0f,64.0f });
		count[i]->SetSize({ 64.0f,64.0f });
		count[i]->Update();
	}
}

void CountCoin::Draw()
{
	if (num>99)
	{
		num = 0;
	}
	sprintf_s(strNum, sizeof(strNum), "%02d", num);
	for (size_t i = 0; i < digit; i++)
	{
		strNum[i] -= 48;
		count[i]->SetTexLeftTop({ 64.0f*strNum[i],0.0f});
		count[i]->Update();
		count[i]->Draw();
	}
}
