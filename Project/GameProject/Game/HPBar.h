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
	/// <param name="Scale">�傫��</param>
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
	/// <param name="pos"></param>
	void SetPos(CVector3D pos);
	/// <summary>
	/// �X�P�[����ݒ�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(float scale);
	/// <summary>
	/// �c���HP�������擾
	/// </summary>
	/// <param name="par"></param>
	void SetValue(float par);
	/// <summary>
	/// �\�����邩��ݒ�
	/// </summary>
	/// <param name="b">�\�����邩</param>
	void SetVisibility(bool b) {
		m_visibility = b;
	}
	/// <summary>
	/// ���X�ɓ����ɂ���
	/// </summary>
	/// <param name="speed">���������鑬�x(�ő�l��1)</param>
	void ChangeTransparent(float speed);
	/// <summary>
	/// �����x��������
	/// </summary>
	void InitializeAlpha();
	/// <summary>
	/// �A���t�@�l���擾
	/// </summary>
	/// <returns></returns>
	float GetAlpha();

private:
	CImage m_img;
	Type m_type;
	CVector3D m_pos;
	float m_par;
	float m_bar_scale;
	float m_alpha;
	bool m_visibility;
};