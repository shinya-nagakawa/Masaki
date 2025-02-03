#pragma once
#include "../Base/EnemyBase.h"

/*移動中のみ特殊行動でステルス状態になり、ターゲット不可*/

class Vampire : public EnemyBase {
private:
	float m_specialDuration; //ステルス状態の継続時間

	/// <summary>
	/// ステルス状態の管理
	/// </summary>
	void ControlStealth();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">生成位置</param>
	/// <param name= "level">レベル</param>
	/// <param name="kinds">種類</param>
	/// <param name="leader">リーダー</param>
	Vampire(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Vampire();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 特殊効果の効果時間を設定
	/// </summary>
	/// <param name=""></param>
	void SetSpecialDuration(float DurationTime);

	class Vampire_Special : public State<EnemyBase*> {
	private:
		const float m_specialTiming; //特殊行動の半透明化のタイミング
		Vampire* mp_owner;           //mp_ownerをVampireクラスで上書き(Vampireの機能を使うため)
	public:
		Vampire_Special(Vampire*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
};