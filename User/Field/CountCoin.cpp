#include "CountCoin.h"
#include"SpriteLoader.h"
using namespace MyEngine;

void CountCoin::Initialize()
{
	count = std::make_unique<Sprite>();
	count->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("nums.png"));
	count->SetPozition({ 10.0f, 100.0f });
	count->SetTexSize({ 64.0f,64.0f });
	count->SetSize({ 64.0f,64.0f });

	count->Update();
}

void CountCoin::Draw()
{
	count->Draw();
}
