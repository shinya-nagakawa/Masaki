#pragma once
#include "../Base/ObjectBase.h"
#include "BuffDebuff.h"
#include "Fade.h"
#include "Cursor.h"

/*ゲーム開始前のバフ選択画面*/

class Menu : public ObjectBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Menu();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Menu();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:
	CImage m_buffUI;      //バフの解説画像
	CImage m_backGround;  //背景
	CFont m_text;         //文字データ

	BuffDebuff PowerBuff; //攻撃力バフ
	BuffDebuff CTBuff;    //CTバフ
	BuffDebuff RangeBuff; //射程バフ

	Fade m_fade;          //フェードクラス
	Cursor m_cursor;      //カーソルクラス

	//バフの種類
	enum BuffKinds {
		ePowerBuff, //攻撃力バフ
		eCTBuff,    //クールタイムバフ
		eRangeBuff, //射程バフ
	};
};