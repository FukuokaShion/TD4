/**
 * @file Option.h
 * @brief オプション画面
 */
#pragma once
#include<memory>
#include"Sprite.h"

class Option {
public:
	Option();
	/**
	 * @brief 初期化
	*/
	void Initialize();
	/**
	 * @brief 更新
	*/
	void Update();
	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw();

private:
	bool isChangeSensitivity_;
	float sensitivityChangeSpeed;
	std::unique_ptr<Sprite> basePic_;
	std::unique_ptr<Sprite> rPic_;
	float rPosY;
	float rPosXStart;
	float rPosXMisalignment;
	float rPosXPerSensitivity;
};