#pragma once

/*�G�̈ړ��Ɏg�p����m�[�h*/

class RouteNode {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�m�[�h���W</param>
	RouteNode(const CVector3D& pos);

	/// <summary>
	/// ���̃m�[�h��z��֒ǉ�
	/// </summary>
	/// <param name="">���̃m�[�h�̃|�C���^</param>
	void LinkNode(RouteNode*);
	/// <summary>
	/// ���̃m�[�h���擾
	/// </summary>
	/// <param name="idx">���m�[�h�z��̓Y��</param>
	/// <returns></returns>
	RouteNode* GetNext(int idx) const;
	/// <summary>
	/// ���m�[�h�z��̗v�f�����擾
	/// </summary>
	/// <returns>���m�[�h�̗v�f��</returns>
	int GetNextSize() const;
	/// <summary>
	/// ���̃m�[�h���܂Ƃ߂�ꂽ�z����擾
	/// </summary>
	/// <returns>�m�[�h�z��</returns>
	std::vector<RouteNode*> GetNextList() const;
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3D GetPos() const;

private:
	std::vector<RouteNode*> m_next;	//���̃m�[�h�z��
	CVector3D m_pos; //���W
};