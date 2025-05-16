#include "CharaBase.h"
#include "../Game/Game.h"
#include "../Game/BuffDebuff.h"
#include "../Game/HPBar.h"
#include "../Game/CharaStatus.h"
#include "../Effekseer/EffekseerEffect.h"

bool CharaBase::m_isTutorial = false;

CharaBase::CharaBase(int type) : ObjectBase(type)
	, m_HPBar(0.07f)
	, m_bar_pos(CVector3D::zero)
	, m_attacktiming(0)
	, m_isStan(false)
	, m_kill(false)
	, m_isCollision(true)
	, m_statestep(0)
	, m_status()
	, m_effect(nullptr){
}

CharaBase::~CharaBase() {
}

void CharaBase::Update(){
	//オブジェクト共通の更新処理
	ObjectBase::Update();
	//プレイヤーか敵のみ重力を与える
	if (GetType() == ePlayer || GetType() == eEnemy) {
		m_pos.y += m_vec.y;
		m_vec.y -= GRAVITY;
	}
	//バフデバフの管理
	BuffDebuffCheck();
	//死亡確認
	if (m_status.GetHP() <= 0.0f) m_kill = true;
	//HPが最大HPを超える時、maxHPに戻す
	if (m_status.GetHP() > m_status.GetMaxHP()) {
		m_status.SetHP(m_status.GetMaxHP());
	}
	//HPがマイナスになるとき、0に戻す
	if (m_status.GetHP() <= 0.0f) {
		m_status.SetHP(0.0f);
	}
	//もしエフェクトが生成されていたら、エフェクトの座標を自身の座標に設定
	if (m_effect) {
		if (m_effect->GetIsKill()) {
			m_effect = nullptr;
		}
		else {
			m_effect->SetPos(m_pos);
		}
	}
}

void CharaBase::Draw(){
	//HPバーの各要素を設定し描画(城クラス以外)
	if (GetType() != eCastle && GetType() != ePlayer) {
		//タワーディフェンス時
		if (Game::GameMode == Game::GameMode::Mode_TD) {
			m_HPBar.SetPos(Utility::WorldToScreen(m_pos + m_bar_pos));
			m_HPBar.SetVisibility(true);
		}
		//アクション時
		else {
			m_HPBar.SetPos(Utility::WorldToScreen(m_pos));
			//プレイヤーが取得出来たら
			if (CharaBase* p = static_cast<CharaBase*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
				CVector3D vec = p->GetPos() - m_pos;
				//プレイヤーと自身の距離が30cmより小さいならHPバーを描画
				if (vec.LengthSq() < 50.0f * 50.0f) {
					m_HPBar.SetVisibility(true);
				}
				//そうでないなら、描画しない
				else {
					m_HPBar.SetVisibility(false);
				}
			}
		}
		m_HPBar.SetValue((float)m_status.GetHP() / m_status.GetMaxHP());
		m_HPBar.Draw();
	}
}

void CharaBase::TakeDamage(float Power, float Defence, int Level_A, int Level_D) {
	//レベルバフ変数を1に設定
	float LevelBuff = 1.0f;
	//攻撃側のレベルが防御側のレベルより高かった時
	if (Level_A > Level_D) {
		//レベルバフを計算(レベルに1差がある毎にダメージに+0.5倍の補正が乗る)
		LevelBuff = 1.0f + (Level_A - Level_D) / 2.0f;
	}
	//ダメージ計算
	float Damage = (1.0f + Power - Defence) * LevelBuff;
	//ダメージがマイナスの場合、1にする
	if (Damage <= 0.0f) {
		Damage = 1.0f;
	}
	//HPからダメージを引く
	m_status.SetHP(m_status.GetHP() - Damage);
}

void CharaBase::BuffDebuffCheck(){
	//ステータスをバフ前に戻す
	m_status.ResetStatus();
	//現在のステータスで基礎ステータスを更新
	m_status.UpdateBaseStatus();

	float BuffCT = 0.0f;     //クールタイムバフ保存変数
	float DebuffCT = 0.0f;   //クールタイムデバフ保存変数
	float RecoverHP = 0.0f;  //回復するHP
	float DamageHP = 0.0f;   //減少するHP
	float BuffS = 0.0f;      //速度バフ保存変数
	float DebuffS = 0.0f;    //速度デバフ保存変数
	float BuffP = 0.0f;      //攻撃力バフ保存変数
	float DebuffP = 0.0f;    //攻撃力デバフ保存変数
	float BuffD = 0.0f;      //防御力バフ保存変数
	float DebuffD = 0.0f;    //防御力デバフ保存変数
	float BuffR = 0.0f;      //射程バフ保存変数
	float DebuffR = 0.0f;    //射程デバフ保存変数

	//リスト内に効果時間の切れたバフ/デバフがあればリストから除外、切れていなければ効果時間減少
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

	//バフ/デバフのリストを最初から探索
	for (auto& b : m_BuffDebufflist) {
		//バフの場合
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
		//デバフの場合
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

	//バフ/デバフを適応
	m_status.ApplyBuffDebuff(RecoverHP, BuffS, BuffP, BuffD, BuffR, BuffCT, DamageHP, DebuffS, DebuffP, DebuffP, DebuffR, DebuffCT);
}

void CharaBase::AddBuffDebuff(const BuffDebuff& buffdebuff, const CVector3D& pos){
	//リスト内から同じバフ/デバフを検索
	auto it = std::find_if(m_BuffDebufflist.begin(), m_BuffDebufflist.end(),
		[&buffdebuff](const BuffDebuff& b) { return b.GetBuffDebuffType() == buffdebuff.GetBuffDebuffType(); });
	//同じバフ/デバフが見つかった場合、古いバフ/デバフをリストから除外
	if (it != m_BuffDebufflist.end()) {
		m_BuffDebufflist.erase(it);
	}
	// 新しいバフ/デバフを追加
	m_BuffDebufflist.push_back(buffdebuff);
	//もしエフェクトが長くて敵についていかないのが見栄えが悪いなら、エフェクトのポインタを用意しそこに生成、nullptrではない間
	//posの座標にエフェクトの座標を更新する　
	//追加されたのがバフの場合
	if (buffdebuff.GetBufforDebuff() == Buff) {
		//バフエフェクトを生成
		m_effect = new EffekseerEffect("Get_Buff", pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), 0, 140);
		//バフサウンドを流す
		SOUND("Buff")->Play();
	}
	//デバフの場合
	else {
		//デバフエフェクトを生成
		m_effect = new EffekseerEffect("Get_Debuff", pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), 0, 140);
		//デバフサウンドを流す
		SOUND("Debuff")->Play();
	}
}

bool CharaBase::IsDeath() const{
	return m_kill;
}

bool CharaBase::GetIsCollision() const{
	return m_isCollision;
}

void CharaBase::SetIsCollision(bool isCollision){
	m_isCollision = isCollision;
}

const CharaStatus& CharaBase::GetStatus() const{
	return m_status;
}

bool CharaBase::GetIsHasBuffDebuff() const{
	return !m_BuffDebufflist.empty();
}

const bool CharaBase::GetIsTutorial(){
	return m_isTutorial;
}

void CharaBase::SetIsTutorial(bool isTutorial){
	m_isTutorial = isTutorial;
}

void CharaBase::NextStep() {
	m_statestep++;
}

int CharaBase::GetStateStep() const{
	return m_statestep;
}

HPBar& CharaBase::GetHPBar(){
	return m_HPBar;
}

int CharaBase::GetAttackTiming() const{
	return m_attacktiming;
}
