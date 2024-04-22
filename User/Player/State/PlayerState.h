/**
 * @file PlayerState.h
 * @brief プレイヤーのステートパターン基底
 */

#pragma once

namespace Player {
	class State {
	public:
		State();
		virtual ~State() {};
		/**
		 * @brief 初期化
		*/
		virtual void Initialize() = 0;
		/**
		 * @brief 更新
		*/
		virtual void Update() = 0;
	protected:
		/**
		 * @brief 状態移行
		*/
		virtual void StateTransition() = 0;
		/**
		 * @brief 調整項目の適用
		*/
		virtual void ApplyGlobalVariables() = 0;
	protected:

	};
}