#include <stdlib.h>
#include "Generic_GameLibrary.h"

///*****************************************
// * GglGraphic2d_DrawSprite関数
// * 2Dポリゴン及びテクスチャを描画します
// *
// * 戻り値：なし
// * 引数：
// * 1.GglImage*		in_pImage	//イメージ本体
// * 2.GglRectangle*		in_pRect	//描画範囲
// * 3.GglVector3f*	in_pVec		//描画位置
// * 4.GglColor4*	in_pColor	//描画色
//*/
//void GglGraphic2d_DrawSprite(GglImage* in_pImage, GglRectangle* in_pRect, GglVector3f* in_pVec, GglColor4* in_pColor)
//{
//	//GglGraphic_Ortho2d();
//	
//	GglGraphic_DrawSpriteBegin();
//
//	glEnable(GL_ALPHA_TEST);
//	glEnable(GL_BLEND);
//
//	glEnable(GL_TEXTURE_2D);
//	glBegin(GL_QUADS);
//
//		glTexCoord2d(in_pRect->l / in_pImage->width, in_pRect->t / in_pImage->height);
//		glVertex2d(in_pVec->x,									in_pVec->y);
//
//		glTexCoord2d(in_pRect->r / in_pImage->width, in_pRect->t / in_pImage->height);
//		glVertex2d(in_pVec->x + (in_pRect->r - in_pRect->l),	in_pVec->y);
//
//		glTexCoord2d(in_pRect->r / in_pImage->width, in_pRect->b / in_pImage->height);
//		glVertex2d(in_pVec->x + (in_pRect->r - in_pRect->l),	in_pVec->y + (in_pRect->b - in_pRect->t));
//
//		glTexCoord2d(in_pRect->l / in_pImage->width, in_pRect->b / in_pImage->height);
//		glVertex2d(in_pVec->x,									in_pVec->y + (in_pRect->b - in_pRect->t));
//		
//
//	glEnd();
//	
//	GglGraphic_DrawSpriteEnd();
//
//}
//
//
/*****************************************
 * GglGraphic2d_DrawSprite関数
 * 2Dポリゴン及びテクスチャを描画します
 *
 * 戻り値：なし
 * 引数：
 * 1.GglImage*		in_pImage	//イメージ本体
 * 2.GglRectangle*		in_pRect	//描画範囲
 * 3.GglVector3f*	in_pVec		//描画位置
 * 4.GglColor4*	in_pColor	//描画色
*/
void GglGraphic2d_DrawSprite(GglImage* in_pImage, GglVector2i* in_pSize, GglRectangle* in_pRect, GglVector3f* in_pVec, GglColor4* in_pColor)
{
	GglGraphic_DrawSpriteBegin();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glAlphaFunc(GL_ALWAYS, 0.5);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, in_pImage->id);
	gluPerspective(GglGraphic_PERS_FOVY, (double)GglGraphic_PERS_WIDTH / GglGraphic_PERS_HEIGHT, GglGraphic_PERS_ZNEAR, GglGraphic_PERS_ZFAR);
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);

		//glTexCoord2d(in_pRect->l / in_pImage->size.x, in_pRect->t / in_pImage->size.y);
		//glVertex2d(in_pVec->x,					in_pVec->y);

		//glTexCoord2d(in_pRect->r / in_pImage->size.x, in_pRect->t / in_pImage->size.y);
		//glVertex2d(in_pVec->x + in_pSize->x,	in_pVec->y);

		//glTexCoord2d(in_pRect->r / in_pImage->size.x, in_pRect->b / in_pImage->size.y);
		//glVertex2d(in_pVec->x + in_pSize->x,	in_pVec->y + in_pSize->y);

		//glTexCoord2d(in_pRect->l / in_pImage->size.x, in_pRect->b / in_pImage->size.y);
		//glVertex2d(in_pVec->x,					in_pVec->y + in_pSize->y);

		glTexCoord2d(0.0, 0.0);
		glVertex2d(in_pVec->x, in_pVec->y);

		glTexCoord2d(1.0, 0.0);
		glVertex2d(in_pVec->x + in_pSize->x, in_pVec->y);

		glTexCoord2d(1.0, 1.0);
		glVertex2d(in_pVec->x + in_pSize->x, in_pVec->y + in_pSize->y);

		glTexCoord2d(0.0, 1.0);
		glVertex2d(in_pVec->x, in_pVec->y + in_pSize->y);
		
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	
	GglGraphic_DrawSpriteEnd();
}
//
///********************************************************************
// * GglGraphic2d_DrawLine2d関数
// * 引数の情報を元に2D直線を描画します
// *
// * 戻り値：なし
// * 引数：
// * 1.const GglVector3f* in_pOrigin		// 直線の始点
// * 2.const GglVector3f* in_pEndPoint	// 直線の終点
// * 3.const GglColor4*	in_pColor		// 直線の色
//*/
//void GglGraphic2d_DrawLine2d(GglVector3f* in_pOrigin, GglVector3f* in_pEndPoint, GglColor4* in_pColor)
//{
//	GglGraphic_Ortho2d();
//
//	//glPushMatrix();
//	//	GglTranslatef(in_pOrigin);
//	//glPopMatrix();
//
//	GglGraphic2d_Color3dv(in_pColor);
//
//	glBegin(GL_LINE_STRIP);
//		GglVector3f_Vertex3dv(in_pOrigin);
//		GglVector3f_Vertex3dv(in_pEndPoint);
//	glEnd();
//
//	return ;
//}

/*****************************************************************
 * GglGraphic2d_Color3dv関数(アルファ値なし)
 * GglGraphic2d_Color4dv関数(アルファ値あり)
 * 描画色を指定します
 *
 * 戻り値：なし
 * 引数：
 * 1.const GglColorRGBA* in_pColor	//トランスレーションする色情報
*/
void GglGraphic2d_Color3dv(const GglColor4* in_pColor)		//アルファなし
{
	glColor3d(in_pColor->r, in_pColor->g, in_pColor->b);
	return ;
}

void GglGraphic2d_Color4dv(const GglColor4* in_pColor)		//アルファあり
{
	glColor4d(in_pColor->r, in_pColor->g, in_pColor->b, in_pColor->a);
	return ;
}

/*************************************
 * GglMaterialfv関数
 * テクスチャマテリアルを変更します
 *
 * 戻り値：なし
 * 引数：
 * 1.const GLenum in_targetFace
 * 2.const GLenum in_lightingMaterial
 * 3.const GglColor4 in_color
*/
void GglGraphic2d_Materialfv(const GLenum	in_targetFace,
							const GLenum	in_lightingMaterial,
							const GglColor4*	in_pColor)
{
	float color[4];

	if(in_pColor == NULL)	return ;

	color[0] = in_pColor->r;
	color[1] = in_pColor->g;
	color[2] = in_pColor->b;
	color[3] = in_pColor->a;

	glMaterialfv(in_targetFace, in_lightingMaterial, color);

	return ;
}