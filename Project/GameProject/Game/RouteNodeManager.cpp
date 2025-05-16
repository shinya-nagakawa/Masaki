#include "RouteNodeManager.h"
#include "../Base/CharaBase.h"

RouteNodeManager* RouteNodeManager::instance = nullptr;

RouteNodeManager::RouteNodeManager(int field) {
	struct NodeData {
		CVector3D pos;           //�ʒu
		std::list<int> next_idx; //�ڑ��m�[�h�ԍ�
	};

	//�`���[�g���A���Ȃ�
	if (CharaBase::GetIsTutorial()) {
		//�m�[�h�z�u
		const NodeData node[] = {
			//���W�Ǝ��̍��W�̗v�f�� ����̏ꍇ��2�ȏ㏑��
			{CVector3D(  8.0f, 0.0f, -3.0f), {1}}, //0
			{CVector3D( -9.0f, 0.0f, -3.0f), {}},  //1
			
		};
		//���̔z�񂩂�m�[�h�z����\�z
		for (int i = 0; i < 2; i++) {
			m_nodes.push_back(new RouteNode(node[i].pos));
		}
		//�m�[�h��ڑ�
		for (int i = 0; i < 2; i++) {
			for (auto& n : node[i].next_idx) {
				m_nodes[i]->LinkNode(m_nodes[n]);
			}
		}
	}
	//�`���[�g���A���ł͂Ȃ��Ȃ�
	else {
		//�m�[�h�z�u
		const NodeData node[] = {
			//���W�Ǝ��̍��W�̗v�f�� ����̏ꍇ��2�ȏ㏑��

			{CVector3D(20.0f, 0.0f, -57.0f),{1}},     //0
			{CVector3D(20.0f, 0.0f, -46.0f),{2, 38}}, //1 ����_1
			{CVector3D(27.0f, 0.0f, -46.0f),{3}},     //2
			{CVector3D(38.0f, 0.0f, -46.0f),{4}},     //3
			{CVector3D(38.0f, 0.0f, -33.0f),{5,20}},  //4 ����_2
			{CVector3D(50.0f, 0.0f, -27.0f),{6}},     //5
			{CVector3D(50.0f, 0.0f, -13.0f),{7}},     //6
			{CVector3D(40.0f, 0.0f, -13.0f),{8}},     //7
			{CVector3D(40.0f, 0.0f,  -6.0f),{9}},     //8
			{CVector3D(40.0f, 0.0f,   5.0f),{10,24}}, //9 ����_3
			{CVector3D(40.0f, 0.0f,  14.0f),{11}},    //10
			{CVector3D(40.0f, 0.0f,  25.0f),{12}},    //11
			{CVector3D(35.0f, 0.0f,  33.0f),{13}},    //12
			{CVector3D(25.0f, 0.0f,  38.0f),{14}},    //13
			{CVector3D(11.0f, 0.0f,  41.0f),{15}},    //14
			{CVector3D(-2.0f, 0.0f,  41.0f),{16}},    //15
			{CVector3D(-16.0f, 0.0f,  41.0f),{17}},    //16
			{CVector3D(-16.0f, 0.0f,  33.0f),{18}},    //17
			{CVector3D(-16.0f, 0.0f,  26.0f),{19}},    //18
			{CVector3D(-22.0f, 0.0f,  26.0f),{}},      //19 �ŏI�n�_1
			{CVector3D(35.0f, 0.0f, -28.0f),{21}},    //20
			{CVector3D(26.0f, 0.0f, -25.0f),{22,33}}, //21 ����_4
			{CVector3D(26.0f, 0.0f, -15.0f),{23}},    //22
			{CVector3D(26.0f, 0.0f,  -5.0f),{24}},    //23
			{CVector3D(26.0f, 0.0f,   5.0f),{25}},    //24
			{CVector3D(26.0f, 0.0f,   7.0f),{26}},    //25
			{CVector3D(11.0f, 0.0f,   7.0f),{27}},    //26
			{CVector3D(11.0f, 0.0f,  16.0f),{28}},    //27
			{CVector3D(-2.0f, 0.0f,  16.0f),{29}},    //28
			{CVector3D(-4.0f, 0.0f,  10.0f),{30}},    //29
			{CVector3D(-7.0f, 0.0f,   5.0f),{31}},    //30
			{CVector3D(-16.0f, 0.0f,   4.0f),{32}},    //31
			{CVector3D(-16.0f, 0.0f,  15.0f),{18}},    //32
			{CVector3D(13.0f, 0.0f, -25.0f),{34}},    //33
			{CVector3D(1.0f, 0.0f, -25.0f),{35}},    //34
			{CVector3D(-10.0f, 0.0f, -21.0f),{36}},    //35
			{CVector3D(-16.0f, 0.0f, -12.0f),{37}},    //36
			{CVector3D(-16.0f, 0.0f,  -3.0f),{31}},    //37
			{CVector3D(12.0f, 0.0f, -41.0f),{39}},    //38 �������烋�[�gB
			{CVector3D(1.0f, 0.0f, -41.0f),{40}},    //39
			{CVector3D(-7.0f, 0.0f, -32.0f),{41}},    //40
			{CVector3D(-16.0f, 0.0f, -22.0f),{36,42}}, //41 ����_5
			{CVector3D(-25.0f, 0.0f, -16.0f),{43}},    //42
			{CVector3D(-34.0f, 0.0f, -23.0f),{44}},    //43
			{CVector3D(-34.0f, 0.0f, -32.0f),{45}},    //44
			{CVector3D(-34.0f, 0.0f, -40.0f),{46}},    //45
			{CVector3D(-52.0f, 0.0f, -40.0f),{47}},    //46
			{CVector3D(-52.0f, 0.0f, -26.0f),{48}},    //47
			{CVector3D(-52.0f, 0.0f, -12.0f),{49}},    //48
			{CVector3D(-52.0f, 0.0f,   2.0f),{50}},    //49
			{CVector3D(-52.0f, 0.0f,  16.0f),{51}},    //50
			{CVector3D(-39.0f, 0.0f,  16.0f),{52}},    //51
			{CVector3D(-31.0f, 0.0f,  21.0f),{}},      //52 �ŏI�n�_2
		};
		//���̔z�񂩂�m�[�h�z����\�z
		for (int i = 0; i < 53; i++) {
			m_nodes.push_back(new RouteNode(node[i].pos));
		}
		//�m�[�h��ڑ�
		for (int i = 0; i < 53; i++) {
			for (auto& n : node[i].next_idx) {
				m_nodes[i]->LinkNode(m_nodes[n]);
			}
		}
	}
}

RouteNodeManager* RouteNodeManager::Getinstance() {
	if (!instance) {
		instance = new RouteNodeManager(1);
	}
	return instance;
}

void RouteNodeManager::Clearinstance() {
	if (!instance) {
		return;
	}
	delete instance;
	instance = nullptr;
}

RouteNode* RouteNodeManager::GetNode(int idx) const {
	if (idx >= GetNodeSize()) return nullptr;
	return m_nodes[idx];
}

int RouteNodeManager::GetNodeSize() const {
	return m_nodes.size();
}

bool RouteNodeManager::Collision(CVector3D pos, float rad) {
	//�w���Ă���m�[�h�Ƃ��̎��̃m�[�h���g����d���[�v
	for (auto& node : m_nodes) {
		for (auto& next : node->GetNextList()) {
			//�f�o�b�O�\��
			//Utility::DrawCapsule(node->GetPos(), next->GetPos(), 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 0.5f));
			//�m�[�h�Ԃ̃J�v�Z���Ɠ������Ă�����true��Ԃ�
			if (CCollision::CollisionCapsuleShpere(node->GetPos(), next->GetPos(), 2.0f, pos, rad)) {
				return false;
			}
		}
	}
	return true;
}

void RouteNodeManager::Render() {
	//�S�Ẵm�[�h��\��
	for (auto& node : m_nodes) {
		RenderNode(node);
	}
}

void RouteNodeManager::RenderNode(RouteNode* n) {
	//�m�[�h�̈ʒu�ɋ���`��
	Utility::DrawSphere(n->GetPos(), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//���̃m�[�h�֐�������	
	for (auto& next : n->GetNextList()) {
		Utility::DrawLine(n->GetPos(), next->GetPos(), CVector4D(0.0f, 1.0f, 0.0f, 1.0f));
	}
}