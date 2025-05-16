#pragma once

/*メニュー画面で使用する、現在の項目を指すカーソル*/

class Cursor {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Cursor();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Cursor();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理(画像)
	/// </summary>
	void Draw();

	/// <summary>
	/// 各要素のカーソルを表示する座標を設定
	/// </summary>
	/// <param name="pos">1つ目の要素の座標</param>
	/// <param name="interval">前の要素からの間隔</param>
	void SetCursorPos(CVector2D pos, float interval);
	/// <summary>
	/// 最大要素数を設定
	/// </summary>
	/// <param name="maxElement">最大要素数</param>
	void SetMaxElement(int maxElement);
	/// <summary>
	/// 現在指している項目の番号を返却
	/// </summary>
	/// <returns>現在の要素番号</returns>
	int GetCurrentElement() const;

private:
	CImage m_img;         //カーソルの画像
	int m_maxElement;     //最大要素数
	int m_currentElement; //現在指している項目
	std::unordered_map<int, CVector2D> m_posList; //項目毎のカーソルを表示する位置
};