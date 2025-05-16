#include "BuildMenu_UI.h"
#include "Player.h"
#include "../Base/CharaBase.h"
#include "../Base/TowerBase.h"

BuildMenu_UI::BuildMenu_UI() : ObjectBase(eUI)
	, mp_UIFrame(new UIFrame(u8"Frame")) //UIフレームを生成
	, mp_player(dynamic_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer)))
	, Arrow(COPY_RESOURCE("Icon_Arrow", CImage))
	, Cannon(COPY_RESOURCE("Icon_Cannon", CImage))
	, Fire(COPY_RESOURCE("Icon_Fire", CImage))
	, Ice(COPY_RESOURCE("Icon_Ice", CImage))
	, Thunder(COPY_RESOURCE("Icon_Thunder", CImage))
	, m_icon(COPY_RESOURCE("Icon", CImage))
	, m_kinds(-1){
	//メニュー表示サウンドを再生
	SOUND("OpenMenu")->Play();
	//UIフレームの子にUIWindowを生成
	UIBase* window = new UIWindow(mp_UIFrame, u8"Option", CVector2D::zero, 
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
/*
	m_icon.SetRect(0.0f, 0.0f, 256.0f, 256.0f);
	//UIImageButtonをタワー毎に生成
	new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Arrow", true,    //弓タワー
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Arrow));
	//チュートリアル中ではないなら(チュートリアル中は弓タワーのみ生成可能)
	if (!CharaBase::GetIsTutorial()) {
		m_icon.SetRect(256.0f, 0.0f, 512.0f, 256.0f);
		new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Cannon", false,  //大砲タワー
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Cannon));
		m_icon.SetRect(512.0f, 0.0f, 768.0f, 256.0f);
		new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Fire", true,     //炎タワー
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Fire));
		m_icon.SetRect(768.0f, 0.0f, 1024.0f, 256.0f);
		new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Ice", true,      //氷タワー
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Ice));
		m_icon.SetRect(1024.0f, 0.0f, 1280.0f, 256.0f);
		new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Thunder", false, //雷タワー
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Thunder));
	}
*/
	
	//UIImageButtonをタワー毎に生成
	new UIImageButton(Arrow, CVector2D(64.0f, 64.0f), window, u8"Tower_Arrow", true,    //弓タワー
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Arrow));
	//チュートリアル中ではないなら(チュートリアル中は弓タワーのみ生成可能)
	if (!CharaBase::GetIsTutorial()) {
		new UIImageButton(Cannon, CVector2D(64.0f, 64.0f), window, u8"Tower_Cannon", false,  //大砲タワー
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Cannon));
		new UIImageButton(Fire, CVector2D(64.0f, 64.0f), window, u8"Tower_Fire", true,     //炎タワー
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Fire));
		new UIImageButton(Ice, CVector2D(64.0f, 64.0f), window, u8"Tower_Ice", true,      //氷タワー
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Ice));
		new UIImageButton(Thunder, CVector2D(64.0f, 64.0f), window, u8"Tower_Thunder", false, //雷タワー
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Thunder));
	}
	
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
