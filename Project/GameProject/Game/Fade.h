#pragma once

/*�t�F�[�h�̋@�\���܂Ƃ߂�����*/

class Fade{
public:
	enum class FadeState {
		eNone,    //�ʏ���
		eFadeIn,  //�t�F�[�h�C�����
		eFadeOut, //�t�F�[�h�A�E�g���
		eGrayIn,  //�O���[�C�����
		eGrayOut, //�O���[�A�E�g���
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="speed">�����x�ύX�̑��x</param>
	Fade(float speed = 0.05);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Fade();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �t�F�[�h�C���J�n
	/// </summary>
	void FadeIn(CImage* image = nullptr);
	/// <summary>
	/// �t�F�[�h�A�E�g�J�n
	/// </summary>
	void FadeOut(CImage* image = nullptr);
	/// <summary>
	/// �O���[�C���J�n
	/// </summary>
	void GrayIn();
	/// <summary>
	/// �O���[�A�E�g�J�n
	/// </summary>
	void GrayOut();

	/// <summary>
	/// �t�F�[�h�C�����I�����Ă��邩���擾
	/// </summary>
	/// <returns>�t�F�[�h�C�����I�����Ă��邩</returns>
	bool IsFadeInEnd() const;
	/// <summary>
	/// �t�F�[�h�A�E�g���I�����Ă��邩���擾
	/// </summary>
	/// <returns>�t�F�[�h�A�E�g���I�����Ă��邩</returns>
	bool IsFadeOutEnd() const;
	/// <summary>
	/// �O���[�C�����I�����Ă��邩���擾
	/// </summary>
	/// <returns>�O���[�C�����I�����Ă��邩</returns>
	bool IsGrayInEnd() const;
	/// <summary>
	/// �O���[�A�E�g���I�����Ă��邩���擾
	/// </summary>
	/// <returns>�O���[�A�E�g���I�����Ă��邩</returns>
	bool IsGrayOutEnd() const;

	/// <summary>
	/// ��Ԃ�������
	/// </summary>
	void InitializeState();
	/// <summary>
	/// �����x��ύX���鑬�x��ύX
	/// </summary>
	void SetSpeed(float speed);
	/// <summary>
	/// ���g�̏�Ԃ��擾
	/// </summary>
	/// <returns>���g�̏��</returns>
	FadeState GetState() const;
	/// <summary>
	/// �����x���擾
	/// </summary>
	/// <returns>�����x</returns>
	float GetAlpha() const;

private:
	CImage* m_img;     //�t�F�[�h�@�\���g�������摜�̃|�C���^
	CImage m_black;    //�t�F�[�h�Ɏg�p���鍕���摜
	float m_alpha;     //�����x
	float m_alphaImg;  //�󂯎�����摜�p�̓����x
	float m_speed;     //�����x��ω������鑬�x
	FadeState m_state; //���s���̏��
};