#pragma once
#include "../Base/ObjectBase.h"

/*��Q�� ������*/

class Obstacle : public ObjectBase {
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos"></param>
	Obstacle(const CVector3D& pos);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Obstacle();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render() override;
};
