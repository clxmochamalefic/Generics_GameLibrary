#include "Generic_GameLibrary.h"
/*********************************************************************************
 * GglSetRect関数
 * 画像の全体サイズ、及び画像の描画領域を指定してGglRect構造体に統一して出力します
 * 
 * 戻り値：GglRect構造体（画像サイズ、領域情報）
 * 引数：
 * 1.const float*	in_top(in_pTop)			//上
 * 2.const float*	in_bottom(in_pBottom)	//下
 * 3.const float*	in_left(in_pLeft)		//左
 * 4.const float*	in_right(in_pRight)		//右
*/
GglRectangle GglRectangle_Initialize( const int in_top,
											const int in_bottom,
											const int in_left,
											const int in_right)
{
	GglRectangle r;
	r.t	= in_top;
	r.b	= in_bottom;
	r.l	= in_left;
	r.r	= in_right;

	return r;
}

GglRectangle GglRectangle_LoadIdentity()
{
	return GglRectangle_Initialize(0, 0, 0, 0);
}

///****************************************************************
// * GglExchangeRect関数
// * GglRectangle情報をVertex2dなどの閾値(0.0~1.0)へ変換する
// * 
// * 戻り値：なし
// * 引数：
// * 1.GglRectangle*			out_pRect	変換後のGglRectangle情報
// * 2.const GglRectangle*	in_pRect	変換したいGglRectangle情報
// * 3.const pngInfo*	in_pInfo	画像の最大領域取得用
//*/
//void GglRectangle_ExchangeIdentity(GglRectangle* out_pRect,
//								const GglRectangle* in_pRect,
//								const pngInfo* in_pInfo)
//{
//	// 上
//	if(in_pRect->t > 0.0f)
//		out_pRect->t = in_pRect->t / in_pInfo->Height;
//	else if(in_pRect->t > (int)in_pInfo->Height)
//		out_pRect->t = 1.0f;
//	else
//		out_pRect->t = 0.0f;
//
//	// 下
//	if(in_pRect->b > 0.0f)
//		out_pRect->b = in_pRect->b / in_pInfo->Height;
//	else if(in_pRect->b > (int)in_pInfo->Height)
//		out_pRect->b = 1.0f;
//	else
//		out_pRect->t = 0;
//
//	// 左
//	if(in_pRect->l > 0)
//		out_pRect->l = in_pRect->l / in_pInfo->Width;
//	else if(in_pRect->l > (int)in_pInfo->Width)
//		out_pRect->l = 1.0f;
//	else
//		out_pRect->l = 0;
//
//	// 右
//	if(in_pRect->r > 0)
//		out_pRect->r = in_pRect->r / in_pInfo->Width;
//	else if(in_pRect->r > (int)in_pInfo->Width)
//		out_pRect->r = 1.0f;
//	else
//		out_pRect->r = 0;
//
//	return ;
//}
