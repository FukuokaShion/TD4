/**
 * @file GameScene.h
 * @brief ゲームプレイシーン
 */
#pragma once
#include"SceneState.h"
#include"Sprite.h"
#include"Audio.h"
#include"GameCamera.h"
#include"Field.h"
#include"Player.h"
#include"Enemy.h"
#include"CollisionManager.h"
#include"Option.h"

using namespace std;

class GameScene : public SceneState {
public:
	GameScene();
	~GameScene();
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
	enum class State {
		game,
		clear,
		death,
		option,
	};
private:
	State state_;
	//サウンド
	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_ = nullptr;
	//メンバ変数
	//カメラ
	unique_ptr<GameCamera> gameCamera_ = nullptr;
	//フィールド
	unique_ptr<Field> field_ = nullptr;
	//プレイヤー
	unique_ptr<Player> player_ = nullptr;
	//エネミー
	unique_ptr<Enemy> enemy_ = nullptr;
	//画像
	unique_ptr<Sprite> pushB_;
	unique_ptr<Sprite> telopBase_;
	float telopBaseAddAlpha_;
	//クリア
	unique_ptr<Sprite> clear_;
	unique_ptr<Sprite> clearEffect_;
	int clearEffAddSize_;
	float clearEffSubtractAlpha_;
	//ゲームオーバー
	unique_ptr<Sprite> youDiedPic_;
	float youDiedAddAlpha_;
	//オプション
	unique_ptr<Option> option_ = nullptr;
};