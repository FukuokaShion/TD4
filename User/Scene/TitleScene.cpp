/**
 * @file TitelScene.cpp
 * @brief タイトルシーン
 */
#include"TitleScene.h"
#include"SceneManager.h"

#include"FbxLoader.h"
#include"SpriteLoader.h"
#include"LightGroup.h"

TitleScene::TitleScene() {}

// 初期化
void TitleScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<GameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);
	// カメラセット
	FBXObject3d::SetCamera(gameCamera_.get());
	Object3d::SetCamera(gameCamera_.get());
	ParticleManager::SetCamera(gameCamera_.get());

	//スプライト
	SpriteLoader* spriteLoader = SpriteLoader::GetInstance();
	titlePic_ = make_unique<Sprite>();
	titlePic_->Initialize(SpriteCommon::GetInstance(), spriteLoader->GetTextureIndex("title.png"));
}

TitleScene::~TitleScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void TitleScene::Update() {
	gameCamera_->Update();
	titlePic_->Update();

	StateTransition();
}

void TitleScene::ObjectDraw() {

}

void TitleScene::FbxDraw() {
}

void TitleScene::SpriteDraw() {
	titlePic_->Draw();
}

void TitleScene::StateTransition() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::SELECT);
	}
}