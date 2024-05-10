#include "Smoke.h"
#include <imgui.h>
#include "GlobalVariables.h"


void Smoke::Initialize()
{
	smokeParticle_ = make_unique<ParticleManager>();
	smokeParticle_->Initialize();
	smokeParticle_->LoadTexture("particle.png");

	//指定した名前のグループを作る
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	//第一引数名のグループ内に第二引数名の調整項目が無ければ、第三引数を初期値として登録
	GlobalVariables::GetInstance()->AddItem(groupName_, "randPos", 0.02f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "randVel", 0.02f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "randVelY", 0.0f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "startScale", 0.8f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "endScale", 0.4f);
	ApplyGlobalVariables();

}

void Smoke::Update(Vector3 PlayerPos)
{
	randPos = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randPos");
	randVel = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randVel");
	randVelY = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randVelY");
	startScale = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "startScale");
	endScale = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "endScale");

	if (isSmokeEffFlag_ == true) { smokeEffTimer_++; }
	if (smokeEffTimer_ <= 100 && smokeEffTimer_ >= 1) {
		//煙エフェクトのでる場所
		EffSummary(Vector3(PlayerPos.x, PlayerPos.y, PlayerPos.z));
	}
	if (smokeEffTimer_ >= 100) {
		smokeEffTimer_ = 0;
	}
	ImGui::Begin("Smoke");
	ImGui::Text("smokeEffTimer_:%d", smokeEffTimer_);
	ImGui::Text("isSmokeEffFlag_:%d", isSmokeEffFlag_);
	ImGui::End();

}

void Smoke::Draw()
{
	smokeParticle_->Draw();
}

void Smoke::ApplyGlobalVariables()
{
	
	//第一引数名のグループ内の第二引数名の調整項目の最新状態を読み込む
	randPos = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randPos");
	randVel = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randVel");
	randVelY = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randVelY");
	startScale = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "startScale");
	endScale = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "endScale");
}

void Smoke::EffSummary(Vector3 pos)
{
	//パーティクル範囲
	for (int i = 0; i < 20; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		Vector3 posGas{};
		posGas.x += (float)rand() / RAND_MAX * randPos - randPos / 2.0f;
		posGas.y += (float)rand() / RAND_MAX * randPos - randPos / 2.0f;
		posGas.z += (float)rand() / RAND_MAX * randPos - randPos / 2.0f;
		posGas += pos;
		//速度
		Vector3 velGas{};
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		velGas.x = (float)rand() / RAND_MAX * randVel - randVel / 2.0f;
		velGas.y = (float)rand() / RAND_MAX * randVelY - randVelY / 2.0f;
		velGas.z = (float)rand() / RAND_MAX * randVel - randVel / 0.2f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		Vector3 accGas{};
		accGas.x = (float)rand() / RAND_MAX * rnd_accGas - rnd_accGas / 2.0f;
		accGas.y = (float)rand() / RAND_MAX * rnd_accGas - rnd_accGas / 2.0f;
		//追加
		smokeParticle_->Add(60, posGas, velGas, accGas, startScale, endScale, { 1.0f,1.0f,1.0f,1.0f });
		smokeParticle_->Update();
	}
}

void Smoke::EffTrueCheck()
{
	isSmokeEffFlag_ = true;
}

void Smoke::EffFalseCheck()
{
	isSmokeEffFlag_ = false;
}
