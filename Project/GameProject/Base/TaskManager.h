#pragma once
#include<list>

/*Task�̊Ǘ� ���X�g�֘A*/

class Task;

class TaskManager {
public:
	/// <summary>
	/// �^�X�N���X�g�ɒǉ�
	/// </summary>
	/// <param name="add"></param>
	/// <param name="isShort"></param>
	/// <param name="layer">�ݒ肵�Ȃ�</param>
	/// 1�ڂ̃��C���[�ɂ̂ݒǉ��A���C���[��؂�ւ��邱�Ƃ�2�ڂ̃��C���[�ɂȂ�A
	/// 2�ڂ̃��C���[�ɂ͎��g��ǉ����Ă��Ȃ��̂ōX�V�������Ă΂�Ȃ�
	static void AddtoTask(Task* add, bool isShort = false, int layer = 0);
	/// <summary>
	/// �����_�[���X�g�ɒǉ�
	/// </summary>
	/// <param name="add"></param>
	/// <param name="isShort"></param>
	static void AddtoRender(Task* add, bool isShort = false);
	/// <summary>
	/// �R���W�������X�g�ɒǉ�
	/// </summary>
	/// <param name="add"></param>
	/// <param name="isShort"></param>
	static void AddtoCollision(Task* add, bool isShort = false);

	/// <summary>
	/// ���X�g����폜
	/// </summary>
	/// <param name="remove"></param>
	/// <param name="isShort"></param>
	static void Remove(Task* remove, bool isShort = false);
	/// <summary>
	/// ���X�g����폜���I�u�W�F�N�g���폜
	/// </summary>
	/// <param name="del"></param>
	static void Delete(Task* del);
	/// <summary>
	/// �폜�̊m�F
	/// </summary>
	static void DeleteChack();

	/// <summary>
	/// �S�I�u�W�F�N�g�폜
	/// </summary>
	static void DeleteAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̍X�V����
	/// </summary>
	static void UpdateAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̕`�揈��(�摜)
	/// </summary>
	static void DrawAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̕`�揈��
	/// </summary>
	static void RenderAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̏Փ˔���
	/// </summary>
	static void CollisionAll();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̍폜
	/// </summary>
	static void KillAll();

	/// <summary>
	/// �I�u�W�F�N�g�̌���
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static Task* FindObject(int type);
	/// <summary>
	/// �I�u�W�F�N�g�̌���(�z����擾)
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static std::list<Task*> FindObjects(int type);
	/// <summary>
	/// �I�u�W�F�N�g�̌���(�Ō�Ɏ擾�����v�f��ԋp)
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static Task* FindObjectReverce(int type);
	/// <summary>
	/// ID�ŃI�u�W�F�N�g������
	/// </summary>
	/// <param name="ID">�����Ώۂ�ID</param>
	/// <returns></returns>
	static Task* FindObjectbyID(unsigned int ID);

	/// <summary>
	/// �I�u�W�F�N�g���ɂ����������蔻����s�����̃��X�g��ԋp
	/// </summary>
	/// <param name="self">���g</param>
	/// <returns></returns>
	static std::list<Task*> GetCollisionTargets(Task* self);
	/// <summary>
	/// ���C���[�̕ύX(�|�[�Y�@�\)
	/// </summary>
	static void LayerChange();
	/// <summary>
	/// ���݂̃��C���[��ԋp
	/// </summary>
	/// <returns></returns>
	static int GetLayer();
	/// <summary>
	/// �w��̃^�C�v���C���f�b�N�X���g�p���邩�擾
	/// </summary>
	/// <param name="type">�m���߂����^�C�v</param>
	/// <returns></returns>
	static bool GetIndexFlag(int type);
	/// <summary>
	/// �C���f�b�N�X���g�p���邩���^�C�v���ɐݒ�
	/// </summary>
	static void SetIndexFlag();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TaskManager();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TaskManager();

	static int currentLayer;                 //���݈����Ă���^�X�N���X�g��
	static std::list<Task*> m_taskList[2];   //�^�X�N�̃��X�g
	static std::list<Task*> m_renderList;    //�`�悷��I�u�W�F�N�g�̃��X�g
	static std::list<Task*> m_collisionList; //�Փ˔�����s���I�u�W�F�N�g�̃��X�g
	static std::list<Task*> m_cacheList;     //�L���b�V���̃��X�g
	static std::unordered_map<int, std::list<Task*>> m_index; //Type���L�[�Ƃ����C���f�b�N�X�̃}�b�v
	static std::unordered_map<int, bool> m_indexFlag;         //Type���ƂɃC���f�b�N�X���g�p���邩�ǂ����𔻕ʂ���}�b�v
};