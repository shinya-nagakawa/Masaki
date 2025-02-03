#include "SkyBox.h"

SkyBox::SkyBox()
	: skybox(COPY_RESOURCE("Sky", CModelObj)){
	for (int i = 0; i < skybox.GetMaterialSize(); i++) {
		if (CTexture* t = skybox.GetMaterial(i)->mp_texture) {
			//テクスチャーの貼り方変更
			t->SetWrapST(GL_CLAMP_TO_EDGE);
			t->SetFilter(GL_LINEAR);
		}
	}
}

void SkyBox::Render() {
	//深度テストOFF
	//ここでの描画は深度バッファへ影響しない
	glDisable(GL_DEPTH_TEST);
	//ライティングOFF
	CLight::SetLighting(false);
	//現在使用中のカメラのビュー行列を取得
	CMatrix matrix = CCamera::GetCurrent()->GetViewMatrix();
	//現在のビュー行列をバックアップ
	CMatrix back = matrix;
	//ビュー行列の座標を無効に
	matrix.m03 = 0; matrix.m13 = 0; matrix.m23 = 0;
	//スカイボックス用のビュー行列設定
	CCamera::GetCurrent()->SetViewMatrix(matrix);
	//スカボックス描画
	skybox.Render();

	//カメラのビュー行列を元に戻す
	CCamera::GetCurrent()->SetViewMatrix(back);
	//元の設定に戻す
	//ライティング有効
	CLight::SetLighting(true);
	//深度テストON
	glEnable(GL_DEPTH_TEST);
}