/**
 * @file GameScene.h
 * @brief ゲームプレイシーン
 */
#pragma once
#include"SceneState.h"
#include"Sprite.h"
#include"Audio.h"
#include"GameCamera.h"
#include"CollisionManager.h"

using namespace std;

class GameScene : public SceneState {
public:
	GameScene();
	~GameScene();
	/**
	 * @brief 初期化
	*/
	void Initialize();
	/**
	 * @brief 更新
	*/
	void Update() override;
	/**
	 * @brief obj描画
	*/
	void ObjectDraw() override;
	/**
	 * @brief fbx描画
	*/
	void FbxDraw() override;
	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw() override;

private:
	/**
	 * @brief シーン移行
	*/
	void StateTransition() override;

private:
	//カメラ
	unique_ptr<GameCamera> gameCamera_ = nullptr;
};