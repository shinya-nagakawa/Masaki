#pragma once

/*�S�Ă̐������̊Ǘ�*/

class TaskManager;

//��ނ̗�
enum Type{
	eBase,          //�x�[�X
	eCamera,        //�J����
	eField,         //�t�B�[���h
	ePlayer,        //�v���C���[
	eEnemy,         //�G
	eCastle,        //��
	eTower,         //�^���[
	eObstacle,      //��Q��
	ePlayer_Attack, //�����̍U��
	eEnemy_Attack,  //�G�̍U��
	eEffect,        //�G�t�F�N�g
	eScreen,        //���
	eUI,            //UI
};

//�����̗D�揇
enum class TaskPrio {
	Scene,
	Object,
	Effect,
	UI,
};

//Type���ɓ����蔻�����肽���I�u�W�F�N�g��ݒ�
extern std::unordered_map<int, std::vector<int>> collisionRules;

class Task {
	friend TaskManager;

public:
	int m_myLayer;               //�����̃��C���[
	unsigned int ID;             //�I�u�W�F�N�g�ŗL��ID
	static unsigned int Base_ID; //��������U�邽�߂̔ԍ�
	float m_elapsedTime;         //�o�ߎ��Ԍv���p
	static bool m_lastCollision; //�Փ˔��肪�I��������
	std::list<Task*> m_collisionList; //�I�u�W�F�N�g���Ɍ��܂����A�Փ˔�����s�������I�u�W�F�N�g�̃��X�g

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type"></param>
	/// <param name="prio"></param>
	Task(int type, int prio);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Task();

	/// <summary>
	/// �D��x�ݒ�
	/// </summary>
	/// <param name="prio">�ݒ肷��D��x</param>
	void SetPriority(int prio);

	/// <summary>
	/// �D��x���擾
	/// </summary>
	/// <returns></returns>
	int GetPriority() const;

	void SetSortOrder(int order);

	int GetSortOrder() const;

	void SetType(int type);

	int GetType() const;

	/// <summary>
	/// �L�����ǂ�����ݒ�
	/// </summary>
	/// <param name="enable">true�Ȃ�ΗL��</param>
	void SetEnable(bool enable);

	bool IsEnable() const;

	void SetShow(bool show);

	bool IsShow() const;

	void Kill();

	bool IsKill() const;

	virtual void Update();
	virtual void Draw();
	virtual void Render();
	virtual void Collision(Task* t);

	/// <summary>
	/// �o�ߎ��Ԍv���p�ϐ���������
	/// </summary>
	void InitializeElapsedTime();

	/// <summary>
	/// �I�u�W�F�N�g�������f���̎擾(�p����ŃI�[�o�[���[�h)
	/// </summary>
	/// <returns></returns>
	virtual CModel* GetModel() {
		return nullptr;
	}

	int m_prio;
	int m_sortOrder;
	int m_type;

	bool m_is_Enable;
	bool m_is_Show;
	bool m_is_Kill;
};