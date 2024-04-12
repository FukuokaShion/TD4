/**
 * @file TitleScene.cpp
 * @brief タイトルシーン
 */
#include"TitleScene.h"
#include"SceneManager.h"
#include"GameScene.h"
#include"SpriteLoader.h"

TitleScene::TitleScene() {}

void TitleScene::Initialize() {
	LightGroup::GetInstance()->ClearCircleShadow();
	//サウンド
	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("ocean.wav");

	pSourceVoice_ = audio_->PlayWave("ocean.wav");

	const float PI = 3.1415f;
	// カメラ生成
	camera_ = new Camera();
	camera_->Initialize(WinApp::window_width, WinApp::window_height);
	camera_->wtf.position = { 0.0f,6.0f,-7.0f };
	const Vector3 camDegree = { 10.0f,-25.0f,0.0f };
	camera_->wtf.rotation = { camDegree.x * PI / 180.0f , camDegree.y * PI / 180.0f,camDegree.z * PI / 180.0f };

	Object3d::SetCamera(camera_);
	FBXObject3d::SetCamera(camera_);

	basePic_ = std::make_unique<Sprite>();
	basePic_->Initialize(SpriteCommon::GetInstance());
	basePic_->SetSize({ WinApp::window_width,WinApp::window_height });

	startSelect_ = { 1185,327 };
	optionSelect_ = { 1185,490 };
	arrow_ = std::make_unique<Sprite>();
	arrow_->Initialize(SpriteCommon::GetInstance());
	arrow_->SetPozition(startSelect_);
	arrow_->SetSize({ 64,64 });

	basePic_->SetTextureIndex(SpriteLoader::TITLE);
	arrow_->SetTextureIndex(SpriteLoader::ARROW);

	field_ = std::make_unique<TitleField>();
	field_->Initialize();

	ship_ = std::make_unique<Ship>();
	ship_->Initialize({ -15,0,21 });

	option_ = std::make_unique<Option>();
	option_->Initialize();
	optionOpen_ = false;
	isStartSelect_ = true;

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	fbxObject3d_ = std::make_unique<FBXObject3d>();
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_.get());
	fbxObject3d_->PlayAnimation(4, 1.0f);
	fbxObject3d_->wtf.position = { -5,-0.35f,8 };
	circleShadow_ = new CircleShadow();
	circleShadow_->SetActive(true);
	circleShadow_->SetCasterPos(fbxObject3d_->wtf.position);
	LightGroup::GetInstance()->SetCircleShadow(circleShadow_);
}

TitleScene::~TitleScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
	audio_->StopWave(pSourceVoice_);
}

//更新
void TitleScene::Update() {
	if (optionOpen_) {
		//オプション画面
		option_->Update();
		if (Input::GetInstance()->PButtonTrigger(A) || Input::GetInstance()->PButtonTrigger(START)) {
			optionOpen_ = false;
		}
	}
	else {
		//スタート画面
		if (ship_->GetIsMoveShip() == false) {
			//選択変更
			if (Input::GetInstance()->LeftStickInput()) {
				if (Input::GetInstance()->GetLeftStickVec().y > 0) {
					arrow_->SetPozition(startSelect_);
					isStartSelect_ = true;
				}
				else if (Input::GetInstance()->GetLeftStickVec().y < 0) {
					arrow_->SetPozition(optionSelect_);
					isStartSelect_ = false;
				}
			}
			//実行
			if (Input::GetInstance()->PButtonTrigger(A)) {
				if (isStartSelect_) {
					sceneManager_->TransitionTo(SceneManager::SCENE::TUTORIAL);
				}
				else {
					optionOpen_ = true;
				}
			}
		}
		camera_->Update();
		field_->Update();
		ship_->Update();
		basePic_->Update();
		arrow_->Update();
		fbxObject3d_->Update();
	}
}


void TitleScene::ObjectDraw() {
	field_->Draw();
	ship_->Draw();
}

void TitleScene::FbxDraw() {
	fbxObject3d_->Draw();
}

void TitleScene::SpriteDraw() {
	if (optionOpen_) {
		option_->SpriteDraw();
	}else {
		basePic_->Draw();
		arrow_->Draw();
	}
}

void TitleScene::StateTransition() {
	if (fadeOutPos < ship_->GetPos().z) {
		sceneManager_->TransitionTo(SceneManager::SCENE::TUTORIAL);
	}
}