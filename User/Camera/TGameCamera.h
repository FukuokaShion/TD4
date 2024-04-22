#pragma once
#include "Camera.h"
#include "Vector2.h"

class Main;

class TGameCamera : public MyEngine::Camera {
public:
	/**
	 * @brief 初期化
	 */
	TGameCamera();
	void Initialize(int window_width, int window_height) override;

	/**
	 * @brief 更新
	 */
	void Update() override;

	void SetCameraPos(const MyEngine::Vector3& playerPos);

private:
	/**
	 * @brief 回転
	 */
	void Rota();

private:
	Main* main_ = nullptr;
};
