#pragma once
#include<list>

/*Task�̊Ǘ� ���X�g�֘A*/

class Task;

class TaskManager {
public:
	/// <summary>
	/// ���g�𐶐�/�ԋp(�V���O���g��)
	/// </summary>
	/// <returns>���g</returns>
	static TaskManager* GetInstance();
	/// <summary>
	/// ���g���폜
	/// </summary>
	static void Clearinstance();

	/// <summary>
	/// �^�X�N���X�g�ɒǉ�
	/// </summary>
	/// <param name="add">�ǉ�����^�X�N</param>
	/// <param name="layer">�ݒ肵�Ȃ�</param>
	/// 1�ڂ̃��C���[�ɂ̂ݒǉ��A���C���[��؂�ւ��邱�Ƃ�2�ڂ̃��C���[�ɂȂ�A
	/// 2�ڂ̃��C���[�ɂ͎��g��ǉ����Ă��Ȃ��̂ōX�V�������Ă΂�Ȃ�
	void AddtoTask(Task* add, int layer = 0);
	/// <summary>
	/// �����_�[���X�g�ɒǉ�
	/// </summary>
	/// <param name="add">�ǉ�����^�X�N</param>
	void AddtoRender(Task* add);
	/// <summary>
	/// �R���W�������X�g�ɒǉ�
	/// </summary>
	/// <param name="add">�ǉ�����^�X�N</param>
	void AddtoCollision(Task* add);

	/// <summary>
	/// ���X�g����폜
	/// </summary>
	/// <param name="remove">�폜����^�X�N</param>
	void Remove(Task* remove);
	/// <summary>
	/// ���X�g����폜���I�u�W�F�N�g���폜
	/// </summary>
	/// <param name="del">�폜����^�X�N</param>
	void Delete(Task* del);
	/// <summary>
	/// �폜�̊m�F
	/// </summary>
	void DeleteChack();

	/// <summary>
	/// �S�I�u�W�F�N�g�폜
	/// </summary>
	void DeleteAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̍X�V����
	/// </summary>
	void UpdateAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̕`�揈��(�摜)
	/// </summary>
	void DrawAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̕`�揈��(���f��)
	/// </summary>
	void RenderAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̏Փ˔���
	/// </summary>
	void CollisionAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̍폜
	/// </summary>
	void KillAll();

	/// <summary>
	/// �I�u�W�F�N�g�̌���(�ŏ��Ɍ��������v�f���擾)
	/// </summary>
	/// <param name="type">��������I�u�W�F�N�g�̃^�C�v</param>
	/// <returns>��������</returns>
	Task* FindObject(int type);
	/// <summary>
	/// �I�u�W�F�N�g�̌���(�z����擾)
	/// </summary>
	/// <param name="type">�擾����I�u�W�F�N�g�̃^�C�v</param>
	/// <returns></returns>
	std::list<Task*> FindObjects(int type);
	/// <summary>
	/// �I�u�W�F�N�g�̌���(�Ō�Ɍ��������v�f���擾)
	/// </summary>
	/// <param name="type">��������I�u�W�F�N�g�̃^�C�v</param>
	/// <returns>��������</returns>
	Task* FindObjectReverce(int type);
	/// <summary>
	/// ID�ŃI�u�W�F�N�g������
	/// </summary>
	/// <param name="ID">�����Ώۂ�ID</param>
	/// <returns>��������</returns>
	Task* FindObjectbyID(unsigned int ID);

	/// <summary>
	/// �I�u�W�F�N�g���ɂ����������蔻����s�����̃��X�g��ԋp
	/// </summary>
	/// <param name="self">���g</param>
	/// <returns>�����蔻����s���I�u�W�F�N�g���܂Ƃ߂�ꂽ���X�g</returns>
	std::list<Task*> GetCollisionTargets(Task* self);
	/// <summary>
	/// ���C���[�̕ύX(�|�[�Y�@�\)
	/// </summary>
	void LayerChange();
	/// <summary>
	/// ���݂̃��C���[��ԋp
	/// </summary>
	/// <returns>���݂̃��C���[</returns>
	int GetLayer() const;
	/// <summary>
	/// �w��̃^�C�v���C���f�b�N�X���g�p���邩�擾
	/// </summary>
	/// <param name="type">�m���߂����^�C�v</param>
	/// <returns>�C���f�b�N�X���g�p����^�C�v��</returns>
	bool GetIndexFlag(int type);
	/// <summary>
	/// �C���f�b�N�X���g�p���邩���^�C�v���ɐݒ�
	/// </summary>
	void SetIndexFlag();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TaskManager();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TaskManager();

private:
	static TaskManager* instance;     //�C���X�^���X

	int currentLayer;                 //���݈����Ă���^�X�N���X�g�̔ԍ�
	std::list<Task*> m_taskList[2];   //�^�X�N�̃��X�g
	std::list<Task*> m_renderList;    //�`�悷��I�u�W�F�N�g�̃��X�g
	std::list<Task*> m_collisionList; //�Փ˔�����s���I�u�W�F�N�g�̃��X�g
	std::list<Task*> m_cacheList;     //�L���b�V���̃��X�g
	std::unordered_map<int, std::list<Task*>> m_index; //Type���L�[�Ƃ����C���f�b�N�X�̃}�b�v
	std::unordered_map<int, bool> m_indexFlag;         //Type���ƂɃC���f�b�N�X���g�p���邩�ǂ����𔻕ʂ���}�b�v
};