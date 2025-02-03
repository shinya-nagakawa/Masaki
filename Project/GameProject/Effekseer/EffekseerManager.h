#pragma once

/*!
*	@brief	�G�t�F�N�g�Ǘ��N���X
*
*	�G�t�F�N�g�Ǘ��N���X
*/
#include "../Base/Task.h"
#include <map>
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#define AL_LIBTYPE_STATIC
#include <AL/alc.h>

#include <EffekseerRendererGL.h>
#include <EffekseerSoundAL.h>
#ifdef _DEBUG
#pragma comment(lib, "Effekseerd.lib")
#pragma comment(lib, "EffekseerRendererGLd.lib")
#pragma comment(lib, "EffekseerSoundALd.lib")
#else
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererGL.lib")
#pragma comment(lib, "EffekseerSoundAL.lib")
#endif




class EffekseerManager : public Task {
	//����������
	static const int	m_inctane_size = 10;
	Effekseer::ManagerRef			m_manager;
	::EffekseerRendererGL::RendererRef	m_renderer;
	EffekseerSound::SoundRef		m_sound;
	struct Effect {
		std::vector<Effekseer::EffectRef> m_effets;
		unsigned int		m_index;
		Effect() : m_index(0) {}
	};
	std::map<std::string, Effect> m_effect_list;
	static EffekseerManager* m_instance;

public:
	/*!
	@brief	�R���X�g���N�^�@�}�l�[�W���[�̏��������s��
	**/
	EffekseerManager();

	/*!
	@brief	�f�X�g���N�^�@�}�l�[�W���[�̔j�����s��
	**/
	~EffekseerManager();

	/*!
	@brief	���������G�t�F�N�g�}�l�[�W���[���擾����
	@retval	�G�t�F�N�g�}�l�[�W���[�̃|�C���^
	**/
	static EffekseerManager* GetInstance() {
		if (!m_instance) m_instance = new EffekseerManager();
		return m_instance;
	}
	static bool isInstance() {
		return (m_instance);
	}

	/*!
	@brief	�G�t�F�N�g�}�l�[�W���[��j������
			Task�ɑg�ݍ���ł��邽�߁A�j�����̂�TaskManager���s��
	@retval	����
	**/
	static void ClearInstance();

	/*!
	@brief	���ׂẴG�t�F�N�g�̍X�V���s��
	@retval ����
	**/
	void Update();

	/*!
	@brief	���ׂẴG�t�F�N�g�̕`����s��
	@retval ����
	**/
	void Render();
	/*!
	@brief	�ǂݍ��񂾃G�t�F�N�g���擾����
	@param	name		[in] �ǂݍ��ݎ��ɐݒ肵�����O
	@retval	�G�t�F�N�g�I�u�W�F�N�g�̃|�C���^
	**/
	Effekseer::EffectRef GetEffect(const std::string& name);


	/*!
	@brief	Effekseer�̃}�l�[�W���[���擾����
	@retval Effekseer::Manager�̃|�C���^
	**/
	Effekseer::ManagerRef GetManager() const {
		return m_manager;
	}
};