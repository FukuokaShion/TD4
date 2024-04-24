/**
 * @file GameScene.cpp
 * @brief ゲームプレイシーン
 */

#include"GameScene.h"
#include"SceneManager.h"
#include"FbxLoader.h"
#include"SpriteLoader.h"
#include"Easing.h"
#include"Collision.h"
#include"LightGroup.h"
#include"Object3D.h"
#include"Model.h"
#include"BaseFieldObject.h"
#include"CoinObject.h"

GameScene::GameScene() {}

// 初期化
void GameScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<TGameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);

	// カメラセット
	FBXObject3d::SetCamera(gameCamera_.get());
	Object3d::SetCamera(gameCamera_.get());

	// プレイヤー
	player_ = make_unique<Player::Main>();
	player_->Initialize();

	//地面
	modelGround_ = MyEngine::Model::LoadFromOBJ("Ground");
	ground_ = make_unique<Ground>(modelGround_.get(), Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 40.0f));
	modelCoin = MyEngine::Model::LoadFromOBJ("collider");

	CoinObject::Spawn(modelCoin.get(), Vector3(-10.0f, 3.0f, 10.0f), Vector3(1.0f, 1.0f, 1.0f));
	CoinObject::Spawn(modelCoin.get(), Vector3(	-5.0f, 3.0f, 10.0f), Vector3(1.0f, 1.0f, 1.0f));
	CoinObject::Spawn(modelCoin.get(), Vector3(	 0.0f, 3.0f, 10.0f), Vector3(1.0f, 1.0f, 1.0f));
	CoinObject::Spawn(modelCoin.get(), Vector3(	 5.0f, 3.0f, 10.0f), Vector3(1.0f, 1.0f, 1.0f));
	CoinObject::Spawn(modelCoin.get(), Vector3(	10.0f, 3.0f, 10.0f), Vector3(1.0f, 1.0f, 1.0f));

	// 当たり判定マネージャー初期化
	CollisionManager::GetInstance()->Initialize();
}

GameScene::~GameScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
	CollisionManager::GetInstance()->Finalize();
	BaseFieldObject::Clear();
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
	ground_->Update();
	CollisionManager::GetInstance()->CheakAllCol();
}

void GameScene::ObjectDraw() {

	ground_->Draw();
	BaseFieldObject::ManagerBaseFieldObject();

#ifdef _DEBUG
	CollisionManager::GetInstance()->DrawCollider();
#endif
}

void GameScene::FbxDraw() { player_->FbxDraw(); }

void GameScene::SpriteDraw() {}

void GameScene::StateTransition() {}