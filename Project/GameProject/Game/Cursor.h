#pragma once

/*���j���[��ʂŎg�p����A���݂̍��ڂ��w���J�[�\��*/

class Cursor {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Cursor();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Cursor();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��(�摜)
	/// </summary>
	void Draw();

	/// <summary>
	/// �e�v�f�̃J�[�\����\��������W��ݒ�
	/// </summary>
	/// <param name="pos">1�ڂ̗v�f�̍��W</param>
	/// <param name="interval">�O�̗v�f����̊Ԋu</param>
	void SetCursorPos(CVector2D pos, float interval);
	/// <summary>
	/// �ő�v�f����ݒ�
	/// </summary>
	/// <param name="maxElement">�ő�v�f��</param>
	void SetMaxElement(int maxElement);
	/// <summary>
	/// ���ݎw���Ă��鍀�ڂ̔ԍ���ԋp
	/// </summary>
	/// <returns>���݂̗v�f�ԍ�</returns>
	int GetCurrentElement() const;

private:
	CImage m_img;         //�J�[�\���̉摜
	int m_maxElement;     //�ő�v�f��
	int m_currentElement; //���ݎw���Ă��鍀��
	std::unordered_map<int, CVector2D> m_posList; //���ږ��̃J�[�\����\������ʒu
};