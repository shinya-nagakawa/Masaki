#include "Player_TD.h"
#include "Player.h"
#include "../Base/TowerBase.h"
#include "Tower_Arrow.h"
#include "Tower_Cannon.h"
#include "ElementTower.h"
#include "BuildMenu_UI.h"
#include "RouteNodeManager.h"

Player_TD::Player_TD()
	: m_isCanBuild(true)
	, mp_newTower(nullptr){
	m_stateList[Player::PlayerState::Idle].reset(new Idle(this));
	m_stateList[Player::PlayerState::Build].reset(new Build(this));
}

void Player_TD::Enter(){

}

void Player_TD::Update(){
	//状態毎の更新処理
	m_stateList[mp_player->GetState()]->Update();
}

void Player_TD::Exit(){
	//建造状態の時、建造を中断
	BuildInterruption();
}

void Player_TD::ChangeState(Player::PlayerState state){
	//変更前の状態の終了時処理呼び出し
	m_stateList[mp_player->GetState()]->Exit();
	//現在の状態に設定
	mp_player->SetState(state);
	//変更後の状態の開始時処理呼び出し
	m_stateList[mp_player->GetState()]->Enter();
}

void Player_TD::BuildInterruption(){
	//もし建造状態なら
	if (mp_player->GetState() == Player::PlayerState::Build) {
		//建てるタワーを選択中なら
		if (UI != nullptr) {
			//タワー建造メニューを削除
			UI.reset();
		}
		//タワーを建てようとしている途中なら
		if (mp_newTower != nullptr) {
			//建てようとしているタワーを削除
			mp_newTower->SetKill();
		}
		//建てるタワーの種類を初期化
		mp_player->SetTowerKinds(-1);
		//待機状態に移行
		mp_player->ChangeState(Player::PlayerState::Idle);
		//キャンセルサウンドを流す
		SOUND("Cansel")->Play();
	}
}

void Player_TD::SetUI(BuildMenu_UI* newUI){
	UI.reset(newUI);
}

TowerBase* Player_TD::GetNewTower(){
	return mp_newTower;
}

void Player_TD::SetNewTower(TowerBase* newTower){
	mp_newTower = newTower;
}

void Player_TD::NewTower(){
	//生成するタワーを分岐
	switch ((TowerBase::Kinds)mp_player->GetTowerKinds())
	{
	case TowerBase::Kinds::Tower_Arrow:
		mp_newTower = new Tower_Arrow(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), (TowerBase::Kinds)mp_player->GetTowerKinds());
		break;
	case TowerBase::Kinds::Tower_Cannon:
		mp_newTower = new Tower_Cannon(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), (TowerBase::Kinds)mp_player->GetTowerKinds());
		break;
	case TowerBase::Kinds::Tower_Fire:
	case TowerBase::Kinds::Tower_Ice:
	case TowerBase::Kinds::Tower_Thunder:
		mp_newTower = new ElementTower(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), (TowerBase::Kinds)mp_player->GetTowerKinds());
		break;
	default:
		break;
	}
}

bool Player_TD::GetIsCanBuild() const{
	return m_isCanBuild;
}

void Player_TD::SetIsCanBuild(bool isCanBuild){
	m_isCanBuild = isCanBuild;
}

void Player_TD::CheckBuild(){
	//タワーを建てられる状態で初期化
	m_isCanBuild = true;

	//敵の進行経路との判定
	if (RouteNodeManager* n = RouteNodeManager::Getinstance()) {
		m_isCanBuild = n->Collision(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), 3.0f);
	}

	//まだ建造可能なら
	if (m_isCanBuild == true) {
		//城周辺との判定
		ObjectBase* b = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCastle));
		//城が存在していたら
		if (b != nullptr) {
			//城とマウス座標との距離
			CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField));
			//チュートリアル中なら
			if (CharaBase::GetIsTutorial()) {
				//距離が5mより小さければ
				if (v.LengthSq() < 5.0f * 5.0f) {
					//タワーを建てられない
					m_isCanBuild = false;
				}
			}
			//チュートリアル中ではないなら
			else {
				//距離が26mより小さければ
				if (v.LengthSq() < 26.0f * 26.0f) {
					//タワーを建てられない
					m_isCanBuild = false;
				}
			}
		}
	}

	//まだ建造可能なら
	if (m_isCanBuild == true) {
		//チュートリアル中なら
		if (CharaBase::GetIsTutorial()) {
			//敵を取得できたら
			if (ObjectBase* b = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eEnemy))) {
				//敵とマウス座標との距離
				CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField));
				//距離が10m(弓タワーの射程)より大きければ
				if (v.LengthSq() > 10.0f * 10.0f) {
					//タワーを建てられない
					m_isCanBuild = false;
				}
			}
		}
	}

	//まだ建造可能なら
	if (m_isCanBuild == true) {
		//タワーのリストを取得
		auto list = TaskManager::GetInstance()->FindObjects(eTower);
		//リスト内のタワーとの当たり判定を行う
		for (auto& t : list) {
			TowerBase* b = static_cast<TowerBase*>(t);
			//指しているタワーが建てようとしているタワーなら以降の処理を行わない
			if (t == mp_newTower) {
				//タワークラスのフラグにも代入し関数を抜け出す(指しているタワーが自身の時点でリストの一番最後のため)
				mp_newTower->SetIsCanBuild(m_isCanBuild);
				return;
			}
			//指しているタワーとマウス座標との距離
			CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField));
			//距離が8mより小さければ
			if (v.LengthSq() < 8.0f * 8.0f) {
				//タワーを建てられない
				m_isCanBuild = false;
			}
		}
	}

	//タワークラスのフラグにも代入
	mp_newTower->SetIsCanBuild(m_isCanBuild);
}

void Player_TD::CheckTower(){
	//タワーのリストを取得
	auto list = TaskManager::GetInstance()->FindObjects(eTower);
	//タワーとマウスの当たり判定を行う
	for (auto& t : list) {
		TowerBase* tb = static_cast<TowerBase*>(t);
		if (CCollision::CollisionCapsule(tb->GetLineS(), tb->GetLineE(), tb->GetRad(), Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)),
			Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), 1.0f)) {

			//建造完了後状態なら
			if (tb->GetState() == TowerBase::TowerState::eState_BuildAfter) {
				//レベルアップできるなら
				if (tb->IsCanLevelUp()) {
					//Eキーでレベルアップ
					if (PUSH(CInput::eButton7)) {
						tb->LevelUp();
					}
				}
			}

			//倒壊状態なら
			else if (tb->GetState() == TowerBase::TowerState::eState_Broken) {
				//修復できるなら
				if (tb->IsCanRepair()) {
					//Rキーでタワーを修復
					if (PUSH(CInput::eButton8)) {
						tb->Repair();
					}
				}

				//Fキーでタワーを回収
				if (PUSH(CInput::eButton9)) {
					tb->Collect();
				}
			}
		}
	}
}
