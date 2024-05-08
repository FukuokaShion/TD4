#include "TGameCamera.h"
#include "Player.h"
#include "Input.h"
#include "Easing.h"

using namespace MyEngine;
using namespace Player;

TGameCamera::TGameCamera() {}

void TGameCamera::Initialize(int window_width, int window_height) {
	Camera::Initialize(window_width, window_height);
	
}

void TGameCamera::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW)) {
		cameraAngle = Back;
	}
	if (Input::GetInstance()->TriggerKey(DIK_RIGHTARROW)) {
		cameraAngle = RightBack;
	}
	if (Input::GetInstance()->TriggerKey(DIK_LEFTARROW)) {
		cameraAngle = LeftBack;
	}

	switch (cameraAngle) {
	case TGameCamera::Back:
		if (Input::GetInstance()->TriggerKey(DIK_1)) {
			speedLv = Low;
		}
		if (Input::GetInstance()->TriggerKey(DIK_2)) {
			speedLv = Medium;
		}
		if (Input::GetInstance()->TriggerKey(DIK_3)) {
			speedLv = High;
		}
		break;
	case TGameCamera::RightBack:
		break;
	case TGameCamera::LeftBack:
		break;
	default:
		break;
	}

	Camera::Update();
}

void TGameCamera::SetParentTF(const Transform& parentWTF) { 
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
		cameraEye_ = { 5, 6,-8};
		cameraTarget_ = {0, 2, 9};
		break;
	case TGameCamera::LeftBack:
		cameraEye_ = {-5, 6,-8};
		cameraTarget_ = {0, 2, 9};
		break;
	default:
		break;
	}

	eye_ = cameraEye_;
	target_ = cameraTarget_;

	wtf = parentWTF;
}
