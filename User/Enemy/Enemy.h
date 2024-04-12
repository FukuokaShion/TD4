/**
 * @file Enemy.h
 * @brief　敵クラス本体
 */

#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"EnemyParticle.h"
#include"EnemyShootingParticle.h"
#include"EnemyDeathParticle.h"
#include"Audio.h"

#include"EnemyHp.h"
#include"EnemyState.h"
#include"EnemyBullet.h"
#include"EnemyBomb.h"
#include"EnemyEarthquake.h"
#include"EnemyUI.h"

class Enemy {
public:
	enum {
		DEATH,
		STUMB,
		SHOOT,
		STAND,
		ATTACK,
		BOMBSHOOT,
		EARTHQUAKE,
		HANDUP,
	};

	enum : uint32_t {
		ROOT,
		ROOTupper,
		hip,
		SPINE1,
		SPINE2,
		neck,
		HEAD,
		head_end,
		shoulder_R,
		ARM1_R,
		ARM2_R,
		HAND_R,
		HAND_R_END,
		shoulder_L,
		ARM1_L,
		ARM2_L,
		HAND_L,
		HAND_L_END,
		LEG1_R,
		LEG2_R,
		footR,
		footR_end,
		LEG1_L,
		LEG2_L,
		footL,
		footL_end,
	};

public:
	Enemy();
	~Enemy();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos);

	/**
	 * @brief FBX描画
	*/
	void Draw();

	/**
	 * @brief Obj描画
	*/
	void ObjDraw();

	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw();

	/**
	 * @brief パーティクル描画
	*/
	void ParticleDraw();

	/**
	 * @brief 状態移行
	*/
	void TransitionTo(EnemyState* state);

	/**
	 * @brief サウンド再生
	*/
	void PlayWave(const std::string& filename);

	/**
	 * @brief アニメーション切り替え
	*/
	void AnimationChange(int animationNum = 0, float speed = 1.0f) { fbxObject3d_->PlayAnimation(animationNum, speed); };

	/**
	 * @brief 座標移動
	*/
	void Move(Vector3 velocity) { fbxObject3d_->wtf.position += velocity; };

	/**
	 * @brief Y軸回転
	*/
	void RotaY(float theta) { fbxObject3d_->wtf.rotation.y = theta; };

	/**
	 * @brief 座標取得
	*/
	Transform GetWtf() { return fbxObject3d_->wtf; };

	/**
	 * @brief 被ダメ処理
	*/
	void OnCollision();

	/**
	 * @brief 生存フラグ
	 */
	bool IsLive() { return hp_->IsLive(); };

	/**
	 * @brief ゲッター
	 */
	int GetHp() { return hp_->GetHp(); };
	bool GetIsAttack() { return isAttack_; };
	int GetPower() { return power_; };


	/**
	 * @brief 押し出し時半径取得
	*/
	float GetRad() { return rad_; };

	/**
	 * @brief セッター
	 */
	void SetIsAttack(bool isAttack) { this->isAttack_ = isAttack; };
	void setPower(int power) { this->power_ = power; };

	/**
	 * @brief 弾生成
	 */
	void CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime = 0);
	/**
	 * @brief 弾生成時パーティクル
	 */
	void CreateBulletParticle(uint32_t boneName, int num);
	void CreateBulletParticle(uint32_t startBoneName, uint32_t endBoneName, int num);
	void CreateEarthquakeParticle(int num);
	/**
	 * @brief 爆弾登録
	 */
	void CreateBomb();

	void CreateEarthquake();
	bool JISIN = false;

	/**
	 * @brief 中心ボーン座標
	 */
	Vector3 GetCenterPos() { return fbxObject3d_->GetBonWorldPos(SPINE1); };
	/**
	 * @brief 手の座標取得
	 */
	Vector3 GetLeftHandPos() { return fbxObject3d_->GetBonWorldPos(HAND_L); };
	Vector3 GetRightHandPos() { return fbxObject3d_->GetBonWorldPos(HAND_R); };


private:
	//サウンド
	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_[10] = { 0 };

	//行動
	EnemyState* state_ = nullptr;

	//体力
	EnemyHp* hp_ = nullptr;

	//当たり判定
	const float rad_ = 1.3f;
	const int MaxColliderNum = 11;
	BaseCollider* colliders_[11];
	uint32_t boneNum_[11];

	//UI
	EnemyUI ui_;

	//モデル
	std::unique_ptr<FBXModel> fbxModel_ = nullptr;
	std::unique_ptr<FBXObject3d> fbxObject3d_ = nullptr;

	//弾リスト
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	std::list<std::unique_ptr<EnemyBomb>> bombs_;
	std::list<std::unique_ptr<Earthquake>> earthquakes_;

	//攻撃判定
	bool isAttack_;
	int power_;

	//パーティクル
	EnemyParticle* particle_ = nullptr;
	EnemyShootingParticle* bulletCreateParticle_ = nullptr;

	//死亡時
	const int DeathLimit = 210;
	int DeathTimer;
	const int DeathDrawTime_ = 90;
	EnemyDeathParticle* deatgparticle_ = nullptr;

	CircleShadow* circleShadow_;
};