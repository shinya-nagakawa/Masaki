#pragma once
#include "../Base/CharaBase.h"

/*城*/

class Castle : public CharaBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
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
	/// モデルを取得
	/// </summary>
	/// <returns>自身のモデル</returns>
	CModel* GetModel() override {
		return &m_model;
	}

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage">受けるダメージ</param>
	void GetDamage(int damage);
	/// <summary>
	/// レベルを返却
	/// </summary>
	/// <returns>現在のレベル</returns>
	int GetLevel() const;

private:
	CModelObj m_model;          //モデルオブジェクト
	bool m_control;             //レベルアップ制御用
};
