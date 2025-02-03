#pragma once
#include "RouteNode.h"

/*�m�[�h�̊Ǘ�*/

class RouteNodeManager {
private:
	static RouteNodeManager* instance; //�C���X�^���X
	std::vector<RouteNode*> m_nodes;   //�S�m�[�h�̔z��

	/// <summary>
	/// �f�o�b�O�\��
	/// </summary>
	/// <param name=""></param>
	void RenderNode(RouteNode*);

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RouteNodeManager(int field);
	/// <summary>
	/// �f�o�b�O�\��
	/// </summary>
	void Render();
	/// <summary>
	/// ���g�𐶐�/�ԋp(�V���O���g��)
	/// </summary>
	/// <returns></returns>
	static RouteNodeManager* Getinstance();
	/// <summary>
	/// ���g���폜
	/// </summary>
	static void Clearinstance();
	/// <summary>
	/// �m�[�h2�Ԃ̃J�v�Z���Ƃ̓����蔻��
	/// </summary>
	/// <param name="pos">������s���I�u�W�F�N�g�̍��W</param>
	/// <param name="rad">������s���I�u�W�F�N�g�̔��a</param>
	/// <returns>�������Ă��邩</returns>
	bool Collision(CVector3D pos, float rad);
	/// <summary>
	/// �m�[�h���擾
	/// </summary>
	/// <param name="idx">�m�[�h�z��̓Y��</param>
	/// <returns></returns>
	RouteNode* GetNode(int idx) const;
	/// <summary>
	/// �m�[�h�z��̗v�f�����擾
	/// </summary>
	/// <returns></returns>
	int GetNodeSize() const;
};