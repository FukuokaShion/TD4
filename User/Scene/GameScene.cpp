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

// 初期化
void GameScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<TGameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);

	// カメラセット
	FBXObject3d::SetCamera(gameCamera_.get());

	// プレイヤー
	player_ = make_unique<Player::Main>();
	player_->Initialize();

	// 当たり判定マネージャー初期化
	CollisionManager::GetInstance()->Initialize();
}

GameScene::~GameScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
	CollisionManager::GetInstance()->Finalize();
}

// 更新
void GameScene::Update() {
	gameCamera_->SetCameraPos({
	    player_->GetPos().x,
	    player_->GetPos().y + 3,
	    player_->GetPos().z - 6,
	});
	gameCamera_->Update();
	player_->Update();
	CollisionManager::GetInstance()->CheakAllCol();
}

void GameScene::ObjectDraw() {

#ifdef _DEBUG
	CollisionManager::GetInstance()->DrawCollider();
#endif
}

void GameScene::FbxDraw() { player_->FbxDraw(); }

void GameScene::SpriteDraw() {}

void GameScene::StateTransition() {}