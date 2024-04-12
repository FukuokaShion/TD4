/**
 * @file TitleField.h
 * @brief ゲームシーンのステージ
 */

#pragma once
#include "Object3d.h"
using namespace MyEngine;

class TitleField {
public:
	TitleField();
	~TitleField();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief 描画
	*/
	void Draw();
private:
	//背景や床
	std::unique_ptr<Object3d> skydome_ = nullptr;
	std::unique_ptr<Model> skydomeMD_ = nullptr;
	std::unique_ptr<Object3d> water_ = nullptr;
	std::unique_ptr<Model> waterMD_ = nullptr;
	std::unique_ptr<Object3d> coast_ = nullptr;
	std::unique_ptr<Model> coastMD_ = nullptr;

	std::unique_ptr<Object3d> rock01_[2];
	std::unique_ptr<Model> rock01MD_ = nullptr;
	std::unique_ptr<Object3d> rock02_[2];
	std::unique_ptr<Model> rock02MD_ = nullptr;
};