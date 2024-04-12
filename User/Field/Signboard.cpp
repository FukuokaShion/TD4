/**
 * @file Signboard.cpp
 * @brief チュートリアル看板
 */

#include"Signboard.h"
#include"SpriteLoader.h"
#include"Input.h"

Signboard::Signboard() {};
Signboard::~Signboard() {};

void Signboard::Initialize(uint32_t texNmb) {
	model_ = Model::LoadFromOBJ("signboard");
	obj_ = Object3d::Create();
	obj_->SetModel(model_.get());

	pushY_ = std::make_unique<Sprite>();
	pushY_->Initialize(SpriteCommon::GetInstance());
	pushY_->SetSize({ WinApp::window_width,WinApp::window_height });
	pushY_->SetTextureIndex(SpriteLoader::TUTORIAL_PUSHY);

	content_ = std::make_unique<Sprite>();
	content_->Initialize(SpriteCommon::GetInstance());
	content_->SetSize({ WinApp::window_width,WinApp::window_height });
	content_->SetTextureIndex(texNmb);

	isSpriteDraw_ = false;
	isContentDraw_ = false;
}

void Signboard::Update() {
	obj_->Update();
	pushY_->Update();
	content_->Update();
}

void Signboard::CheckCol(Vector3 playerPos) {
	Vector2 distance = { playerPos.x - obj_->wtf.position.x,playerPos.z - obj_->wtf.position.z };
	if (drawDistance > distance.length()) {
		isSpriteDraw_ = true;
		if (Input::GetInstance()->PButtonTrigger(Y)) {
			if (isContentDraw_) {
				isContentDraw_ = false;
			}else {
				isContentDraw_ = true;
			}
		}
	}else {
		isContentDraw_ = false;
		isSpriteDraw_ = false;
	}
}

void Signboard::ObjDraw() {
	obj_->Draw();
}

void Signboard::SpriteDraw() {
	if (isSpriteDraw_) {
		if(isContentDraw_){
			content_->Draw();
		}else {
			pushY_->Draw();
		}
	}
}