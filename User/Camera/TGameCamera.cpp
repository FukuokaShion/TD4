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

	Camera::Update();
}

void TGameCamera::SetParentTF(const Transform& parentWTF) { 
	switch (cameraAngle) {
	case TGameCamera::Back:
		cameraEye_ = { 0, 6,-9};
		break;
	case TGameCamera::RightBack:
		cameraEye_ = { 5, 6,-8};
		break;
	case TGameCamera::LeftBack:
		cameraEye_ = {-5, 6,-8};
		break;
	default:
		break;
	}
	cameraTarget_ = {0, 2, 9};

	eye_ = cameraEye_;
	target_ = cameraTarget_;

	wtf = parentWTF;
}
