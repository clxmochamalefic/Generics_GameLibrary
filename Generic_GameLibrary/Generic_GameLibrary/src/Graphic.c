#include "Generic_GameLibrary.h"

/******************************************************
 * GglPerspective関数
 * 描画モードを透視投影に切り替えます
 * 
 * 戻り値、引数：なし
*/
void GglGraphic_Perspective(void)
{
	glMatrixMode(GL_PROJECTION);						//行列モード切替
	glLoadIdentity();									//行列初期化

	gluPerspective( GglGraphic_PERS_FOVY,
					(double)GglGraphic_PERS_WIDTH / GglGraphic_PERS_HEIGHT, 
					GglGraphic_PERS_ZNEAR,
					GglGraphic_PERS_ZFAR);

	return ;
}

/******************************************************
 * GglOrtho2d関数
 * 描画モードを平行投影に切り替えます
 *
 * 戻り値、引数：なし
*/
void GglGraphic_Ortho2d(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(GglGraphic_ORTHO_LEFT, GglGraphic_ORTHO_RIGHT, GglGraphic_ORTHO_BOTTOM, GglGraphic_ORTHO_TOP);

	return ;
}

/****************************************************************
 * GglGraphic_DrawSpriteBegin関数
 * 2Dスプライトの描画の開始処理を行います
 * 実際には、2Dを描画する為に3D描画層よりも下の階層に降りています
 *
 * 戻り値：なし
 * 引数　：なし
*/
void GglGraphic_DrawSpriteBegin(void)
{
	glMatrixMode(GL_PROJECTION);			// 射影変換行列設定
	glPushMatrix();							// 現在の射影変換行列を保存
	gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);
	glLoadIdentity();
	glOrtho(0, GglGraphic_ORTHO_RIGHT, GglGraphic_ORTHO_BOTTOM, 0, -1, 1);	// 正射影変換設定
	
	glMatrixMode(GL_MODELVIEW);				// モデルビュー変換行列設定
	glPushMatrix();							// 現在のモデルビュー行列を保存
	glLoadIdentity();						// 単位行列を設定
}

/****************************************************************
 * GglGraphic_DrawSpriteEnd関数
 * 2Dスプライトの描画の終了処理を行います
 * 実際には、2Dを描画を終了するため、3D描画層へ戻っています
 *
 * 戻り値：なし
 * 引数　：なし
*/
void GglGraphic_DrawSpriteEnd(void)
{
	glMatrixMode(GL_PROJECTION);	// 射影変換行列設定
	glPopMatrix();					// 射影変換行列を復元
	glMatrixMode(GL_MODELVIEW);		// モデルビュー変換行列設定
	glPopMatrix();					// モデルビュー行列を復元
	glLoadIdentity();				// 単位行列を設定
}