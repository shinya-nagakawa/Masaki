#pragma once
#include "../Base/CharaBase.h"

/*城*/

class Castle : public CharaBase {
private:
	CModelObj m_model; //モデルオブジェクト
	bool m_control;    //レベルアップ制御用

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">配置位置</param>
	Castle(const CVector3D& pos);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Castle();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render() override;
	/// <summary>
	/// ダメージを受ける
	/// </summary>
	/// <param name="damage">受けるダメージ量</param>
	void GetDamage(int damage);
	/// <summary>
	/// レベルを返却
	/// </summary>
	/// <returns></returns>
	int GetLevel();
	/// <summary>
	/// モデルを返却
	/// </summary>
	/// <returns>自身のモデル</returns>
	CModel* GetModel() override {
		return &m_model;
	}
};
