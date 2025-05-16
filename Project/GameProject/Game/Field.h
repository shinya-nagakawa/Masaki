#pragma once
#include "../Base/ObjectBase.h"
#include "SkyBox.h"
#include "Sea.h"
#include "AttackZone.h"
#include "EnemyManager.h"

/*フィールド*/

class Field : public ObjectBase{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Field();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Field();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render() override;
	/// <summary>
	/// モデルを取得
	/// </summary>
	/// <returns>自身のモデル</returns>
	CModel* GetModel() override {
		return &m_collisionModel;
	}

	//攻撃座標を取得
	AttackZone& GetAttackZone();

private:
	CModelObj m_model;          //モデルオブジェクト
	CModelObj m_collisionModel; //当たり判定用モデルオブジェクト
	SkyBox m_skyBox;            //スカイボックス
	Sea m_sea;                  //海
	AttackZone m_attackZone;    //攻撃座標
	std::list<CVector3D> m_atackPosList[EnemyManager::m_maxEnemy]; //AttackZoneを設定するための座標のリスト(フィールド毎に変わる)
};
