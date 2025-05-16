#include "Cursor.h"

Cursor::Cursor()
	: m_img(COPY_RESOURCE("ArrowUI", CImage))
	, m_maxElement(0)
	, m_currentElement(0){
}

Cursor::~Cursor(){
}

void Cursor::Update(){
	//Wキーで上
	if (PUSH(CInput::eUp)) {
		//現在の要素が一番先頭なら、一番下に設定
		if (m_currentElement == 0) {
			m_currentElement = m_maxElement - 1;
		}
		//そうでないなら、そのまま上へ
		else {
			m_currentElement--;
		}
	}
	//Sキーで下
	if (PUSH(CInput::eDown)) {
		//現在の要素が一番最後なら、一番上に設定
		if (m_currentElement == m_maxElement - 1) {
			m_currentElement = 0;
		}
		//そうでないなら、そのまま下へ
		else {
			m_currentElement++;
		}
	}
}

void Cursor::Draw(){
	m_img.SetPos(m_posList[m_currentElement]);
	
	m_img.Draw();
}

void Cursor::SetCursorPos(CVector2D pos, float interval){
	//最初の要素は座標をそのまま代入
	m_posList[0] = pos;
	//以降の要素は、座標のyの値に間隔の数値を加算したものを設定
	for (int i = 1; i < m_maxElement; i++) {
		m_posList[i] = pos + CVector2D(0.0f, interval) * i;
	}
}

void Cursor::SetMaxElement(int maxElement){
	m_maxElement = maxElement;
}

int Cursor::GetCurrentElement() const{
	return m_currentElement;
}
