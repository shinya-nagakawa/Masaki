#include "Cursor.h"

Cursor::Cursor()
	: m_img(COPY_RESOURCE("ArrowUI", CImage))
	, m_maxElement(0)
	, m_currentElement(0){
}

Cursor::~Cursor(){
}

void Cursor::Update(){
	//W�L�[�ŏ�
	if (PUSH(CInput::eUp)) {
		//���݂̗v�f����Ԑ擪�Ȃ�A��ԉ��ɐݒ�
		if (m_currentElement == 0) {
			m_currentElement = m_maxElement - 1;
		}
		//�����łȂ��Ȃ�A���̂܂܏��
		else {
			m_currentElement--;
		}
	}
	//S�L�[�ŉ�
	if (PUSH(CInput::eDown)) {
		//���݂̗v�f����ԍŌ�Ȃ�A��ԏ�ɐݒ�
		if (m_currentElement == m_maxElement - 1) {
			m_currentElement = 0;
		}
		//�����łȂ��Ȃ�A���̂܂܉���
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
	//�ŏ��̗v�f�͍��W�����̂܂ܑ��
	m_posList[0] = pos;
	//�ȍ~�̗v�f�́A���W��y�̒l�ɊԊu�̐��l�����Z�������̂�ݒ�
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
