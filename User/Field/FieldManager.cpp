#include "FieldManager.h"
#include"CoinObject.h"
#include"GoalObject.h"
void FieldManager::Initialize()
{
	models.insert(std::make_pair("coin", MyEngine::Model::LoadFromOBJ("collider")));
	models.insert(std::make_pair("goal", MyEngine::Model::LoadFromOBJ("goal")));
}


void FieldManager::Load(const std::string& num)
{
	jsonLoader_.reset(LevelLoader::LoadJson(num));
	// レベルデータからオブジェクトを生成、配置
	for (auto& objectData : jsonLoader_->objects)
	{
		// ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end())
		{
			model = it->second.get();
		}
		//コイン
		if (objectData.fileName == "coin")
		{
			//CoinObject::Spawn(model, objectData.translation, objectData.scaling);
		}
		//ゴール
		else if (objectData.fileName == "goal")
		{
			//CoinObject::Spawn(model, objectData.translation, objectData.scaling,objectData.rotation);
		}
	}
}
