/**
 * @file TutorialField.cpp
 * @brief チュートリアルシーンのステージ描画
 */

#include"TutorialField.h"
#include"SpriteLoader.h"

TutorialField::TutorialField() {

}

void TutorialField::Initialize() {
	scarecrow_ = std::make_unique<Scarecrow>();
	scarecrow_->Initialize();
	Vector3 scarecrowNewPos = { 23,0,-12 };
	scarecrow_->SetPos(scarecrowNewPos);

	cameraBoard_ = make_unique<Signboard>();
	cameraBoard_->Initialize(SpriteLoader::TUTORIAL_CAMERA);
	cameraBoard_->SetPos({ 14,0,-32 });
	cameraBoard_->SetRota({ 0,0,0 });

	attackBoard_ = make_unique<Signboard>();
	attackBoard_->Initialize(SpriteLoader::TUTORIAL_ATTACK);
	attackBoard_->SetPos({ 26,0,-24 });
	attackBoard_->SetRota({ 0,0,0 });

	jampBoard_ = make_unique<Signboard>();
	jampBoard_->Initialize(SpriteLoader::TUTORIAL_JUMP);
	jampBoard_->SetPos({36,0,-6});
	jampBoard_->SetRota({0,0,0});

	rollingBoard_ = make_unique<Signboard>();
	rollingBoard_->Initialize(SpriteLoader::TUTORIAL_ROLLING);
	rollingBoard_->SetPos({ 11,0,-11 });
	rollingBoard_->SetRota({ 0,0,0 });

	nextBoard_ = make_unique<Signboard>();
	nextBoard_->Initialize(SpriteLoader::TUTORIAL_NEXT);
	nextBoard_->SetPos({ 27,0,4 });
	nextBoard_->SetRota({ 0,0,0 });

	moveBoard_ = make_unique<Signboard>();
	moveBoard_->Initialize(SpriteLoader::TUTORIAL_MOVE);
	moveBoard_->SetPos({ 1.5f,0,-47 });
	moveBoard_->SetRota({ 0,0,0 });


	//背景
	skydomeMD_ = Model::LoadFromOBJ("skydome");
	skydome_ = Object3d::Create();
	skydome_->SetModel(skydomeMD_.get());
	skydome_->wtf.scale = (Vector3{ 1000, 1000, 1000 });
	skydome_->SetLightingActive(false);

	waterMD_ = Model::LoadFromOBJ("water");
	water_ = Object3d::Create();
	water_->SetModel(waterMD_.get());
	water_->wtf.position = { 0,-0.4f,0 };
	water_->wtf.scale = { 2,1,2 };

	coastMD_ = Model::LoadFromOBJ("coast");
	coast_ = Object3d::Create();
	coast_->SetModel(coastMD_.get());
	//coast_->wtf.scale = { 2,1,2 };
	coast_->wtf.rotation.y = 3.14f;

	rock01MD_ = Model::LoadFromOBJ("rock01");
	rock02MD_ = Model::LoadFromOBJ("rock02");

	for (int i = 0; i < 2; i++) {
		rock01_[i] = Object3d::Create();
		rock01_[i]->SetModel(rock01MD_.get());
		rock02_[i] = Object3d::Create();
		rock02_[i]->SetModel(rock02MD_.get());
	}

	rock01_[0]->wtf.position = { -50,0,240 };
	rock01_[0]->wtf.scale = { 1.4f,1,1 };
	rock01_[0]->wtf.rotation = { 0,0,0 };

	rock01_[1]->wtf.position = { -60,0,250 };
	rock01_[1]->wtf.scale = { 1,1.3f,1.2f };
	rock01_[1]->wtf.rotation = { 0,3.141592f / 2.0f,0 };

	rock02_[0]->wtf.position = { -70,0,250 };
	rock02_[0]->wtf.scale = { 2,2,2 };
	rock02_[0]->wtf.rotation = { 0,0,0 };

	rock02_[1]->wtf.position = { -40,0,240 };
	rock02_[1]->wtf.scale = { 1.5f,1.5f,1.5f };
	rock02_[1]->wtf.rotation = { 0,220.0f * 3.141592f / 180,0 };

	for (int i = 0; i < wallRockNum_; i++) {
		wallRock_[i] = Object3d::Create();
		wallRock_[i]->SetModel(rock01MD_.get());
	}
	wallRock_[0]->wtf.position = { -55,0,0 };
	wallRock_[0]->wtf.scale = { 2.0f,2.0f,4.0f };
	wallRock_[0]->wtf.rotation = { 0,0,0 };
	wallRock_[1]->wtf.position = { -53,0,-20 };
	wallRock_[1]->wtf.scale = { 2.0f,3.0f,5.0f };
	wallRock_[1]->wtf.rotation = { 0,-0.349066f,0 };
	wallRock_[2]->wtf.position = { -36,0,-42 };
	wallRock_[2]->wtf.scale = { 2.0f,5.0f,8.0f };
	wallRock_[2]->wtf.rotation = { 0,-0.715585f,0 };
	wallRock_[3]->wtf.position = { 0,0,-60 };
	wallRock_[3]->wtf.scale = { 12.0f,6.0f,2.0f };
	wallRock_[3]->wtf.rotation = { 0,0,0 };
	wallRock_[4]->wtf.position = { 36,0,-42 };
	wallRock_[4]->wtf.scale = { 2.0f,5.0f,8.0f };
	wallRock_[4]->wtf.rotation = { 0,0.715585f,0 };
	wallRock_[5]->wtf.position = { 53,0,-20 };
	wallRock_[5]->wtf.scale = { 2.0f,3.0f,5.0f };
	wallRock_[5]->wtf.rotation = { 0,0.349066f,0 };
	wallRock_[6]->wtf.position = { 55,0,0 };
	wallRock_[6]->wtf.scale = { 2.0f,3.0f,4.0f };
	wallRock_[6]->wtf.rotation = { 0,0,0 };

	wallRock_[7]->wtf.position = { 56,0,10 };
	wallRock_[7]->wtf.scale = { 2.0f,2.0f,4.0f };
	wallRock_[7]->wtf.rotation = { 0,0,0 };

	wallRock_[8]->wtf.position = { -20,0,-56 };
	wallRock_[8]->wtf.scale = { 4.0f,5.5f,2.0f };
	wallRock_[8]->wtf.rotation = { 0,0,0 };
	
	wallRock_[9]->wtf.position = { 20,0,-56 };
	wallRock_[9]->wtf.scale = { 3.0f,5.3f,2.0f };
	wallRock_[9]->wtf.rotation = { 0,0,0 };
}

TutorialField::~TutorialField() {}

void TutorialField::Update() {
	scarecrow_->Update();
	jampBoard_->Update();
	jampBoard_->CheckCol(playerPos_);
	attackBoard_->Update();
	attackBoard_->CheckCol(playerPos_);
	rollingBoard_->Update();
	rollingBoard_->CheckCol(playerPos_);
	cameraBoard_->Update();
	cameraBoard_->CheckCol(playerPos_);
	nextBoard_->Update();
	nextBoard_->CheckCol(playerPos_);
	moveBoard_->Update();
	moveBoard_->CheckCol(playerPos_);

	skydome_->Update();
	water_->Update();
	coast_->Update();
	for (int i = 0; i < 2; i++) {
		rock01_[i]->Update();
		rock02_[i]->Update();
	}
	for (int i = 0; i < wallRockNum_; i++) {
		wallRock_[i]->Update();;
	}
}

void TutorialField::ObjDraw() {
	scarecrow_->Draw();
	jampBoard_->ObjDraw();
	attackBoard_->ObjDraw();
	rollingBoard_->ObjDraw();
	cameraBoard_->ObjDraw();
	nextBoard_->ObjDraw();
	moveBoard_->ObjDraw();

	skydome_->Draw();
	water_->Draw();
	coast_->Draw();
	for (int i = 0; i < 2; i++) {
		rock01_[i]->Draw();
		rock02_[i]->Draw();
	}
	for (int i = 0; i < wallRockNum_; i++) {
		wallRock_[i]->Draw();;
	}
}

void TutorialField::SpriteDraw() {
	jampBoard_->SpriteDraw();
	attackBoard_->SpriteDraw();
	rollingBoard_->SpriteDraw();
	cameraBoard_->SpriteDraw();
	nextBoard_->SpriteDraw();
	moveBoard_->SpriteDraw();
}