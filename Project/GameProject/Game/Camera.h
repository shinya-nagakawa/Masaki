#pragma once
#include "../Base/ObjectBase.h"

/*カメラ*/

class Camera : public ObjectBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Camera();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render() override;

	/// <summary>
	/// 指定のオブジェクトにズーム
	/// </summary>
	/// <param name="b">指定したオブジェクト</param>
	void Zoom(ObjectBase* b);

private:
	int old_GameMode;  //ゲームモード変更時の比較用
	float m_dist;      //目標にしているオブジェクトとの間隔
};