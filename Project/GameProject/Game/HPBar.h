#pragma once

/*HP�o�[ �L�����N�^�[�S�Ă�����*/

class HPBar {
public:
	enum class Type {
		ePlayerBar, //�v���C���[��HP
		eCastleBar, //���HP
		eEnemyBar,  //�G��HP
		eTowerBar,  //�^���[��HP
		eMax        //�ő�HP
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="Scale">�X�P�[��</param>
	HPBar(float Scale);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~HPBar();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �o�[�̃^�C�v��ݒ�
	/// </summary>
	/// <param name="Bar_type">�\������Ώۂɍ��킹���^�C�v</param>
	void SetType(Type Bar_type);
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷����W</param>
	void SetPos(CVector3D pos);
	/// <summary>
	/// �X�P�[����ݒ�
	/// </summary>
	/// <param name="scale">�ݒ肷��X�P�[��</param>
	void SetScale(float scale);
	/// <summary>
	/// �c���HP�������擾
	/// </summary>
	/// <param name="par">HP����</param>
	void SetValue(float par);
	/// <summary>
	/// �\�����邩��ݒ�
	/// </summary>
	/// <param name="b">�\�����邩</param>
	void SetVisibility(bool b) {
		m_visibility = b;
	}

	/// <summary>
	/// �A���t�@�l��������
	/// </summary>
	void InitializeAlpha();
	/// <summary>
	/// �A���t�@�l���擾
	/// </summary>
	/// <returns>�A���t�@�l</returns>
	float GetAlpha() const;
	/// <summary>
	/// �A���t�@�l��ݒ�
	/// </summary>
	/// <param name="alpha">�A���t�@�l</param>
	void SetAlpha(float alpha);

private:
	CImage m_img;      //�摜�f�[�^
	Type m_type;       //�^�C�v
	CVector3D m_pos;   //���W
	float m_par;       //���݂̊���
	float m_bar_scale; //�X�P�[��
	float m_alpha;     //�����x
	bool m_visibility; //�\�����邩
};