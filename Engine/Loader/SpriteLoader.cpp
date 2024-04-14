/**
 * @file SpriteLoader.cpp
 * @brief スプライト読み込み
 */

#include"SpriteLoader.h"

void SpriteLoader::Load() {
	SpriteCommon::GetInstance()->Initialize();

	SpriteCommon::GetInstance()->LoadTexture(WHITE, "white.png");
	SpriteCommon::GetInstance()->LoadTexture(LOADING, "loading.png");
}