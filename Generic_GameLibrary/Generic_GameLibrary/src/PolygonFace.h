#ifndef GglPolygonFace_h__
#define GglPolygonFace_h__

#include "Definition.h"
#include "Vector2.h"

/****
 * GglPolygonFace構造体
 * ポリゴンと面情報を持つ
***********************************************************/
struct GglPolygonFace
{
	GglBoolean	useFourPolygon;	// 四角ポリゴン使用フラグ
	GglBoolean	useTexture;		// テクスチャ使用フラグ
	int			index[4];		// 使用するバーテクス情報
	int			materialIndex;	// 面に対応するマテリアルのインデックス情報（GglModel.fMaxから動的確保）
	GglVector2d	uv;				// uv座標情報

}typedef GglPolygonFace;

#endif