#include "Generic_GameLibrary.h"

/*******************************************************************************
 * GglColor4_AssembleElements関数
 * 画像に付加する色を256で指定して、それをGglColorRGBA構造体に統一して出力します
 *
 * 戻り値：GglColor4構造体（色情報）
 * 引数：
 * 1.const int		in_r256		//赤色
 * 2.const int		in_g256		//緑色
 * 3.const int		in_b256		//青色
 * 4.const int		in_a256		//アルファ情報
 * 5.GglColorRGBA	out_pColor	//GglColorRGBA出力
*/
GglColor4 GglColor4_Initialize(const unsigned char in_r256, const unsigned char in_g256, const unsigned char in_b256, const unsigned char in_a256)
{
	GglColor4 c;

	c.array[0] = GglColor_BYTE2FLOAT(in_r256);
	c.array[1] = GglColor_BYTE2FLOAT(in_g256);
	c.array[2] = GglColor_BYTE2FLOAT(in_b256);
	c.array[3] = GglColor_BYTE2FLOAT(in_a256);

	return c;
}

GglColor4 GglColor4_LoadIdentity()
{
	return GglColor4_Initialize(0, 0, 0, 0);
}