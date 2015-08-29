#ifndef InputDevice_h__
#define InputDevice_h__

#include "Definition.h"

/**
 * GglInputDevice構造体
 * glutKeyboardFuncなどで取得されるキーボード情報や
 * マウスのボタン情報などを取得します
 */
struct GglInputDevice
{
	GglByte	keyState[256];	// キーボードの入力情報を保持します
	int		mouseButton;	// マウスの入力情報を保持します
	int		mouseState;		// マウスのボタンの状態を保持します
	int		mouseX;			// それぞれの操作時のマウスのX座標を保持します
	int		mouseY;			// それぞれの操作時のマウスのY座標を保持します

}typedef GglInputDevice;

void GglInputDevice_GetKeyboardState(void);
void GglInputDevice_Mouse(int in_button, int in_state, int in_x, int in_y);

#endif