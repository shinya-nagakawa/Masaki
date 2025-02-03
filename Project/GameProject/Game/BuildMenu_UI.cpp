#include "BuildMenu_UI.h"
#include "Player.h"
#include "../Base/TowerBase.h"

BuildMenu_UI::BuildMenu_UI() : ObjectBase(eUI)
	, mp_UIFrame(new UIFrame(u8"Frame")) //UIフレームを生成
	, mp_player(dynamic_cast<Player*>(TaskManager::FindObject(ePlayer)))
	, Arrow(COPY_RESOURCE("Icon_Arrow", CImage))
	, Cannon(COPY_RESOURCE("Icon_Cannon", CImage))
	, Fire(COPY_RESOURCE("Icon_Fire", CImage))
	, Ice(COPY_RESOURCE("Icon_Ice", CImage))
	, Thunder(COPY_RESOURCE("Icon_Thunder", CImage)){
	//UIフレームの子にUIWindowを生成
	UIBase* window = new UIWindow(mp_UIFrame, u8"Option", CVector2D::zero, 
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	//UIImageButtonをタワー毎に生成
	new UIImageButton(Arrow, CVector2D(64.0f, 64.0f), window, u8"Tower_Arrow", true,    //弓タワー
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Arrow));
	//new UIImageButton(Arrow, CVector2D(64.0f, 64.0f), window, u8"Tower_Arrow", true,    //弓タワー
		//KindsCheck((int)TowerBase::Kinds::Tower_Arrow));
	new UIImageButton(Cannon, CVector2D(64.0f, 64.0f), window, u8"Tower_Cannon", false,  //大砲タワー
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Cannon));
	new UIImageButton(Fire, CVector2D(64.0f, 64.0f), window, u8"Tower_Fire", true,     //炎タワー
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Fire));
	new UIImageButton(Ice, CVector2D(64.0f, 64.0f), window, u8"Tower_Ice", true,      //氷タワー
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Ice));
	new UIImageButton(Thunder, CVector2D(64.0f, 64.0f), window, u8"Tower_Thunder", false, //雷タワー
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Thunder));
}

BuildMenu_UI::~BuildMenu_UI(){
	//UIフレームを削除
	delete mp_UIFrame;
}

void BuildMenu_UI::Update(){
}

void BuildMenu_UI::Draw(){
	//UIフレームを描画
	mp_UIFrame->Draw();
}

void BuildMenu_UI::KindsCheck(int kinds){
	m_kinds = kinds;
}
