#pragma once

/*敵の移動に使用するノード*/

class RouteNode {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">ノード座標</param>
	RouteNode(const CVector3D& pos);

	/// <summary>
	/// 次のノードを配列へ追加
	/// </summary>
	/// <param name="">次のノードのポインタ</param>
	void LinkNode(RouteNode*);
	/// <summary>
	/// 次のノードを取得
	/// </summary>
	/// <param name="idx">次ノード配列の添字</param>
	/// <returns></returns>
	RouteNode* GetNext(int idx) const;
	/// <summary>
	/// 次ノード配列の要素数を取得
	/// </summary>
	/// <returns>次ノードの要素数</returns>
	int GetNextSize() const;
	/// <summary>
	/// 次のノードがまとめられた配列を取得
	/// </summary>
	/// <returns>ノード配列</returns>
	std::vector<RouteNode*> GetNextList() const;
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3D GetPos() const;

private:
	std::vector<RouteNode*> m_next;	//次のノード配列
	CVector3D m_pos; //座標
};