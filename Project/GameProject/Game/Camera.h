#pragma once
#include "../Base/ObjectBase.h"

/*�J����*/

class Camera : public ObjectBase {
private:
	int old_GameMode;  //�Q�[�����[�h�ύX���̔�r�p
	float m_dist;      //�Ԋu

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Camera();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render() override;
	/// <summary>
	/// �w��̃I�u�W�F�N�g�ɃY�[���@���ݖ��g�p
	/// </summary>
	/// <param name="b">�w�肵���I�u�W�F�N�g</param>
	void Zoom(ObjectBase* b);
};