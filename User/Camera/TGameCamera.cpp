#include "TGameCamera.h"
#include "Player.h"
#include "Input.h"
#include "Easing.h"
#include <imgui.h>
#include "GlobalVariables.h"

using namespace MyEngine;
using namespace Player;

TGameCamera::TGameCamera() {}

void TGameCamera::Initialize(int window_width, int window_height) {
	Camera::Initialize(window_width, window_height);

	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	globalVariables->CreateGroup(groupName_);
	globalVariables->AddItem(groupName_, "lowEyePos_",       {0.0f, 4.0f, -9.0f});
	globalVariables->AddItem(groupName_, "lowTargetPos_",    {0.0f, 3.0f, 9.0f});
	globalVariables->AddItem(groupName_, "mediumEyePos_",    {0.0f, 8.0f, -12.0f});
	globalVariables->AddItem(groupName_, "mediumTargetPos_", {0.0f, 1.0f, 9.0f});
	globalVariables->AddItem(groupName_, "highEyePos_",      {0.0f, 10.0f, -18.0f});
	globalVariables->AddItem(groupName_, "highTargetPos_",   {0.0f, 1.0f, 9.0f});
	globalVariables->AddItem(groupName_, "lightEyePos_",     {5.0f, 6.0f, -15.0f});
	globalVariables->AddItem(groupName_, "lightTargetPos_",  {0.0f, 2.0f, 9.0f});
	globalVariables->AddItem(groupName_, "leftEyePos_",      {-5.0f, 6.0f, -15.0f});
	globalVariables->AddItem(groupName_, "leftTargetPos_",   {0.0f, 2.0f, 9.0f});
	ApplyGlobalVariables();
}

void TGameCamera::ApplyGlobalVariables() {
	lowEyePos_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "lowEyePos_");
	lowTargetPos_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "lowTargetPos_");
	mediumEyePos_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "mediumEyePos_");
	mediumTargetPos_ =
	    GlobalVariables::GetInstance()->GetVector3Value(groupName_, "mediumTargetPos_");
	highEyePos_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "highEyePos_");
	highTargetPos_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "highTargetPos_");
	lightEyePos_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "lightEyePos_");
	lightTargetPos_ =
	    GlobalVariables::GetInstance()->GetVector3Value(groupName_, "lightTargetPos_");
	leftEyePos_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "leftEyePos_");
	leftTargetPos_ = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "leftTargetPos_");
}

void TGameCamera::Update() {
	ApplyGlobalVariables();
	if (isEase) {
		easeTimer_++;

		if (easeTimer_ >= easeTime_) {
			isEase = false;
			easeTimer_ = 0;
		}
	} 
	else {
		InputAngle();

		AngleUpdate();
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
}

void TGameCamera::AngleUpdate() {
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

void TGameCamera::SetParentTF(const Transform& parentWTF) { 
	if (isEase) {
		switch (cameraAngle) {
		case TGameCamera::Back:
			switch (speedLv) {
			case TGameCamera::Low:
				endCameraEye_ = lowEyePos_;
				endCameraTarget_ = lowTargetPos_;
				cameraEye_ =
				    MyEngine::Easing::OutQuadVec3(cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
				cameraTarget_ =
				    MyEngine::Easing::OutQuadVec3(cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
				break;
			case TGameCamera::Medium:
				endCameraEye_ = mediumEyePos_;
				endCameraTarget_ = mediumTargetPos_;
				cameraEye_ =
				    MyEngine::Easing::OutQuadVec3(cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
				cameraTarget_ =
				    MyEngine::Easing::OutQuadVec3(cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
				break;
			case TGameCamera::High:
				endCameraEye_ = highEyePos_;
				endCameraTarget_ = highTargetPos_;
				cameraEye_ =
				    MyEngine::Easing::OutQuadVec3(cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
				cameraTarget_ =
				    MyEngine::Easing::OutQuadVec3(cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
				break;
			default:
				break;
			}
			break;
		case TGameCamera::RightBack:
			endCameraEye_ = lightEyePos_;
			endCameraTarget_ = lightTargetPos_;
			cameraEye_ =
			    MyEngine::Easing::OutQuadVec3(cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
			cameraTarget_ =
			    MyEngine::Easing::OutQuadVec3(cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
			break;
		case TGameCamera::LeftBack:
			endCameraEye_ = leftEyePos_;
			endCameraTarget_ = leftTargetPos_;
			cameraEye_ =
			    MyEngine::Easing::OutQuadVec3(cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
			cameraTarget_ =
			    MyEngine::Easing::OutQuadVec3(cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
			break;
		default:
			break;
		}

		eye_ = cameraEye_;
		target_ = cameraTarget_;
	} 
	else {
		cameraEye_ = endCameraEye_;
		cameraTarget_ = endCameraTarget_;

		eye_ = cameraEye_;
		target_ = cameraTarget_;
	}

	wtf = parentWTF;
}
