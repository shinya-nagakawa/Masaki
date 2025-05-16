#pragma once
#include "EnemyManager.h"
#include <optional>

/*敵が重ならないよう管理するための座標 Field毎に設定/所持*/

class AttackZone {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	AttackZone();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~AttackZone();

	/// <summary>
	/// 座標を初期化
	/// </summary>
	/// /// <param name="list">フィールド毎に切り替わる座標のリスト</param>
	void InitializeAttackPos(const std::list<CVector3D> list[EnemyManager::m_maxEnemy]);
	/// <summary>
	/// 空いている座標を占領し、その座標を返す
	/// </summary>
	/// <param name="index">取得したい座標の番号</param>
	/// <returns>取得できるか</returns>
	std::optional<CVector3D> OccupyPoint(int index);
	/// <summary>
	/// 指定された座標の占領を解除
	/// </summary>
	/// <param name="index">座標の番号</param>
	/// <param name="pos">座標</param>
	void ReleaseAttackPos(int index, const CVector3D& pos);

private:
	//攻撃地点に必要な要素がまとめられた構造体
	struct AttackPos
	{
		CVector3D pos; //自身の止まる座標
		bool isTaken;  //占領されているか

		//コンストラクタ(引数は座標のみ)
		AttackPos(const CVector3D& pos) : pos(pos), isTaken(false) {}
	};
	std::list<AttackPos> m_attackZoneList[EnemyManager::m_maxEnemy]; //攻撃を開始する座標のリスト
};