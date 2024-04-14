/**
 * @file SpriteLoader.h
 * @brief スプライト読み込み
 */

#pragma once
#include"Sprite.h"

class SpriteLoader {
public:
	enum {
		WHITE,
		TITLE,
		LOADING,
		ENEMYUI,
		PLAYERUI,
		BOSSFELLED,
		YOUDIED,
		OPTION,
		RSTICK,
		TELOPBASE,
		PUSHA,
		ARROW,
		TUTORIAL_PUSHY,
		TUTORIAL_JUMP,
		TUTORIAL_ATTACK,
		TUTORIAL_ROLLING,
		TUTORIAL_CAMERA,
		TUTORIAL_NEXT,
		TUTORIAL_MOVE,
	};

	/**
	 * @brief 読み込み
	*/
	static void Load();
};