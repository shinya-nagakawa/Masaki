#pragma once
#include "Player.h"

/*�v���C���[�̊e���[�h�̏����̎����Ɏg���N���X*/

class PlayerMode {
public:
    virtual ~PlayerMode() {}
    /// <summary>
    /// �v���C���[���擾
    /// </summary>
    /// <returns>�v���C���[</returns>
    Player* GetPlayer(){
        return mp_player;
    }
    /// <summary>
    /// �v���C���[��ݒ�
    /// </summary>
    /// <param name="player">�v���C���[</param>
    void SetPlayer(Player* player) {
        mp_player = player;
    }

    //�J�n������
    virtual void Enter() = 0;
    // ���[�h���Ƃ̍X�V����
    virtual void Update() = 0;
    // ���[�h���Ƃ̕`�揈��
    virtual void Render() {}
    //�I��������
    virtual void Exit() = 0;

    /// <summary>
    /// ��ԑJ��
    /// </summary>
    /// <param name="state">�ύX������</param>
    virtual void ChangeState(Player::PlayerState state) = 0;

protected:
    Player* mp_player = nullptr; //�v���C���[
};