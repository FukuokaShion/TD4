#pragma once
#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"

class TGameCamera : public MyEngine::Camera {
public:
	enum Angle {
		Back,
		RightBack,
		LeftBack,
	};

	/**
	 * @brief 初期化
	 */
	TGameCamera();
	void Initialize(int window_width, int window_height) override;

	/**
	 * @brief 更新
	 */
	void Update() override;

	void SetParentTF(const MyEngine::Transform& parentWTF);

private:
	Angle cameraAngle = Back;

	MyEngine::Vector3 cameraEye_;
	MyEngine::Vector3 cameraTarget_;
};
