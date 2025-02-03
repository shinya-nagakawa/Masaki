#include "Camera.h"
#include "Player.h"
#include "Game.h"

Camera::Camera() : ObjectBase(eCamera)
	, old_GameMode(Game::GameMode)
	, m_dist(0.0f){
}

void Camera::Update() {
	if (old_GameMode != Game::GameMode) {
		old_GameMode = Game::GameMode;
		m_dist = 0.0f;
	}
}

void Camera::Render() {
	//影描画の時は移行の処理を行わない
	if (CShadow::isDoShadow()) return;
	//カメラの移動速度
	float cam_speed = 0.001f;
	switch (Game::GameMode)
	{
	//見下ろし
	case 0: {
		//見下ろし用の高さに変更
		m_pos.y = 40.0f;

		//定点カメラのキーでの横移動
		if (HOLD(CInput::eLeft)) m_pos.x += 0.5f;
		if (HOLD(CInput::eRight)) m_pos.x -= 0.5f;
		//定点カメラのキーでの縦移動
		if (HOLD(CInput::eUp)) m_pos.z += 0.5f;
		if (HOLD(CInput::eDown)) m_pos.z += -0.5f;

		//制限位置まで来た場合に制限ギリギリの位置まで押し出す
		//カメラの移動制限 後々フィールドごとに制限する値を用意してそれを条件式に追加
		//左側の制限
		if (m_pos.x >= 15.0f) {
			m_pos.x = 15.0f;
		}
		//右側の制限
		if (m_pos.x <= -15.0f) {
			m_pos.x = -15.0f;
		}
		//上側の制限
		if (m_pos.z >= 15.0f) {
			m_pos.z = 15.0f;
		}
		//下側の制限
		if (m_pos.z <= -50.0f) {
			m_pos.z = -50.0f;
		}

		//distを使ったズーム
		m_dist = min(15.0f, max(0.5f, m_dist - CInput::GetMouseWheel()));
		//TDカメラ専用の回転値
		CVector3D cam_rot = CVector3D(DtoR(70.0f), 0.0f, 0.0f);
		//カメラの座標を注視点に設定
		CVector3D at = m_pos;
		//distを使って注視点から引く
		CVector3D cam_pos = at + CMatrix::MRotation(cam_rot).GetFront() * -m_dist;
		//カメラを設定
		CCamera::GetCurrent()->LookAt(cam_pos, at, CVector3D(0.0f, 1.0f, 0.0f));
	}
		break;
	//一人称
	case 1: {
		//マウスの移動に合わせたカメラの回転
		CVector2D mouse_vec = CInput::GetMouseVec();
		m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0.0f) * cam_speed;
		//上下カメラ移動の制限
		m_rot.x = min(DtoR(45.0f), max(DtoR(-45.0f), m_rot.x));

		m_rot.y = Utility::NormalizeAngle(m_rot.y);
		//distを使ったズーム
		m_dist = min(10.0f, max(2.0f, m_dist - CInput::GetMouseWheel()));

		if (Task* t = TaskManager::FindObject(ePlayer)) {
			Player* p = static_cast<Player*>(t);
			CMatrix cam_matrix =
				CMatrix::MTranselate(p->GetPos())
				* CMatrix::MTranselate(CVector3D(0.0f, 1.1f, 0.0f)) * CMatrix::MRotation(m_rot)
				* CMatrix::MTranselate(CVector3D(-0.5f, 1.0f, 0.0f));
			//カメラのワールド行列でカメラを設定
			CCamera::GetCurrent()->SetTranseRot(cam_matrix);
		}
	}
		break;
	//三人称
	case 2: {
		//マウスの移動に合わせたカメラの回転
		CVector2D mouse_vec = CInput::GetMouseVec();
		m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0.0f) * cam_speed;
		//上下カメラ移動の制限
		m_rot.x = min(DtoR(45.0f), max(DtoR(-45.0f), m_rot.x));

		m_rot.y = Utility::NormalizeAngle(m_rot.y);
		//distを使ったズーム
		m_dist = min(10.0f, max(2.0f, m_dist - CInput::GetMouseWheel()));

		if (Task* t = TaskManager::FindObject(ePlayer)) {
			ObjectBase* b = static_cast<ObjectBase*>(t);
			CMatrix cam_matrix =
				CMatrix::MTranselate(b->GetPos())
				* CMatrix::MTranselate(CVector3D(0.0f, 1.1f, 0.0f)) * CMatrix::MRotation(m_rot)
				* CMatrix::MTranselate(CVector3D(-0.5f, 0.4f, -2.0f));
			//カメラのワールド行列でカメラを設定
			CCamera::GetCurrent()->SetTranseRot(cam_matrix);
		}
		//プレイヤーの取得
		if (Task* t = TaskManager::FindObject(ePlayer))
		{
			Player* p = static_cast<Player*>(t);
			//プレイヤーの座標(足元)+上に上昇した部分を注視点に設定
			CVector3D at = p->GetPos() + CVector3D(0.0f, 1.4f, 0.0f);
			//distを使って注視点から少し引く
			CVector3D cam_pos = at + CMatrix::MRotation(m_rot).GetFront() * -m_dist;
			//カメラを設定
			CCamera::GetCurrent()->LookAt(cam_pos, at, CVector3D(0.0f, 1.0f, 0.0f));
		}
	}
		break;
	default:
		break;
	}
}

void Camera::Zoom(ObjectBase* b) {
	//ターゲットへのベクトル(このままではターゲットの足元に行ってしまうので、高さ分y座標から引く)
	CVector3D target = b->GetPos() - m_pos;
	//ターゲットへ移動
	m_pos += target.GetNormalize() * 0.03f;
}