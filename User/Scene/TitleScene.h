/**
 * @file TitleScene.h
 * @brief タイトルシーン
 */
#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"Sprite.h"
#include "Object3d.h"
#include"Audio.h"
#include"SceneState.h"
#include"TitleField.h"
#include"Ship.h"
#include"Option.h"

class TitleScene : public SceneState {
public:
	TitleScene();
	~TitleScene();
	/**
	 * @brief 初期化
	*/
	void Initialize();
	/**
	 * @brief 更新
	*/
	void Update() override;
	/**
	 * @brief obj描画
	*/
	void ObjectDraw() override;
	/**
	 * @brief fbx描画
	*/
	void FbxDraw() override;
	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw() override;
private:
	/**
	 * @brief シーン移行
	*/
	void StateTransition() override;
private:
	//サウンド
	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_ = nullptr;
	//オプション
	std::unique_ptr<Option> option_;
	//カメラ
	Camera* camera_ = nullptr;
	//画像
	std::unique_ptr<Sprite> basePic_;
	std::unique_ptr<Sprite> arrow_;
	//フィールド
	std::unique_ptr<TitleField> field_;
	//船
	const float fadeOutPos = 60.0f;
	std::unique_ptr<Ship> ship_;
	//キャラ
	std::unique_ptr<FBXModel> fbxModel_ = nullptr;
	std::unique_ptr<FBXObject3d> fbxObject3d_ = nullptr;
	CircleShadow* circleShadow_;
	//操作
	Vector2 startSelect_;
	Vector2 optionSelect_;
	bool optionOpen_;
	bool isStartSelect_;
};