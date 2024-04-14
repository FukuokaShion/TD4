/**
 * @file GameScene.cpp
 * @brief ゲームプレイシーン
 */
#include "GameScene.h"
#include "Collision.h"
#include "Easing.h"
#include "FbxLoader.h"
#include "LightGroup.h"
#include "SceneManager.h"
#include "SpriteLoader.h"

GameScene::GameScene() {}

void GameScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<GameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);

	// 当たり判定マネージャー初期化
	CollisionManager::GetInstance()->Initialize();
}

GameScene::~GameScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
	CollisionManager::GetInstance()->Finalize();
}

// 更新
void GameScene::Update() {
	gameCamera_->Update();
	CollisionManager::GetInstance()->CheakAllCol();
}

void GameScene::ObjectDraw() {

#ifdef _DEBUG
	CollisionManager::GetInstance()->DrawCollider();
#endif
}

void GameScene::FbxDraw() {}

void GameScene::SpriteDraw() {}

void GameScene::StateTransition() {}