#include "TGameCamera.h"
#include "Player.h"

TGameCamera::TGameCamera() {}

void TGameCamera::Initialize(int window_width, int window_height) {
	Camera::Initialize(window_width, window_height);

}

void TGameCamera::Update() { Camera::Update(); }

void TGameCamera::Rota() {}

void TGameCamera::SetCameraPos(const MyEngine::Vector3& playerPos) { wtf.position = playerPos; }
