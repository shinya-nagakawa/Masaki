#pragma once
#include "../Base/ObjectBase.h"
#include "SkyBox.h"
#include "AttackZone.h"
#include "EnemyManager.h"

/*フィールド*/

class Field : public ObjectBase
{
private:
	CModelObj m_model;       //モデルオブジェクト
	SkyBox m_skyBox;         //スカイボックス
	AttackZone m_attackZone; //攻撃座標
	std::list<CVector3D> m_atackPosList[EnemyManager::m_maxEnemy]; //AttackZoneを設定するための座標のリスト(フィールド毎に変わる)

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
	/// モデルを返却
	/// </summary>
	/// <returns>自身のモデル</returns>
	CModel* GetModel() override {
		return &m_model;
	}
	//攻撃座標を取得
	AttackZone& GetAttackZone();
};

class Grass : public Task {
private:

	CTexture* m_grass_texture;
	std::vector<CVector3D> m_grassPositions;
	unsigned int m_shaderProgram;
	unsigned int m_vao, m_vbo;
	void GenerateGrassPositions();
	bool WriteFile(const char* posfile);
	bool ReadFile(const char* posfile);
public:
	Grass(const char* texture);
	Grass(const char* texture, const char* posfile);
	void Update();
	void Render();
};