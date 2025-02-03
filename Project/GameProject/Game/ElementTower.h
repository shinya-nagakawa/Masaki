#pragma once
#include "../Base/TowerBase.h"
#include "BuffDebuff.h"

/*属性タワー 機能的な違いがほとんどないため一括*/

//属性タワー毎に異なる要素
struct TowerData
{
	char ObjectEffect[32]; //オブジェクト用エフェクトの名前
	char AttackEffect[32]; //攻撃用エフェクトの名前
	char HitEffect[32];    //ヒット用エフェクトの名前
	char BrokenEffect[32]; //倒壊オブジェクト用のエフェクトの名前
	int EffectStart;       //エフェクトの開始フレーム
	int EffectEnd;         //エフェクトの終了フレーム
	int DebuffType;        //与えることのできるデバフ
	int DebuffEffect;      //デバフのかかるステータス
	float DebuffTime;      //デバフの時間
	float DebuffSize;      //デバフの倍率
};

class ElementTower : public TowerBase {
private:
	ObjectBase* mp_object_Effect; //オブジェクト用エフェクト
	ObjectBase* mp_attack_Effect; //攻撃開始用エフェクト
	ObjectBase* mp_hit_Effect;    //攻撃命中用エフェクト
	TowerData* mp_towerData;      //エフェクトやデバフのデータのポインタ
	BuffDebuff m_debuff;          //与えることのできるデバフ

	/// <summary>
	/// 攻撃
	/// </summary>
	virtual void Attack() override;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ElementTower(const CVector3D& pos, Kinds kinds);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ElementTower();
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Render() override;
	/// <summary>
	/// 指定した位置にヒットエフェクトを生成
	/// </summary>
	/// <param name="pos">生成したい位置</param>
	void NewHitEffect(const CVector3D& pos);
	/// <summary>
	/// デバフの倍率を設定(雷タワーのみ)
	/// </summary>
	/// <param name="enemyHP">敵の最大HP</param>
	void SetDebuffSize(float enemyHP);
	/// <summary>
	/// 与えることのできるデバフを返却
	/// </summary>
	/// <returns></returns>
	BuffDebuff GetDebuff() const;
	/// <summary>
	/// オブジェクトエフェクトを設定
	/// </summary>
	/// <param name="state">設定したいエフェクトにあった状態</param>
	void SetObjectEffect(TowerState state);



	//属性タワーの倒壊状態
	class Element_Broken : public Broken {
	private:
		ElementTower* mp_owner;
	public:
		Element_Broken(ElementTower*);
		virtual void Enter() override;
		virtual void Exit() override;
	};
};