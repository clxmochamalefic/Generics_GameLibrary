#include "Generic_GameLibrary.h"

GglInputDevice			g_inputDevice;		// 入力デバイス管理						[( InputDevice.h	)]
GglFps					g_fps;				// Fps構造体のグローバル変数			[( Fps.h			)]
//GglImage*				g_imageArray;		// イメージデータ格納配列				[( Image.h			)]

GglLinkList			g_linkList;		// タスクシステム

GglMemoryList		g_memoryList;	// メモリ管理リスト
GglNetworkList		g_networkList;	// ネットワーク用ソケット構造体
GglMultiThreadList	g_multiThread;			// マルチスレッドハンドルリンクリスト