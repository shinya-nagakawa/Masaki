#include "../Game/Player_TD.h"
#include "TowerBase.h"
#include "../Game/BuildMenu_UI.h"

Player_TD::Build::Build(Player_TD* owner) : State(owner) {
}

void Player_TD::Build::Enter() {

}

void Player_TD::Build::Update() {
	//タワーを建てようとしている時のみ実行する
	if (mp_owner->GetNewTower()) mp_owner->CheckBuild();
	//タワー建造を中断したいなら右クリックで中断し、以降の処理を行わない
	if (PUSH(CInput::eMouseR)) {
		mp_owner->BuildInterruption();
		return;
	}

	switch (mp_owner->GetPlayer()->GetStateStep())
	{
		//ステップ0 建造メニューを生成
	case 0: {
		//建造未完了状態に設定
		mp_owner->GetPlayer()->SetIsBuildClear(false);
		//建造メニュー画面を生成し次のステップへ
		mp_owner->SetUI(new BuildMenu_UI());
		mp_owner->GetPlayer()->NextStep();
	}
		  break;
		  //ステップ1 マウスポインターの位置から建造前段階のタワーの生成
	case 1: {
		//新しく建てるタワーの種類が決まれば(変数の初期値は-1)
		if (mp_owner->GetPlayer()->GetTowerKinds() >= 0) {
			//メニュー画面を削除し、指定のタワーを建造し次のステップへ
			mp_owner->SetUI(nullptr);
			mp_owner->NewTower();
			mp_owner->GetPlayer()->NextStep();
		}
	}
		  break;
		  //ステップ2 建造完了までタワーの位置情報を更新する
	case 2: {
		//タワーの座標をマウスのワールド座標で更新
		mp_owner->GetNewTower()->SetPos(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)));
		//タワーを建てられるなら
		if (mp_owner->GetIsCanBuild()) {
			//左クリックで位置を決定として次のステップへ
			if (PUSH(CInput::eMouseL)) {
				mp_owner->GetPlayer()->NextStep();
			}
		}
	}
		  break;
		  //ステップ3 タワーの建造完了
	case 3:
		//建造を完了させる
		mp_owner->GetNewTower()->BuildClear();
		//新しく建てるタワーのポインターをnullで初期化
		mp_owner->SetNewTower(nullptr);
		//建てるタワーの種類保存用変数を-1に設定
		mp_owner->GetPlayer()->SetTowerKinds(-1);
		//建造完了状態に設定
		mp_owner->GetPlayer()->SetIsBuildClear(true);
		//待機状態に移行
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Idle);
		break;
	default:
		break;
	}
}

void Player_TD::Build::Exit() {

}