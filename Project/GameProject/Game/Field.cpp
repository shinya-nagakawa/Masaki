#include "Field.h"
#include "../Base/CharaBase.h"

Field::Field() : ObjectBase(eField) {
	m_scale = CVector3D(0.3f, 0.3f, 0.3f);
	//チュートリアルではないなら
	if (!CharaBase::GetIsTutorial()) {
		//通常のフィールドを読み込み
		m_model = COPY_RESOURCE("Field", CModelObj);
		m_collisionModel = COPY_RESOURCE("CollisionField", CModelObj);
		m_rot += CVector3D(0.0f, DtoR(90.0f), 0.0f);

		//攻撃座標を設定
		m_atackPosList[0].push_back(CVector3D(-30.8f, -0.3f, 24.4f));
		m_atackPosList[1].push_back(CVector3D(-27.5f, 0.0f, 28.0f));
		m_atackPosList[2].push_back(CVector3D(-33.6f, -0.4f, 21.8f));
		m_atackPosList[3].push_back(CVector3D(-26.3f, 0.3f, 31.0f));
		m_atackPosList[4].push_back(CVector3D(-36.4f, -0.7f, 20.5f));
		m_atackPosList[5].push_back(CVector3D(-25.5f, 0.3f, 34.3f));
		m_atackPosList[6].push_back(CVector3D(-39.3f, -0.9f, 19.6f));
		m_atackPosList[7].push_back(CVector3D(-25.7f, 0.1f, 36.7f));
		m_atackPosList[8].push_back(CVector3D(-42.0f, -0.6f, 19.2f));
		m_atackPosList[9].push_back(CVector3D(-25.8f, -0.2f, 39.4f));
	}
	//チュートリアルなら
	else {
		//チュートリアル用フィールドを読み込み
		m_model = COPY_RESOURCE("TutorialField", CModelObj);
		m_collisionModel = COPY_RESOURCE("CollisionTutorialField", CModelObj);
	}

	m_sea.InitWater();

	//攻撃範囲を設定
	m_attackZone.InitializeAttackPos(m_atackPosList);
}

Field::~Field() {
}

void Field::Render() {
	m_skyBox.Render();
	m_sea.RenderWater();
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_collisionModel.SetRot(m_rot);
	m_collisionModel.SetScale(m_scale);
	m_collisionModel.UpdateMatrix();
	m_model.Render();
	

	/*デバッグ 攻撃座標の表示*/
	//Utility::DrawSphere(CVector3D(-30.8f, -0.3f, 24.4f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-27.5f, 0.0f, 28.0f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-33.6f, -0.4f, 21.8f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-26.3f, 0.3f, 31.0f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-36.4f, -0.7f, 20.5f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-25.5f, 0.3f, 34.3f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-39.3f, -0.9f, 19.6f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-25.7f, 0.1f, 36.7f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-42.0f, -0.6f, 19.2f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-25.8f, -0.2f, 39.4f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
}

AttackZone& Field::GetAttackZone(){
	return m_attackZone;
}
