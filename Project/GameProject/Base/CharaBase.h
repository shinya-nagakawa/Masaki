#pragma once
#include "ObjectBase.h"
#include "../Game/CharaStatus.h"
#include "../Game/HPBar.h"

/*キャラクターの基底クラス*/

class BuffDebuff;

class CharaBase : public ObjectBase {
public:
	/// <summary>
	/// キャラ共通の更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// キャラ共通の描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// HPバーを取得
	/// </summary>
	/// <returns>HPバー</returns>
	HPBar& GetHPBar();

	/// <summary>
	/// 攻撃生成のタイミングを取得
	/// </summary>
	/// <returns>攻撃生成のタイミング</returns>
	int GetAttackTiming() const;

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="Power">攻撃をした者の攻撃力</param>
	/// <param name="Defence">攻撃を受けた者の防御力</param>
	/// <param name="Level_A">攻撃をした者のレベル</param>
	/// <param name="Level_D">攻撃を受けた者のレベル</param>
	void TakeDamage(float Power, float Defence, int Level_A, int Level_D);
	/// <summary>
	/// バフ/デバフを付与する
	/// </summary>
	/// <param name="">与えたいバフ/デバフ</param>
	void AddBuffDebuff(const BuffDebuff& buffdebuff, const CVector3D& pos);

	/// <summary>
	/// 死んでいるかを取得
	/// </summary>
	/// <returns>死んでいるか</returns>
	bool IsDeath() const;
	/// <summary>
	/// 当たり判定を行うか取得
	/// </summary>
	/// <returns>当たり判定を行うか</returns>
	bool GetIsCollision() const;
	/// <summary>
	/// 当たり判定を行うか設定
	/// </summary>
	/// <param name="isCollision">当たり判定を行うか</param>
	void SetIsCollision(bool isCollision);
	/// <summary>
	/// ステータスを返却
	/// </summary>
	/// <returns>自身のステータス</returns>
	const CharaStatus& GetStatus() const;

	/// <summary>
	/// 自身がバフやデバフを持っているか取得(持っていたらtrue)
	/// </summary>
	/// <returns>バフ/デバフがリスト内に存在するか</returns>
	bool GetIsHasBuffDebuff() const;

	/// <summary>
	/// チュートリアルか取得
	/// </summary>
	/// <returns>チュートリアルか</returns>
	const static bool GetIsTutorial();
	/// <summary>
	/// チュートリアルか設定
	/// </summary>
	/// <param name="isTutorial">チュートリアルか</param>
	static void SetIsTutorial(bool isTutorial);

	/// <summary>
	/// 次のステップへ
	/// </summary>
	void NextStep();
	/// <summary>
	/// 現在のステップを取得
	/// </summary>
	/// <returns>現在のステップ</returns>
	int GetStateStep() const;

protected:
	CharaStatus m_status;    //個別に持つステータス

	HPBar m_HPBar;           //HPバー
	CVector3D m_bar_pos;     //HPバーを表示させたい座標

	int m_attacktiming;      //攻撃を行うフレーム(プレイヤーと敵以外使わないので移動)

	bool m_isStan;           //硬直状態か
	bool m_kill;             //死亡状態か
	bool m_isCollision;      //当たり判定を行うか

	static bool m_isTutorial; //チュートリアル中か

	int m_statestep;         //状態管理用

	ObjectBase* m_effect;    //エフェクト用ポインタ

	std::list<BuffDebuff> m_BuffDebufflist; //持っているバフとデバフのリスト

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">タイプ</param>
	CharaBase(int type);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CharaBase();

private:
	/// <summary>
	/// バフとデバフの確認と反映
	/// </summary>
	void BuffDebuffCheck();
};
