/**
 * @file TutorialField.h
 * @brief チュートリアルシーンのステージ
 */

#pragma once
#include "Object3d.h"
#include"Scarecrow.h"
#include"Signboard.h"
#include"Ship.h"

using namespace std;

class TutorialField {
public:
	TutorialField();
	~TutorialField();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief obj描画
	*/
	void ObjDraw();

	/**
	 * @brief sprite描画
	*/
	void SpriteDraw();

	/**
	 * @brief 丸太の位置取得
	*/
	Vector3 GetScarecrowPos() { return scarecrow_->GetPos(); };

	/**
	 * @brief 丸太の注視点座標取得
	*/
	Vector3 GetScarecrowTargetPos() { return scarecrow_->GetTargetPos(); };

	/**
	 * @brief プレイヤー位置設定
	*/
	void SetPlayerPos(Vector3 playerPos) { playerPos_ = playerPos; };

private:
	Vector3 playerPos_ = { 0,0,0 };

	//オブジェクト
	unique_ptr<Scarecrow> scarecrow_ = nullptr;
	unique_ptr<Signboard> jampBoard_ = nullptr;
	unique_ptr<Signboard> attackBoard_ = nullptr;
	unique_ptr<Signboard> rollingBoard_ = nullptr;
	unique_ptr<Signboard> cameraBoard_ = nullptr;
	unique_ptr<Signboard> nextBoard_ = nullptr;
	unique_ptr<Signboard> moveBoard_ = nullptr;

	//背景や床
	unique_ptr<Object3d> skydome_ = nullptr;
	unique_ptr<Model> skydomeMD_ = nullptr;
	unique_ptr<Object3d> water_ = nullptr;
	unique_ptr<Model> waterMD_ = nullptr;
	unique_ptr<Object3d> coast_ = nullptr;
	unique_ptr<Model> coastMD_ = nullptr;
	unique_ptr<Object3d> rock01_[2];
	unique_ptr<Model> rock01MD_ = nullptr;
	unique_ptr<Object3d> rock02_[2];
	unique_ptr<Model> rock02MD_ = nullptr;
	const int wallRockNum_ = 10;
	unique_ptr<Object3d> wallRock_[10];
};