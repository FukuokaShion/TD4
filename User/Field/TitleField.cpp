/**
 * @file TitleField.cpp
 * @brief ゲームシーンのステージ描画
 */

#include"TitleField.h"

TitleField::TitleField() {

}

void TitleField::Initialize() {
	//obj
	skydomeMD_ = Model::LoadFromOBJ("skydome");
	skydome_ = Object3d::Create();
	skydome_->SetModel(skydomeMD_.get());
	skydome_->wtf.scale = (Vector3{ 1000, 1000, 1000 });
	skydome_->SetLightingActive(false);

	waterMD_ = Model::LoadFromOBJ("water");
	water_ = Object3d::Create();
	water_->SetModel(waterMD_.get());
	water_->wtf.scale = { 2,1,2 };

	coastMD_ = Model::LoadFromOBJ("coast");
	coast_ = Object3d::Create();
	coast_->SetModel(coastMD_.get());
	coast_->wtf.scale = { 2,1,2 };
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
}

TitleField::~TitleField() {
}

void TitleField::Update() {
	skydome_->Update();
	water_->Update();
	coast_->Update();
	for (int i = 0; i < 2; i++) {
		rock01_[i]->Update();
		rock02_[i]->Update();
	}
}

void TitleField::Draw() {
	skydome_->Draw();
	water_->Draw();
	coast_->Draw();
	for (int i = 0; i < 2; i++) {
		rock01_[i]->Draw();
		rock02_[i]->Draw();
	}
}