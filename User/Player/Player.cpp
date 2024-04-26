/**
 * @file Player.cpp
 * @brief プレイヤー本体
 */

#include"Player.h"
#include"PlayerDash.h"

using namespace Player;

Main::Main(){}
Main::~Main(){}

void Main::Initialize() {
	//モデル生成
	bodyModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	body_ = std::make_unique<FBXObject3d>();
	body_->Initialize();
	body_->SetModel(bodyModel_.get());
	body_->PlayAnimation(DASH, 3.0f);
	//ステート
	state_ = std::make_unique<Dash>();
	state_->Initialize();
}

void Main::Update() {
	state_->Update();
	body_->wtf.position += {0.0f, 0, 0.0f};
	body_->Update();
	
}

void Main::FbxDraw() {
	body_->Draw(); 
}

Vector3 Main::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;

	body_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = body_->wtf.matWorld.m[ 3 ][ 0 ];
	worldPos.y = body_->wtf.matWorld.m[ 3 ][ 1 ];
	worldPos.z = body_->wtf.matWorld.m[ 3 ][ 2 ];

	return worldPos;
}

const Vector3& Player::Main::GetPos() const { return body_->wtf.position; }
