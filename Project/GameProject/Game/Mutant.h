#pragma once
#include "../Base/EnemyBase.h"
#include "../Base/State.h"
#include "BuffDebuff.h"

/*特殊行動で範囲ダメージと範囲バフ*/

class Mutant : public EnemyBase {
private:
	BuffDebuff m_buff; //与えることのできるバフ

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">生成位置</param>
	/// <param name= "level">レベル</param>
	/// <param name="kinds">種類</param>
	/// <param name="leader">リーダー</param>
	Mutant(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Mutant();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 自分の与えることのできるバフを返却
	/// </summary>
	/// <returns></returns>
	BuffDebuff GetBuff() const;

	class Mutant_Special : public State<EnemyBase*> {
	private:
		const float m_specialTiming; //特殊行動の攻撃/バフ生成のタイミング
		Mutant* mp_owner;            //mp_ownerをMutantクラスで上書き(Mutantの機能を使うため)
	public:
		Mutant_Special(Mutant*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
};