/**
 * @file Player.h
 * @brief プレイヤー本体
 */
#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include "PlayerState.h"
#include "CollisionPrimitive.h"

using namespace MyEngine;

namespace Player {
	class Main {
	public:
		//アニメーション番号
		enum Animation {
			ATTACK,
			JUMP,
			STUMB,
			STAND,
			JUMPATTACK,
			DASH,
			SLIDE,
			AVOID,
		};
		enum StateNum {
			DASH_STATE,
			JUMP_STATE,
			SLIDE_STATE,
		};
	public:
		Main();
		~Main();
		/**
		 * @brief 初期化
		*/
		void Initialize();
		/**
		 * @brief 更新
		*/
		void Update(const Transform& parentWTF);
		/**
		 * @brief 描画
		*/
		void FbxDraw();
		/**
		 * @brief 状態移行
		*/
		void TransitionTo(StateNum nextState);
		/**
		 * @brief アニメーション切り替え
		*/
		void AnimationChange(int animationNum = 0, float speed = 1.0f) { body_->PlayAnimation(animationNum, speed); };
		/**
		 * @brief 座標取得
		*/
		const Transform GetWorldTransform() { return body_->wtf; };

	private:
		// モデル
		std::unique_ptr<FBXModel> bodyModel_ = nullptr;
		std::unique_ptr<FBXObject3d> body_ = nullptr;
		Transform rocalWtf_;
		// 行動パターン
		std::unique_ptr<State> state_ = nullptr;
		//回転の最大
		float rotaMax_;
		//横移動の最大
		float moveMax_;
		//当たり判定
		BaseCollider* bodyCollider_ = nullptr;
		float colliderRad_;
		uint32_t spineBoneNum_;
	};
}