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
	ParticleManager::SetCamera(gameCamera_.get());

	// プレイヤー
	player_ = make_unique<Player::Main>();
	player_->Initialize();

	//地面
	modelGround_ = MyEngine::Model::LoadFromOBJ("Ground");
	ground_ = make_unique<Ground>(modelGround_.get(), Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 40.0f),gameCamera_.get());
	
	//フィールドマネージャー
	fieldManager_ = make_unique<FieldManager>();
	fieldManager_->Initialize();
	fieldManager_->Load("1");
	

	//パーティクル
	playerParticleManager_ = make_unique<PlayerParticleManager>();
	playerParticleManager_->Initialize();
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
	gameCamera_->SetParentTF(player_->GetWorldTransform());
	gameCamera_->Update();
	player_->Update();
  
	//引数ぶぶんを自機の中心座標でお願い
	playerParticleManager_->ParticleCreate(PlayerParticleManager::SMOKE, player_->GetWorldTransform().position);
	playerParticleManager_->ParticleCreate(PlayerParticleManager::BACKBOOST, player_->GetWorldTransform().position + Vector3{ 0,3,0 });
	playerParticleManager_->Update(player_->GetWorldTransform().position);
	ground_->Update();
	CollisionManager::GetInstance()->CheakAllCol();
}

void GameScene::ObjectDraw() {

	ground_->Draw();
	fieldManager_->Draw();
#ifdef _DEBUG
	CollisionManager::GetInstance()->DrawCollider();
#endif
}

void GameScene::FbxDraw() { 
	player_->FbxDraw(); 

}

void GameScene::SpriteDraw() {
	playerParticleManager_->Draw();
}

void GameScene::StateTransition() {}