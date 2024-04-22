/**
 * @file Player.h
 * @brief プレイヤー本体
 */
#pragma once
#include"FBXModel.h"
#include"FBXObject3d.h"
#include"PlayerState.h"

using namespace MyEngine;

namespace Player {
	class Main {
	public:
		//アニメーション番号
		enum Animation {
			AVOID,
			ATTACK,
			JUMP,
			JUMPATTACK,
			STAND,
			STUMB,
			DASH,
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
		void Update();
		/**
		 * @brief 描画
		*/
		void FbxDraw();
	private:
		//モデル
		std::unique_ptr<FBXModel> bodyModel_ = nullptr;
		std::unique_ptr<FBXObject3d> body_ = nullptr;
		//行動パターン
		std::unique_ptr<State> state_ = nullptr;
	};
}