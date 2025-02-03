#pragma once
#include "RouteNode.h"

/*ノードの管理*/

class RouteNodeManager {
private:
	static RouteNodeManager* instance; //インスタンス
	std::vector<RouteNode*> m_nodes;   //全ノードの配列

	/// <summary>
	/// デバッグ表示
	/// </summary>
	/// <param name=""></param>
	void RenderNode(RouteNode*);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RouteNodeManager(int field);
	/// <summary>
	/// デバッグ表示
	/// </summary>
	void Render();
	/// <summary>
	/// 自身を生成/返却(シングルトン)
	/// </summary>
	/// <returns></returns>
	static RouteNodeManager* Getinstance();
	/// <summary>
	/// 自身を削除
	/// </summary>
	static void Clearinstance();
	/// <summary>
	/// ノード2つ間のカプセルとの当たり判定
	/// </summary>
	/// <param name="pos">判定を行うオブジェクトの座標</param>
	/// <param name="rad">判定を行うオブジェクトの半径</param>
	/// <returns>当たっているか</returns>
	bool Collision(CVector3D pos, float rad);
	/// <summary>
	/// ノードを取得
	/// </summary>
	/// <param name="idx">ノード配列の添字</param>
	/// <returns></returns>
	RouteNode* GetNode(int idx) const;
	/// <summary>
	/// ノード配列の要素数を取得
	/// </summary>
	/// <returns></returns>
	int GetNodeSize() const;
};