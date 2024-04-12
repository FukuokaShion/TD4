/**
 * @file Field.cpp
 * @brief ゲームシーンのステージ描画
 */

#include"Field.h"

Field::Field() {

}

void Field::Initialize() {
	//背景
	skydomeMD_ = Model::LoadFromOBJ("skydome");
	skydome_ = Object3d::Create();
	skydome_->SetModel(skydomeMD_.get());
	skydome_->wtf.scale = (Vector3{ 1000, 1000, 1000 });
	skydome_->SetLightingActive(false);

	floorMD_ = Model::LoadFromOBJ("floor");
	floor_ = Object3d::Create();
	floor_->SetModel(floorMD_.get());

	waterMD_ = Model::LoadFromOBJ("water");
	water_ = Object3d::Create();
	water_->SetModel(waterMD_.get());
	water_->wtf.scale = { 2,1,2 };

	rock01MD_ = Model::LoadFromOBJ("rock01");
	rock02MD_ = Model::LoadFromOBJ("rock02");

	for (int i = 0; i < 3; i++) {
		rock01_[i] = Object3d::Create();
		rock01_[i]->SetModel(rock01MD_.get());
		rock02_[i] = Object3d::Create();
		rock02_[i]->SetModel(rock02MD_.get());
	}

	float PI = 3.141592f;

	rock01_[0]->wtf.position = { 42,0,65 };
	rock01_[0]->wtf.scale = { 5,5,5 };
	rock01_[0]->wtf.rotation = { 0,0,0 };

	rock01_[1]->wtf.position = { 122,0,10 };
	rock01_[1]->wtf.scale = { 5,5,5 };
	rock01_[1]->wtf.rotation = { PI / 4,0,0 };

	rock01_[2]->wtf.position = { -26,0,-73 };
	rock01_[2]->wtf.scale = { 5,5,5 };
	rock01_[2]->wtf.rotation = { 0,0,0 };

	rock02_[0]->wtf.position = { -45,0,105 };
	rock02_[0]->wtf.scale = { 12,12,12 };
	rock02_[0]->wtf.rotation = { 0,0,0 };

	rock02_[1]->wtf.position = { 75,0,-75 };
	rock02_[1]->wtf.scale = { 10,10,10 };
	rock02_[1]->wtf.rotation = { 0,-3.0f * PI / 4.0f,0 };

	rock02_[2]->wtf.position = { -91,0,-49 };
	rock02_[2]->wtf.scale = { 8,8,8 };
	rock02_[2]->wtf.rotation = { 0,3.0f * PI / 20.0f,0 };
}

Field::~Field() {}

void Field::Update() {
	skydome_->Update();
	floor_->Update();
	water_->Update();
	for (int i = 0; i < 3; i++) {
		rock01_[i]->Update();
		rock02_[i]->Update();
	}
}

void Field::Draw() {
	skydome_->Draw();

	floor_->Draw();
	water_->Draw();

	for (int i = 0; i < 3; i++) {
		rock01_[i]->Draw();
		rock02_[i]->Draw();
	}
}