#ifndef GglFps_h__
#define GglFps_h__

#include "Definition.h"

/**
 * GglFps構造体
 * 画面更新時間情報をまとめている
 */
struct GglFps
{
	GglClock	countMode;			// １秒間に何度更新するかを保存する
	GglClock	leaveTime;			// 前回の更新の時間を保存する
	GglClock	secondTime;			// １秒前の更新の時間を保存する
	int			nowCount	: 8;	// １秒間に何度Fpsを更新したかをカウントする
	int			secondCount	: 8;	// 前回の１秒間にどれくらい更新されたかを保存する

}typedef GglFps;

#endif