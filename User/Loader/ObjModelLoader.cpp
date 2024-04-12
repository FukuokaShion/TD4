/**
 * @file ObjModelLoader.cpp
 * @brief objモデル読み込み
 */

#include"ObjModelLoader.h"

void ObjModelLoader::Finalize() {
	models_.clear();
}

ObjModelLoader* ObjModelLoader::GetInstance() {
	static ObjModelLoader instance;
	return &instance;
}

void ObjModelLoader::LoadModel(const string& modelname) {
	decltype(models_)::iterator it = models_.find(modelname);
	if (it == models_.end()) {
		models_[modelname] = Model::LoadFromOBJ(modelname);
	}
}

std::unique_ptr<Model> ObjModelLoader::GetModel(const string& modelname) {
	std::unique_ptr<Model> newModel = nullptr;
	decltype(models_)::iterator it = models_.find(modelname);
	if (it != models_.end()) {
		//newModel = it->second;
	}
	return newModel;
}