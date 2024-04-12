/**
 * @file ObjModelLoader.h
 * @brief objモデル読み込み
 */

#pragma once
#include"Model.h"
#include<string>
#include<map>

using string = std::string;
using namespace MyEngine;

class ObjModelLoader {
public:
	void Finalize();

	/**
	 * @brief インスタンス取得
	*/
	static ObjModelLoader* GetInstance();

	/**
	 * @brief モデル読み込み
	*/
	void LoadModel(const string& modelname);

	/**
	 * @brief モデル取得
	*/
	std::unique_ptr<Model> GetModel(const string& modelname);
private:
	std::map<string, std::unique_ptr<Model>> models_;
};