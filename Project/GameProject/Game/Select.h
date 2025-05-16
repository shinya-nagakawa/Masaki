#pragma once
#include "../Base/ObjectBase.h"
#include "Fade.h"
#include "Cursor.h"

/*ゲームのモードを選択する画面*/

class Select : public ObjectBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Select();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Select();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:
	CImage m_textBox;     //テキストボックス
	CImage m_backGround;  //背景
	CFont m_text;         //文字データ
	Fade m_fade;          //フェードクラス
	Cursor m_cursor;      //カーソルクラス

	//選べるモード
	enum ModeSelect {
		eGame,     //ゲーム
		eTutorial, //チュートリアル
	};
};