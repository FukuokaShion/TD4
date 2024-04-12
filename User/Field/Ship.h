/**
 * @file ship.h
 * @brief タイトルシーン
 */

#pragma once
#include "Object3d.h"
#include"Input.h"
#include"Sprite.h"

class Ship {
public:
	~Ship();

	/**
	 * @brief 初期化
	*/
	void Initialize(Vector3 createPos);

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief obj描画
	*/
	void Draw();

	/**
	 * @brief sprite描画
	*/
	void SpriteDraw();

	/**
	 * @brief 動き始める
	*/
	void Start() { isMoveShip_ = true; };

	/**
	 * @brief 座標取得
	*/
	Vector3 GetPos() { return ship_->wtf.position; };

	/**
	 * @brief 動き始めているか取得
	*/
	bool GetIsMoveShip() { return isMoveShip_; };

	/**
	 *  @brief 当たり判定
	*/
	void CheckCol(Vector3 playerPos);

private:
	std::unique_ptr<Object3d> ship_ = nullptr;
	std::unique_ptr<Model> shipMD_ = nullptr;
	std::unique_ptr<Sprite> pushY_ = nullptr;
	float shipAngle_;
	bool isMoveShip_;
	float shipSpeed_;
	int timer_;
	int limit_;
	const float drawDistance = 13.0f;
	bool isSpriteDraw_;
	bool isPlayerDraw_;
	//プレイヤー
	std::unique_ptr<Object3d> player_ = nullptr;
	std::unique_ptr<Model> playerMD_ = nullptr;

};