/**
 * @file Scarecrow.h
 * @brief チュートリアル用丸太
 */

#pragma once
#include "Object3d.h"
#include"CollisionPrimitive.h"
#include"CollisionManager.h"

class Scarecrow {
public:
	Scarecrow();
	~Scarecrow();

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

	/**
	 * @brief ヒット時処理
	*/
	void OnCollision();

	/**
	 * @brief 丸太の位置設定
	*/
	void SetPos(Vector3 newPos);

	/**
	 * @brief 丸太の位置取得
	*/
	Vector3 GetPos() {return obj_->wtf.position; };

	/**
	 * @brief 丸太の注視点座標取得
	*/
	Vector3 GetTargetPos() {return targetPos_; };

private:
	//丸太
	std::unique_ptr<Object3d> obj_;
	std::unique_ptr<Model> model_;


	Vector3 targetLocalPos_;
	Vector3 targetPos_;

	//当たり判定
	BaseCollider* sphere_;
	bool isHit_;
	int hitTimer_;
	const int limit_ = 24;
};