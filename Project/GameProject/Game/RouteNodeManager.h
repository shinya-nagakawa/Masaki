#pragma once
#include "RouteNode.h"

/*�m�[�h�̊Ǘ�*/

class RouteNodeManager {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="field">�t�B�[���h�ԍ�</param>
	RouteNodeManager(int field);

	/// <summary>
	/// ���g�𐶐�/�ԋp(�V���O���g��)
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static RouteNodeManager* Getinstance();
	/// <summary>
	/// ���g���폜
	/// </summary>
	static void Clearinstance();

	/// <summary>
	/// �m�[�h���擾
	/// </summary>
	/// <param name="idx">�m�[�h�z��̓Y��</param>
	/// <returns>�m�[�h</returns>
	RouteNode* GetNode(int idx) const;
	/// <summary>
	/// �m�[�h�z��̗v�f�����擾
	/// </summary>
	/// <returns>�m�[�h�̗v�f��</returns>
	int GetNodeSize() const;

	/// <summary>
	/// �m�[�h2�Ԃ̃J�v�Z���Ƃ̓����蔻��
	/// </summary>
	/// <param name="pos">������s���I�u�W�F�N�g�̍��W</param>
	/// <param name="rad">������s���I�u�W�F�N�g�̔��a</param>
	/// <returns>�������Ă��邩</returns>
	bool Collision(CVector3D pos, float rad);

	/// <summary>
	/// �f�o�b�O�\��
	/// </summary>
	void Render();

private:
	static RouteNodeManager* instance; //�C���X�^���X
	std::vector<RouteNode*> m_nodes;   //�S�m�[�h�̔z��

	/// <summary>
	/// �f�o�b�O�\��
	/// </summary>
	/// <param name="">�\������m�[�h</param>
	void RenderNode(RouteNode*);
};