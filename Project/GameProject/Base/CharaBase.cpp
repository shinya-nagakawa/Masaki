#include "CharaBase.h"
#include "../Game/BuffDebuff.h"
#include "../Game/HPBar.h"
#include "../Game/CharaStatus.h"
#include "../Effekseer/EffekseerEffect.h"

CharaBase::CharaBase(int type) : ObjectBase(type)
	, m_HPBar(0.07f)
	, m_bar_pos(CVector3D::zero)
	, m_attacktiming(0)
	, m_statuspoint(0)
	, m_isStan(false)
	, m_kill(false)
	, m_statestep(0)
	, m_status()
	, m_effect(nullptr){
}

CharaBase::~CharaBase() {
}

void CharaBase::Update(){
	//�I�u�W�F�N�g���ʂ̍X�V����
	ObjectBase::Update();
	//�v���C���[���G�̂ݏd�͂�^����
	if (GetType() == ePlayer || GetType() == eEnemy) {
		m_pos.y += m_vec.y;
		m_vec.y -= GRAVITY;
	}
	//�o�t�f�o�t�̊Ǘ�
	BuffDebuffCheck();
	//���S�m�F
	if (m_status.GetHP() <= 0.0f) m_kill = true;
	//HP���ő�HP�𒴂��鎞�AmaxHP�ɖ߂�
	if (m_status.GetHP() > m_status.GetMaxHP()) {
		m_status.SetHP(m_status.GetMaxHP());
	}
	//HP���}�C�i�X�ɂȂ�Ƃ��A0�ɖ߂�
	if (m_status.GetHP() <= 0.0f) {
		m_status.SetHP(0.0f);
	}
	//�����G�t�F�N�g����������Ă�����A�G�t�F�N�g�̍��W�����g�̍��W�ɐݒ�
	if (m_effect) {
		m_effect->SetPos(m_pos);
	}
}

void CharaBase::Draw(){
	//HP�o�[�̊e�v�f��ݒ肵�`��
	if (GetType() != eCastle) m_HPBar.SetPos(Utility::WorldToScreen(m_pos + m_bar_pos));
	m_HPBar.SetValue((float)m_status.GetHP() / m_status.GetMaxHP());
	m_HPBar.Draw();
}

void CharaBase::TakeDamage(float Power, float Defence, int Level_A, int Level_D) {
	//���x���o�t�ϐ���1�ɐݒ�
	float LevelBuff = 1.0f;
	//�U�����̃��x�����h�䑤�̃��x����荂��������
	if (Level_A > Level_D) {
		//���x���o�t���v�Z(���x����1�������閈�Ƀ_���[�W��+0.5�{�̕␳�����)
		LevelBuff = 1.0f + (Level_A - Level_D) / 2.0f;
	}
	//�_���[�W�v�Z
	float Damage = (1.0f + Power - Defence) * LevelBuff;
	//�_���[�W���}�C�i�X�̏ꍇ�A1�ɂ���
	if (Damage <= 0.0f) {
		Damage = 1.0f;
	}
	//HP����_���[�W������
	m_status.SetHP(m_status.GetHP() - Damage);
}

void CharaBase::BuffDebuffCheck(){
	//�X�e�[�^�X���o�t�O�ɖ߂�
	m_status.ResetStatus();
	//���݂̃X�e�[�^�X�Ŋ�b�X�e�[�^�X���X�V
	m_status.UpdateBaseStatus();

	float BuffCT = 0.0f;     //�N�[���^�C���o�t�ۑ��ϐ�
	float DebuffCT = 0.0f;   //�N�[���^�C���f�o�t�ۑ��ϐ�
	float RecoverHP = 0.0f;  //�񕜂���HP
	float DamageHP = 0.0f;   //��������HP
	float BuffS = 0.0f;      //���x�o�t�ۑ��ϐ�
	float DebuffS = 0.0f;    //���x�f�o�t�ۑ��ϐ�
	float BuffP = 0.0f;      //�U���̓o�t�ۑ��ϐ�
	float DebuffP = 0.0f;    //�U���̓f�o�t�ۑ��ϐ�
	float BuffD = 0.0f;      //�h��̓o�t�ۑ��ϐ�
	float DebuffD = 0.0f;    //�h��̓f�o�t�ۑ��ϐ�
	float BuffR = 0.0f;      //�˒��o�t�ۑ��ϐ�
	float DebuffR = 0.0f;    //�˒��f�o�t�ۑ��ϐ�

	//���X�g���Ɍ��ʎ��Ԃ̐؂ꂽ�o�t/�f�o�t������΃��X�g���珜�O�A�؂�Ă��Ȃ���Ό��ʎ��Ԍ���
	auto itr = m_BuffDebufflist.begin();
	while (itr != m_BuffDebufflist.end()) {
		if (itr->IsTimeOver()) {
			itr = m_BuffDebufflist.erase(itr);
		}
		else {
			itr->SubtractionTime();
			itr++;
		}
	}

	//�o�t/�f�o�t�̃��X�g���ŏ�����T��
	for (auto& b : m_BuffDebufflist) {
		//�o�t�̏ꍇ
		if (b.GetBufforDebuff() == Buff) {
			switch (b.GetEffect()) {
			case HP:      RecoverHP = max(RecoverHP, b.GetSize()); break;
			case Speed:   BuffS     = max(BuffS, b.GetSize());     break;
			case Power:   BuffP     = max(BuffP, b.GetSize());     break;
			case Defence: BuffD     = max(BuffD, b.GetSize());     break;
			case Range:   BuffR     = max(BuffR, b.GetSize());     break;
			case CT:      BuffCT    = min(BuffCT, b.GetSize());    break;
			default: break;
			}
		}
		//�f�o�t�̏ꍇ
		else {
			switch (b.GetEffect()) {
			case HP:      DamageHP = min(DamageHP, b.GetSize()); break;
			case Speed:   DebuffS  = max(DebuffS, b.GetSize());  break;
			case Power:   DebuffP  = max(DebuffP, b.GetSize());  break;
			case Defence: DebuffD  = max(DebuffD, b.GetSize());  break;
			case Range:   DebuffR  = max(DebuffR, b.GetSize());  break;
			case CT:      DebuffCT = max(DebuffCT, b.GetSize()); break;
			default: break;
			}
		}
	}

	//�o�t/�f�o�t��K��
	m_status.ApplyBuffDebuff(RecoverHP, BuffS, BuffP, BuffD, BuffR, BuffCT, DamageHP, DebuffS, DebuffP, DebuffP, DebuffR, DebuffCT);
}

void CharaBase::AddBuffDebuff(const BuffDebuff& buffdebuff, const CVector3D& pos){
	//���X�g�����瓯���o�t/�f�o�t������
	auto it = std::find_if(m_BuffDebufflist.begin(), m_BuffDebufflist.end(),
		[&buffdebuff](const BuffDebuff& b) { return b.GetBuffDebuffType() == buffdebuff.GetBuffDebuffType(); });
	//�����o�t/�f�o�t�����������ꍇ�A�Â��o�t/�f�o�t�����X�g���珜�O
	if (it != m_BuffDebufflist.end()) {
		m_BuffDebufflist.erase(it);
	}
	// �V�����o�t/�f�o�t��ǉ�
	m_BuffDebufflist.push_back(buffdebuff);
	//�����G�t�F�N�g�������ēG�ɂ��Ă����Ȃ��̂����h���������Ȃ�A�G�t�F�N�g�̃|�C���^��p�ӂ������ɐ����Anullptr�ł͂Ȃ���
	//pos�̍��W�ɃG�t�F�N�g�̍��W���X�V����@
	//�ǉ����ꂽ�̂��o�t�̏ꍇ
	if (buffdebuff.GetBufforDebuff() == Buff) {
		//�o�t�G�t�F�N�g�𐶐�
		m_effect = new EffekseerEffect("Get_Buff", pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f));
	}
	//�f�o�t�̏ꍇ
	else {
		//�f�o�t�G�t�F�N�g�𐶐�
		m_effect = new EffekseerEffect("Get_Debuff", pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f));
	}
}

bool CharaBase::IsDeath() const{
	return m_kill;
}

const CharaStatus& CharaBase::GetStatus() const{
	return m_status;
}

void CharaBase::NextStep() {
	m_statestep++;
}