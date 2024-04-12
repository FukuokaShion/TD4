#pragma once
/**
 * @file Signboard.h
 * @brief チュートリアル看板
 */

#pragma once
#include "Object3d.h"
#include "Sprite.h"

class Signboard {
public:
	Signboard();
	~Signboard();
	/**
	 * @brief 初期化
	*/
	void Initialize(uint32_t texNmb);
	/**
	 * @brief 座標設定
	*/
	void SetPos(Vector3 pos) { obj_->wtf.position = pos; };
	/**
	 * @brief 角度設定
	*/
	void SetRota(Vector3 rota) { obj_->wtf.rotation = rota; };
	/**
	 * @brief 更新
	*/
	void Update();
	/**
	 * @brief オブジェクト描画
	*/
	void ObjDraw();
	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw();
	/**
	 * @brief スプライト表示判定
	*/
	void CheckCol(Vector3 playerPos);

private:
	std::unique_ptr<Object3d> obj_ = nullptr;
	std::unique_ptr<Model> model_ = nullptr;
	std::unique_ptr<Sprite> pushY_ = nullptr;
	std::unique_ptr<Sprite> content_ = nullptr;
	bool isSpriteDraw_;
	bool isContentDraw_;
	const float drawDistance = 3.0f;
};