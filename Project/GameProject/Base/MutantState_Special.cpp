#include "../Game/Mutant.h"
#include "../Game/EnemyAttack.h"
#include "../Game/BuffDebuff.h"

Mutant::Mutant_Special::Mutant_Special(Mutant* owner) : State(owner) 
	, m_specialTiming(57.0f)
	, mp_owner(owner){
}

void Mutant::Mutant_Special::Enter() {
	//����s���̃A�j���[�V�����ɕύX
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimSpecial, false);
}

void Mutant::Mutant_Special::Update() {
	switch (mp_owner->m_statestep)
	{
	//�X�e�b�v0 : �w��̃^�C�~���O�ōU���ƃo�t�𐶐�
	case 0:
		//�U��/�o�t�̐����^�C�~���O�Ȃ�
		if (mp_owner->m_model.GetAnimationFrame() >= m_specialTiming) {
			//�G�̃��X�g���擾���˒��͈͓��̓G�ɍU���͂̃o�t
			auto list = TaskManager::FindObjects(eEnemy);
			for (auto& t : list) {
				CharaBase* b = static_cast<CharaBase*>(t);
				CVector3D v = b->GetPos() - mp_owner->GetPos();
				if (CVector3D(v.x, 0.0f, v.z).LengthSq() < pow(mp_owner->m_status.GetRange(), 2)) {
					//�U���͂�5�b��1.5�{
					b->AddBuffDebuff(mp_owner->GetBuff(), b->GetPos());
				}
			}
			//�U���𐶐�����
			if (mp_owner->GetEnemyAttack() == nullptr) {
				//����U���𐶐�
				mp_owner->SetEnemyAttack(new EnemyAttack(mp_owner->GetPos(), EnemyAttack::Kinds::Roar, *mp_owner));
			}
			mp_owner->NextStep();
		}
		
		break;
	//�X�e�b�v1 : �A�j���[�V�������I�����Ă�����A�ҋ@��ԂɈڍs
	case 1:
		if (mp_owner->m_model.isAnimationEnd()) {
			//�U���̃|�C���^��nullptr�ɐݒ�
			mp_owner->SetEnemyAttack(nullptr);
			mp_owner->ChangeState(mp_owner->GetOldEnemyState());
		}
		break;
	default:
		break;
	}
}

void Mutant::Mutant_Special::Exit() {
}