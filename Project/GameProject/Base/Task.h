#pragma once

/*�S�Ă̐������̊Ǘ�*/

class TaskManager;

//��ނ̗�
enum Type{
	eControl,       //�R���g���[��
	eCamera,        //�J����
	eField,         //�t�B�[���h
	ePlayer,        //�v���C���[
	eEnemy,         //�G
	eCastle,        //��
	eTower,         //�^���[
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
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�^�C�v</param>
	/// <param name="prio">�D��x</param>
	Task(int type, int prio);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Task();

	/// <summary>
	/// �D��x���擾
	/// </summary>
	/// <returns>�D��x</returns>
	int GetPriority() const;
	/// <summary>
	/// �D��x�ݒ�
	/// </summary>
	/// <param name="prio">�D��x</param>
	void SetPriority(int prio);

	/// <summary>
	/// �^�C�v���擾
	/// </summary>
	/// <returns>�^�C�v</returns>
	int GetType() const;
	/// <summary>
	/// �^�C�v��ݒ�
	/// </summary>
	/// <param name="type">�^�C�v</param>
	void SetType(int type);

	/// <summary>
	/// �L�����ǂ������擾
	/// </summary>
	/// <returns></returns>
	bool GetIsEnable() const;
	/// <summary>
	/// �L�����ǂ�����ݒ�
	/// </summary>
	/// <param name="enable">true�Ȃ�ΗL��</param>
	void SetEnable(bool enable);

	/// <summary>
	/// �\�����邩���擾
	/// </summary>
	/// <returns></returns>
	bool GetIsShow() const;
	/// <summary>
	/// �\�����邩��ݒ�
	/// </summary>
	/// <param name="show"></param>
	void SetShow(bool show);

	/// <summary>
	/// �폜���邩�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsKill() const;
	/// <summary>
	/// �폜����
	/// </summary>
	void SetKill();

	/// <summary>
	/// ID���擾
	/// </summary>
	/// <returns></returns>
	unsigned int GetID() const;

	/// <summary>
	/// �o�ߎ��Ԍv���p�ϐ���������
	/// </summary>
	void InitializeElapsedTime();
	/// <summary>
	/// �o�ߎ��Ԍv���p�ϐ����擾
	/// </summary>
	/// <returns></returns>
	float GetElapsedTime() const;
	/// <summary>
	/// �o�ߎ��Ԍv���p�ϐ���ݒ�
	/// </summary>
	void SetElapsedTime(float deltaTime);

	/// <summary>
	/// �Փ˔��肪�I���������擾
	/// </summary>
	/// <returns></returns>
	bool GetLastCollision() const;

	/// <summary>
	/// �Փ˔�����s�������I�u�W�F�N�g�̃��X�g���擾
	/// </summary>
	/// <returns></returns>
	std::list<Task*> GetCollisionList();
	/// <summary>
	/// �Փ˔�����s�������I�u�W�F�N�g�̃��X�g��ݒ�
	/// </summary>
	/// <param name="collisionList"></param>
	void SetCollisionList(std::list<Task*> collisionList);

	/// <summary>
	/// �I�u�W�F�N�g�������f���̎擾(�p����ŃI�[�o�[���[�h)
	/// </summary>
	/// <returns></returns>
	virtual CModel* GetModel() {
		return nullptr;
	}

	virtual void Update();
	virtual void Draw();
	virtual void Render();
	virtual void Collision(Task* t);

protected:
	float m_elapsedTime; //�o�ߎ��Ԍv���p

private:
	int m_prio;
	int m_type;
	bool m_isEnable;
	bool m_isShow;
	bool m_isKill;

	int m_myLayer;               //�����̃��C���[
	unsigned int ID;             //�I�u�W�F�N�g�ŗL��ID
	static unsigned int Base_ID; //��������U�邽�߂̔ԍ�
	static bool m_lastCollision; //�Փ˔��肪�I��������
	std::list<Task*> m_collisionList; //�I�u�W�F�N�g���Ɍ��܂����A�Փ˔�����s�������I�u�W�F�N�g�̃��X�g
};