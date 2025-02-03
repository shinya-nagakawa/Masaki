#pragma once
#include "../Base/EnemyBase.h"

/*HP半分以下時、特殊行動でステータス大幅強化*/

class BeastMan_Deer : public EnemyBase {
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">生成位置</param>
	/// <param name="kinds">種類</param>
	BeastMan_Deer(const CVector3D& pos, Kinds kinds);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BeastMan_Deer();

	class BeastMan_Deer_Special : public State<EnemyBase*> {
	private:
		const float m_specialTiming; //特殊行動のゴブリン生成のタイミング
		BeastMan_Deer* mp_owner;     //mp_ownerをBeastMan_Wolfクラスで上書き(BeastMan_Wolfの機能を使うため)
	public:
		BeastMan_Deer_Special(BeastMan_Deer*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
};