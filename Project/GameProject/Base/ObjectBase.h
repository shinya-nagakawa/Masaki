#pragma once
#define GRAVITY (9.8f*0.001f)
#include "Task.h"

/*オブジェクトの基底クラス*/

class ObjectBase : public Task{
protected:
	CVector3D m_pos;   //座標
	CVector3D m_rot;   //回転値
	CVector3D m_vec;   //移動ベクトル
	CVector3D m_dir;   //前方向
	CVector3D m_scale; //拡縮
	//球、カプセル用
	float m_rad;       //半径
	//カプセル用
	float m_height;    //高さ
	CVector3D m_lineS; //始点
	CVector3D m_lineE; //終点

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type"></param>
	ObjectBase(int type);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjectBase();
	/// <summary>
	/// 更新処理(オブジェクト共通の処理)
	/// </summary>
	void Update() override;

public:
	//変化するステータスの列挙
	enum CheckItem {
		CT, //バフの時は短縮なので-、デバフの時は増加なので+
		HP,
		Speed,
		Power,
		Defence,
		Range,
	};
	//バフデバフのタイプ(同じバフデバフを付与できないよう)
	enum BuffDebuffType {
		Player_Buff,             //プレイヤーがタワーに与えるバフ
		Mutant_PowerBuff,        //ミュータントが行う特殊行動のバフ
		FireTower_DefenceDebuff, //炎タワーの防御デバフ
		IceTower_SpeedDebuff,    //氷タワーの速度デバフ
		ThunderTower_DOTDebuff,  //雷タワーの持続ダメージデバフ
	};
	//バフかデバフか確認用(もっといい方法があれば削除する)
	enum BufforDebuff {
		Buff,  //バフ
		Debuff //デバフ
	};

	/// <summary>
	/// 座標取得
	/// </summary>
	/// <returns>現在の座標</returns>
	const CVector3D& GetPos() const;
	/// <summary>
	/// 座標設定
	/// </summary>
	/// <param name="pos">設定する座標</param>
	void SetPos(const CVector3D& pos);
	/// <summary>
	/// 回転値取得
	/// </summary>
	/// <returns>現在の回転値</returns>
	const CVector3D& GetRot() const;
	/// <summary>
	/// 回転値設定
	/// </summary>
	/// <param name="rot">設定する回転値</param>
	void SetRot(const CVector3D& rot);
	/// <summary>
	/// 半径取得
	/// </summary>
	/// <returns>半径</returns>
	float GetRad() const;
	/// <summary>
	/// 高さを返却
	/// </summary>
	/// <returns>高さ</returns>
	float GetHeight() const;
	/// <summary>
	/// 始点取得
	/// </summary>
	/// <returns>カプセルに使う始点</returns>
	const CVector3D& GetLineS() const;
	/// <summary>
	/// 終点取得
	/// </summary>
	/// <returns>カプセルに使う終点</returns>
	const CVector3D& GetLineE() const;
	/// <summary>
	/// 正面方向を取得
	/// </summary>
	/// <returns></returns>
	CVector3D GetForward() const;

	/// <summary>
	/// モデルの透明度を設定
	/// </summary>
	/// <param name="model">透明度を設定するモデル</param>
	/// <param name="alpha">設定したい透明度</param>
	void SetTransparency(CModel* model, float alpha);
};