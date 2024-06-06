#include "TGameCamera.h"
#include "Player.h"
#include "Input.h"
#include "Easing.h"

using namespace MyEngine;
using namespace Player;

TGameCamera* TGameCamera::gameCamera_ = nullptr;

TGameCamera::TGameCamera() {}

void TGameCamera::Initialize(int window_width, int window_height) {
	Camera::Initialize(window_width, window_height);
	
}

void TGameCamera::Update() {
	if (isEase) {
		easeTimer_++;

		if (easeTimer_ >= easeTime_) {
			isEase = false;
			easeTimer_ = 0;
		}
	} 
	else {
		InputAngle();
	}

	Camera::Update();
}

void TGameCamera::InputAngle() {
	if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW)) {
		cameraAngle = Back;
		isEase = true;
	}

	if (Input::GetInstance()->TriggerKey(DIK_RIGHTARROW)) {
		cameraAngle = RightBack;
		isEase = true;
	}

	if (Input::GetInstance()->TriggerKey(DIK_LEFTARROW)) {
		cameraAngle = LeftBack;
		isEase = true;
	}

	switch (cameraAngle) {
	case TGameCamera::Back:
		if (Input::GetInstance()->TriggerKey(DIK_1)) {
			speedLv = Low;
			isEase = true;
		}

		if (Input::GetInstance()->TriggerKey(DIK_2)) {
			speedLv = Medium;
			isEase = true;
		}

		if (Input::GetInstance()->TriggerKey(DIK_3)) {
			speedLv = High;
			isEase = true;
		}
		break;
	case TGameCamera::RightBack:
		break;
	case TGameCamera::LeftBack:
		break;
	default:
		break;
	}
}

void TGameCamera::AngleUpdate() {
	if (isEase) {
		switch (cameraAngle) {
		case TGameCamera::Back:
			switch (speedLv) {
			case TGameCamera::Low:
				cameraEye_ =
				    MyEngine::Easing::OutQuadVec3(cameraEye_, {0, 4, -9}, easeTimer_ / easeTime_);
				cameraTarget_ =
				    MyEngine::Easing::OutQuadVec3(cameraTarget_, {0, 3, 9}, easeTimer_ / easeTime_);
				break;
			case TGameCamera::Medium:
				cameraEye_ =
				    MyEngine::Easing::OutQuadVec3(cameraEye_, {0, 8, -12}, easeTimer_ / easeTime_);
				cameraTarget_ =
				    MyEngine::Easing::OutQuadVec3(cameraTarget_, {0, 1, 9}, easeTimer_ / easeTime_);
				break;
			case TGameCamera::High:
				cameraEye_ =
				    MyEngine::Easing::OutQuadVec3(cameraEye_, {0, 10, -18}, easeTimer_ / easeTime_);
				cameraTarget_ =
				    MyEngine::Easing::OutQuadVec3(cameraTarget_, {0, 1, 9}, easeTimer_ / easeTime_);
				break;
			default:
				break;
			}
			break;
		case TGameCamera::RightBack:
			cameraEye_ =
			    MyEngine::Easing::OutQuadVec3(cameraEye_, {5, 6, -15}, easeTimer_ / easeTime_);
			cameraTarget_ =
			    MyEngine::Easing::OutQuadVec3(cameraTarget_, {0, 2, 9}, easeTimer_ / easeTime_);
			break;
		case TGameCamera::LeftBack:
			cameraEye_ =
			    MyEngine::Easing::OutQuadVec3(cameraEye_, {-5, 6, -15}, easeTimer_ / easeTime_);
			cameraTarget_ =
			    MyEngine::Easing::OutQuadVec3(cameraTarget_, {0, 2, 9}, easeTimer_ / easeTime_);
			break;
		default:
			break;
		}
	} else {
		switch (cameraAngle) {
		case TGameCamera::Back:
			switch (speedLv) {
			case TGameCamera::Low:
				cameraEye_ = {0, 4, -9};
				cameraTarget_ = {0, 3, 9};
				break;
			case TGameCamera::Medium:
				cameraEye_ = {0, 8, -12};
				cameraTarget_ = {0, 1, 9};
				break;
			case TGameCamera::High:
				cameraEye_ = {0, 10, -15};
				cameraTarget_ = {0, 1, 9};
				break;
			default:
				break;
			}
			break;
		case TGameCamera::RightBack:
			cameraEye_ = {5, 6, -15};
			cameraTarget_ = {0, 2, 9};
			break;
		case TGameCamera::LeftBack:
			cameraEye_ = {-5, 6, -15};
			cameraTarget_ = {0, 2, 9};
			break;
		default:
			break;
		}
	}

	eye_ = cameraEye_;
	target_ = cameraTarget_;
}

void TGameCamera::SetParentTF(const Transform& parentWTF) { 
	wtf = parentWTF;
}
