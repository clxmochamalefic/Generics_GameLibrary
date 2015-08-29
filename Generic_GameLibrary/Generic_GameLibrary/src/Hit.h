#ifndef GglHit_h__
#define GglHit_h__

#include "Definition.h"
#include "Vector3f.h"
#include "Rectangle.h"

/**
 * GglHit構造体
 * 当たり判定に必要な変数、関数ポインタを持つ
 */
struct GglHit
{
	GglBoolean		useHit;									// 当たり判定を使用するかどうかをフラグとして扱う
	GglBoolean		useSphere;								// 円形、球形当たり判定を使用するかどうかをフラグとして扱う

	GglVector3f*	hitPosition;							// インスタンスのポジション
	float			hitRadius;								// 当たり判定の半径（当たり判定はすべて円形で行う）
	GglRectangle	hitRect;								// 当たり判定の矩形

	GglObject*		(*HitEventArray)(GglObject, GglObject);	// 当たり判定時に呼ばれる関数アレイ
	int				HitEventFuncCount;						// 当たり判定時に呼ばれる関数アレイのアレイ最大数

}typedef GglHit;

#endif