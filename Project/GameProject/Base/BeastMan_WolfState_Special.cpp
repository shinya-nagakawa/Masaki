#include "../Game/BeastMan_Wolf.h"
#include "../Game/Goblin.h"

BeastMan_Wolf::BeastMan_Wolf_Special::BeastMan_Wolf_Special(BeastMan_Wolf* owner) : State(owner)
	, mp_owner(owner)
	, m_specialTiming(57.0f){
}

void BeastMan_Wolf::BeastMan_Wolf_Special::Enter(){
	//����s���A�j���[�V�����ɕύX
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimSpecial, false);
}

void BeastMan_Wolf::BeastMan_Wolf_Special::Update(){
	switch (mp_owner->m_statestep)
	{
	//�X�e�b�v0 : �w��̃^�C�~���O�œG�𐶐�
	case 0:
		//�����A�j���[�V�����̃t���[�����w��̃^�C�~���O�Ȃ�
		if (mp_owner->m_model.GetAnimationFrame() == m_specialTiming) {
			//�S�u������2�̐������A���̃S�u�����̈ړ���ԏ��������g�̕��ɕύX�H
			//new Goblin();
			//new Goblin();
		}
		break;
	//�X�e�b�v1 : �A�j���[�V�������I�����Ă�����ҋ@��Ԃֈڍs
	case 1:
		if (mp_owner->m_model.isAnimationEnd()) {
			mp_owner->ChangeState(EnemyState::eState_Idle);
		}
		break;
	default:
		break;
	}
}

void BeastMan_Wolf::BeastMan_Wolf_Special::Exit(){

}
