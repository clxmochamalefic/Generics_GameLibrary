#ifndef GglMaterialList_h__
#define GglMaterialList_h__

#include "Color.h"
#include "Definition.h"

/****
 * GglMaterialList構造体
 * 上記のマテリアルデータを管理する構造体
**********************************************************/
struct GglMaterialList			// 3Dモデル用マテリアルリスト
{
	GglColor4	colorType;		// 拡散光、あるいは環境光
	int			lightPower;		// 鏡面光の指数
	GglColor4	specularColor;	// 鏡面光
	GglColor4	emissionColor;	// 放射輝度

	GglString	textureName;	// テクスチャ画像名

}typedef GglMaterialList;

#endif