#include "BuildMenu_UI.h"
#include "Player.h"
#include "../Base/CharaBase.h"
#include "../Base/TowerBase.h"

BuildMenu_UI::BuildMenu_UI() : ObjectBase(eUI)
	, mp_UIFrame(new UIFrame(u8"Frame")) //UI�t���[���𐶐�
	, mp_player(dynamic_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer)))
	, Arrow(COPY_RESOURCE("Icon_Arrow", CImage))
	, Cannon(COPY_RESOURCE("Icon_Cannon", CImage))
	, Fire(COPY_RESOURCE("Icon_Fire", CImage))
	, Ice(COPY_RESOURCE("Icon_Ice", CImage))
	, Thunder(COPY_RESOURCE("Icon_Thunder", CImage))
	, m_icon(COPY_RESOURCE("Icon", CImage))
	, m_kinds(-1){
	//���j���[�\���T�E���h���Đ�
	SOUND("OpenMenu")->Play();
	//UI�t���[���̎q��UIWindow�𐶐�
	UIBase* window = new UIWindow(mp_UIFrame, u8"Option", CVector2D::zero, 
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
/*
	m_icon.SetRect(0.0f, 0.0f, 256.0f, 256.0f);
	//UIImageButton���^���[���ɐ���
	new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Arrow", true,    //�|�^���[
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Arrow));
	//�`���[�g���A�����ł͂Ȃ��Ȃ�(�`���[�g���A�����͋|�^���[�̂ݐ����\)
	if (!CharaBase::GetIsTutorial()) {
		m_icon.SetRect(256.0f, 0.0f, 512.0f, 256.0f);
		new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Cannon", false,  //��C�^���[
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Cannon));
		m_icon.SetRect(512.0f, 0.0f, 768.0f, 256.0f);
		new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Fire", true,     //���^���[
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Fire));
		m_icon.SetRect(768.0f, 0.0f, 1024.0f, 256.0f);
		new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Ice", true,      //�X�^���[
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Ice));
		m_icon.SetRect(1024.0f, 0.0f, 1280.0f, 256.0f);
		new UIImageButton(m_icon, CVector2D(64.0f, 64.0f), window, u8"Tower_Thunder", false, //���^���[
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Thunder));
	}
*/
	
	//UIImageButton���^���[���ɐ���
	new UIImageButton(Arrow, CVector2D(64.0f, 64.0f), window, u8"Tower_Arrow", true,    //�|�^���[
		std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Arrow));
	//�`���[�g���A�����ł͂Ȃ��Ȃ�(�`���[�g���A�����͋|�^���[�̂ݐ����\)
	if (!CharaBase::GetIsTutorial()) {
		new UIImageButton(Cannon, CVector2D(64.0f, 64.0f), window, u8"Tower_Cannon", false,  //��C�^���[
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Cannon));
		new UIImageButton(Fire, CVector2D(64.0f, 64.0f), window, u8"Tower_Fire", true,     //���^���[
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Fire));
		new UIImageButton(Ice, CVector2D(64.0f, 64.0f), window, u8"Tower_Ice", true,      //�X�^���[
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Ice));
		new UIImageButton(Thunder, CVector2D(64.0f, 64.0f), window, u8"Tower_Thunder", false, //���^���[
			std::bind(&Player::SetTowerKinds, mp_player, (int)TowerBase::Kinds::Tower_Thunder));
	}
	
}

BuildMenu_UI::~BuildMenu_UI(){
	//UI�t���[�����폜
	delete mp_UIFrame;
}

void BuildMenu_UI::Update(){
}

void BuildMenu_UI::Draw(){
	//UI�t���[����`��
	mp_UIFrame->Draw();
}

void BuildMenu_UI::KindsCheck(int kinds){
	m_kinds = kinds;
}
