/***************************************************************************************
 *
 * Generic_GameLibrary for Windows Version 1.0.0.private alpha
 *
 * Generic_GameLibraryはOpenGLを使用したゲームライブラリです。
 * 開発者：Cocoalix
 *
***************************************************************************************/
#ifndef Generic_GameLibrary_H
#define Generic_GameLibrary_H

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glut32.lib")

#ifdef _DEBUG

//#pragma comment(lib, "glpngd.lib")
#pragma comment(lib, "libpngd.lib")
#pragma comment(lib, "libpng15d.lib")
#pragma comment(lib, "zlibd.lib")
#pragma comment(lib, "zlib1d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_core240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_highgui240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_video240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_ml240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_legacy240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_imgproc240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_objdetect240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_features2d240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_contrib240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_calib3d240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_flann240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_gpu240d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbb_debug.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbb_preview_debug.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbbmalloc_debug.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbbmalloc_proxy_debug.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbbproxy_debug.lib")

#else

//#pragma comment(lib, "glpng.lib")
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "libpng15.lib")
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "zlib1.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_core240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_highgui240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_video240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_ml240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_legacy240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_imgproc240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_objdetect240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_features2d240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_contrib240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_calib3d240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_flann240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\x86\\vc9\\lib\\opencv_gpu240.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbb.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbb_preview.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbbmalloc.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbbmalloc_proxy.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\opencv\\build\\common\\tbb\\lib\\ia32\\vc9\\tbbproxy.lib")

#endif

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "glew.h"
#include "glut.h"
#include "glext.h"
//#include "glpng.h"
#include "wglew.h"
#include "Ggl_Keys.h"
#include "png.h"
#include "zlib.h"

/********************************************* 別名定義 *********************************************/
typedef char*			GglString;		// 文字列型
typedef char			GglByte;		// バイト型(1byte)
typedef unsigned char	GglUByte;		// 符号なしバイト型(1byte)
typedef void*			GglObject;		// オブジェクト型(注意、汎用ポインタ(void*)です)
typedef unsigned int	GglSize;		// サイズ型 32bitマシンでのsize_tと等価
typedef clock_t			GglClock;		// クロック型 Windowsのclock_tと等価
typedef unsigned int*	GglSocket;

/*
**************** 定数 ****************
*/
#define GGL_SYSTEMVER					("1.0.0.PrivateBeta")	// システムバージョン文字列

#define GGL_PI							(3.14159265358979)		// 円周率
#define GGL_GRAVITY_FACTOR				(-0.098)				// 重力
#define GglNetwork_USE_LOCALHOST		("localhost")			// ネットワーク用自IP文字列

#define GGL_FILE_READ_MODE				("r")
#define GGL_FILE_WRITE_MODE				("w")
#define GGL_FILE_ADD_MODE				("a")
#define GGL_FILE_READ_PLUS				("r+")
#define GGL_FILE_WRITE_PLUS				("w+")
#define GGL_FILE_ADD_PLUS				("a+")

#define GGL_FILE_READ_BINALY			("rb")
#define GGL_FILE_WRITE_BINALY			("wb")
#define GGL_FILE_ADD_BINALY				("ab")
#define GGL_FILE_READ_BINPLUS			("rb+")
#define GGL_FILE_WRITE_BINPLUS			("wb+")
#define GGL_FILE_ADD_BINPLUS			("ab+")

// Link.h
#define GglLinkList_MAXTASK			(1024)					// タスク登録最大数

// Graphic.h
#define GglGraphic_PERS_WIDTH			(800.0)					//
#define GglGraphic_PERS_HEIGHT			(600.0)
#define GglGraphic_PERS_ZNEAR			(0.0)

#define GglGraphic_PERS_ZFAR			(100.0)
#define GglGraphic_PERS_FOVY			(60.0)

#define GglGraphic_ORTHO_TOP			(0.0)
#define GglGraphic_ORTHO_BOTTOM			(103.9231)
#define GglGraphic_ORTHO_LEFT			(0.0)

#define GglGraphic_ORTHO_RIGHT			(103.9231)
#define GglGraphic_ORTHO_ZNEAR			(0.0)
#define GglGraphic_ORTHO_ZFAR			(100.0)

// Fps.h
#define GglFps_ONE_FRAME_FOR_SIXTY		((GglClock)14)			// FPS60用
#define GglFps_ONE_FRAME_FOR_THIRTY		((GglClock)25)			// FPS30用
#define GglFps_ONE_FRAME_FOR_FIFTEEN	((GglClock)60)			// FPS15用

#define GGL_MAX_STRING_LENGTH			(256)


/*
**************** マクロ ***************
*/
// Debug Tools
#ifdef GGL_USE_DEBUG

#define GglDebug_PrintExceptionLine()					printf("\n**********iiCatch Exception!!**********\nfrom : %s [L%d]\n", __FILE__, __LINE__)
#define GglDebug_PrintAlertLine(str)					printf("\n*****iiALERT!!*****\nSummary : %s\nfrom : %s [L%d]\n", str, __FILE__, __LINE__)
#define GglDebug_PrintInformationLine(str)				printf("\n----- Information -----\nSummary : %s\n   from : %s [L%d]\n", str, __FILE__, __LINE__)

#else

#define GglDebug_PrintExceptionLine()
#define GglDebug_PrintAlertLine(str)
#define GglDebug_PrintInformationLine(str)

#endif

// 演算系
#define GGL_TORAD(x)									(x * GGL_PI / 180)					// 度数からラジアンへ
#define GGL_TODEG(x)									(x * 180 / GGL_PI)					// ラジアンから度数へ
#define GGL_POW2(x)										(x * x)								// 二乗
#define GglColor_BYTE2FLOAT(x)							(x/255)								// 色を0~256から0.0~1.0に表現する(Color.h)

// その他
#define GglVector3f_Normal3(x, y, z)					GglVector3f_Set(x, y, z)				// 関数別名(GglVector3f.h)
#define GglVector3d_Normal3d(x, y, z)					GglVector3d_Set(x, y, z)			// 関数別名(Vector3d.h)

// Network
#define GglNetwork_CloseSocket(x)						closesocket(x)

// MultiThread
#define GglMultiThread_BeginThread(func, size, arg)		_beginthread(func, size, arg)			// 関数別名 スレッドを作成
#define GglMultiThread_EndThread()						_endthread()

#define GglMultiThread_CreateMutex(attr, owner, name)	CreateMutex(attr, owner, __name)
#define GglMultiThread_CloseMutex(x)					CloseHandle(x)

#define GglMultiThread_InitializeCriticalSection(x)		InitializeCriticalSection(x)
#define GglMultiThread_DeleteCriticalSection(x)			DeleteCriticalSection(x)
#define GglMultiThread_EnterCriticalSection(x)			EnterCriticalSection(x)

#define GglMultiThread_LeaveCriticalSection(x)			LeaveCriticalSection(x)

// InputDevice
#define GglInputDevice_KeyDown(x)						(g_inputDevice.keyState[x] & 0x80)

// foreach文
#define GGL_FOREACH(val, init, terms, cont)				if((init)!=NULL)	for((val)=(init);(val)!=(terms)&&(val)!=NULL;(val)=(val)->cont)

// New
#define GGL_NEW(type,cnt)			(type*)GglMemory_New(sizeof(type)*cnt)

#define GglBoolean_NEW(cnt)			GGL_NEW(GglBoolean,cnt)
#define GglLinkStatus_NEW(cnt)		GGL_NEW(GglLinkStatus,cnt)
#define GglLinkPriority_NEW(cnt)	GGL_NEW(GglLinkPriority,cnt)

#define GglVector2f_NEW(cnt)		GGL_NEW(GglVector2f,cnt)
#define GglVector2d_NEW(cnt)		GGL_NEW(GglVector2d,cnt)
#define GglVector2i_NEW(cnt)		GGL_NEW(GglVector2i,cnt)

#define GglVector3f_NEW(cnt)		GGL_NEW(GglVector3f,cnt)
#define GglVector3d_NEW(cnt)		GGL_NEW(GglVector3d,cnt)
#define GglVector3i_NEW(cnt)		GGL_NEW(GglVector3i,cnt)

#define GglVector4f_NEW(cnt)		GGL_NEW(GglVector4f,cnt)
#define GglVector4d_NEW(cnt)		GGL_NEW(GglVector4d,cnt)
#define GglVector4i_NEW(cnt)		GGL_NEW(GglVector4i,cnt)

#define GglColor3_NEW(cnt)			GGL_NEW(GglColor3,cnt)
#define GglColor4_NEW(cnt)			GGL_NEW(GglColor4,cnt)
#define GglFps_NEW(cnt)				GGL_NEW(GglFps,cnt)

#define GglRectangle_NEW(cnt)		GGL_NEW(GglRectangle,cnt)
#define GglHit_NEW(cnt)				GGL_NEW(GglHit,cnt)
#define GglImage_NEW(cnt)			GGL_NEW(GglImage,cnt)

#define GglInputDevice_NEW(cnt)		GGL_NEW(GglInputDevice,cnt)
#define GglMatrix3x3_NEW(cnt)		GGL_NEW(GglMatrix3x3,cnt)
#define GglMatrix4x4_NEW(cnt)		GGL_NEW(GglMatrix4x4,cnt)

#define GglMemory_NEW(cnt)			GGL_NEW(GglMemory,cnt)
#define GglMemoryList_NEW(cnt)		GGL_NEW(GglMemoryList,cnt)
#define GglMaterialList_NEW(cnt)	GGL_NEW(GglMaterialList,cnt)

#define GglPolygonFace_NEW(cnt)		GGL_NEW(GglPolygonFace,cnt)
#define GglVertex_NEW(cnt)			GGL_NEW(GglVertex,cnt)
#define GglFace_NEW(cnt)			GGL_NEW(GglFace,cnt)

#define GglMaterial_NEW(cnt)		GGL_NEW(GglMaterial,cnt)
#define GglModel_NEW(cnt)			GGL_NEW(GglModel,cnt)
#define GglThread_NEW(cnt)			GGL_NEW(GglThread,cnt)

#define GglMultiThreadList_NEW(cnt)	GGL_NEW(GglMultiThreadList,cnt)
#define GglLink_NEW(cnt)			GGL_NEW(GglLink,cnt)
#define GglLinkList_NEW(cnt)		GGL_NEW(GglLinkList,cnt)

#define GglSocketNode_NEW(cnt)		GGL_NEW(GglSocketNode,cnt)
#define GglNetworkList_NEW(cnt)		GGL_NEW(GglNetworkList,cnt)


// Vector演算
// 初期化
#define GglVector2_Set(_tgt, _x, _y)				((_tgt).x=(_x));((_tgt).y=(_y))
#define GglVector3_Set(_tgt, _x, _y, _z)			((_tgt).x=(_x));((_tgt).y=(_y));((_tgt).z=(_z))
#define GglVector4_Set(_tgt, _x, _y, _z, _q)		((_tgt).x=(_x));((_tgt).y=(_y));((_tgt).z=(_z));((_tgt).q=(_q))

#define GglVector2_SetInitialize(_out)				GglVector2_Set(_out, 0.0, 0.0)
#define GglVector3_SetInitialize(_out)				GglVector3_Set(_out, 0.0, 0.0, 0.0)
#define GglVector4_SetInitialize(_out)				GglVector4_Set(_out, 0.0, 0.0, 0.0, 0.0)

#define GglVector2_SetEqual(_x, _y)					{(_x), (_y)}
#define GglVector3_SetEqual(_x, _y, _z)				{(_x), (_y), (_z)}
#define GglVector4_SetEqual(_x, _y, _z, _q)			{(_x), (_y), (_z), (_q)}

#define GglVector2_SetInitializeEqual()				GglVector2_SetEqual(0.0, 0.0)
#define GglVector3_SetInitializeEqual()				GglVector3_SetEqual(0.0, 0.0, 0.0)
#define GglVector4_SetInitializeEqual()				GglVector4_SetEqual(0.0, 0.0, 0.0, 0.0)

// 加算
#define GglVector2_Add(_out, _a, _b)				GglVector2_Set(_out, (_a).x+(_b).x, (_a).y+(_b).y)
#define GglVector3_Add(_out, _a, _b)				GglVector3_Set(_out, (_a).x+(_b).x, (_a).y+(_b).y, (_a).z+(_b).z)
#define GglVector4_Add(_out, _a, _b)				GglVector4_Set(_out, (_a).x+(_b).x, (_a).y+(_b).y, (_a).z+(_b).z, (_a).q+(_b).q)

#define GglVector2_AddEqual(_a, _b)					GglVector2_SetEqual((_a).x+(_b).x, (_a).y+(_b).y)
#define GglVector3_AddEqual(_a, _b)					GglVector3_SetEqual((_a).x+(_b).x, (_a).y+(_b).y, (_a).z+(_b).z)
#define GglVector4_AddEqual(_a, _b)					GglVector4_SetEqual((_a).x+(_b).x, (_a).y+(_b).y, (_a).z+(_b).z, (_a).q+(_b).q)

// 減算
#define GglVector2_Sub(_out, _a, _b)				GglVector2_Set(_out, (_a).x-(_b).x, (_a).y-(_b).y)
#define GglVector3_Sub(_out, _a, _b)				GglVector3_Set(_out, (_a).x-(_b).x, (_a).y-(_b).y, (_a).z-(_b).z)
#define GglVector4_Sub(_out, _a, _b)				GglVector4_Set(_out, (_a).x-(_b).x, (_a).y-(_b).y, (_a).z-(_b).z, (_a).q-(_b).q)

#define GglVector2_SubEqual(_a, _b)					GglVector2_SetEqual((_a).x-(_b).x, (_a).y-(_b).y)
#define GglVector3_SubEqual(_a, _b)					GglVector3_SetEqual((_a).x-(_b).x, (_a).y-(_b).y, (_a).z-(_b).z)
#define GglVector4_SubEqual(_a, _b)					GglVector4_SetEqual((_a).x-(_b).x, (_a).y-(_b).y, (_a).z-(_b).z, (_a).q-(_b).q)

// 内積
#define GglVector2_Dot(_a, _b)						(((_a).x*(_b).x)+((_a).y*(_b).y))
#define GglVector3_Dot(_a, _b)						(((_a).x*(_b).x)+((_a).y*(_b).y)+((_a).z*(_b).z))
#define GglVector4_Dot(_a, _b)						(((_a).x*(_b).x)+((_a).y*(_b).y)+((_a).z*(_b).z)+((_a).q*(_b).q))

// 外積
#define GglVector2_Cross(_a, _b)					((_a.x*_b.y)-(_a.y*_b.x))
#define GglVector3_Cross(_out, _a, _b)				GglVector3_Set((_out), ((_a).y*(_b).z-(_a).z*(_b).y), ((_a).z*(_b).x-(_a).x*(_b).z), ((_a).x*(_b).y-(_a).y*(_b).x))
#define GglVector3_CrossEqual(_a, _b)				GglVector3_SetEqual(((_a).y*(_b).z-(_a).z*(_b).y), ((_a).z*(_b).x-(_a).x*(_b).z), ((_a).x*(_b).y-(_a).y*(_b).x))
//#define GglVector4_Cross(_out, _a, _b)		

// ベクトルスカラー倍
#define GglVector2_MulScalar(_vec, _out, _scl)		((_out).x)=((_vec).x)*(_scl); ((_out).y)=((_vec).y)*(_scl)
#define GglVector3_MulScalar(_vec, _out, _scl)		((_out).x)=((_vec).x)*(_scl); ((_out).y)=((_vec).y)*(_scl); ((_out).z)=((_vec).z)*(_scl)
#define GglVector4_MulScalar(_vec, _out, _scl)		((_out).x)=((_vec).x)*(_scl); ((_out).y)=((_vec).y)*(_scl); ((_out).z)=((_vec).z)*(_scl); ((_out).q)=((_vec).q)*(_scl)

// バーテクス設定
#define GglVector2_Vertex2dv(_src, _type)			(glVertex2##_type##v(_src))
#define GglVector3_Vertex3dv(_src, _type)			(glVertex3##_type##v(_src))

// 法線設定
#define GglVector2_Normal2(_src, _type)				(glNormal2##_type(((_src).x), ((_src).y)))
#define GglVector3_Normal3(_src, _type)				(glNormal3##_type(((_src).x), ((_src).y)))
#define GglVector_Normalv(_src, _dim, _type)		(glNormal##_dim##_type(_src))

// 平行移動
#define GglVector_Translate(_src, _type)			(glTranslate##_type(((_src).x), ((_src).y), ((_src).z)))
#define GglVector_Translatev(_src, _type)			(glTranslate##_type##d(_src))

// 正規化
#define GglVector2_Normalize(_src, _out)			{double s = sqrt(GGL_POW2((_src).x)+GGL_POW2((_src).y)); (_out).x=(_src).x/s; (_out).y=(_src).y/s;}
#define GglVector3_Normalize(_src, _out)			{double s = sqrt(GGL_POW2((_src).x)+GGL_POW2((_src).y)+GGL_POW2((_src).z)); (_out).x=(_src).x/s; (_out).y=(_src).y/s; (_out).z=(_src).z/s;}
#define GglVector4_Normalize(_src, _out)			{double s = sqrt(GGL_POW2((_src).x)+GGL_POW2((_src).y)+GGL_POW2((_src).z)+GGL_POW2((_src).q)); (_out).x=(_src).x/s; (_out).y=(_src).y/s; (_out).z=(_src).z/s; (_out).q=(_src).q/s;}

// ベクトル長さ
#define GglVector2_GetLength(_vec)					(sqrt(GGL_POW2((_vec).x)+GGL_POW2((_vec).y)))
#define GglVector3_GetLength(_vec)					(sqrt(GGL_POW2((_vec).x)+GGL_POW2((_vec).y)+GGL_POW2((_vec).z)))

// 加速度
#define GglVector_Accel(_vi, _accl, _time)			((_vi)+(_accl)*(_time))

// 重力加速度
#define GglVector_GravityAccel(_vi, time)			((_vi)*(_time)+(GGL_GRAVITY_FACTOR/2)*(GGL_POW2((_time))))


/********************************************* 列挙定義 *********************************************/

/****
 * GglBoolean列挙体
 * ブーリアンを持つ
**********************************************************/
enum GglBoolean			// ブーリアン
{
	GglFalse,			// 偽(=0)
	GglTrue				// 真(=1)

}typedef GglBoolean;

/****
 * GglLinkStatus列挙体
 * オブジェクトの状態を表現する
************************************************************/
enum GglLinkStatus
{
	StatusDelete,	//オブジェクト削除
	StatusSleep,	//オブジェクトは実行から外されるが削除されない
	StatusLive		//オブジェクト実行

}typedef GglLinkStatus;

/****
 * GglLinkPriority列挙体
 * オブジェクトの描画順番を表現する
************************************************************/
enum GglLinkPriority
{
	PrioLinkHead,		// LinkTaskのHeadを表す	常に先頭
	PrioEmergency,		// 緊急を表す プレイヤーよりも早く動かしたい時に使う
	PrioPlayer,			// 基本的にプレイヤーオブジェクトを表す
	PrioCharactor,		// プレイヤー以外のキャラクターオブジェクト
	PrioObject,			// 普通のオブジェクト
	PrioBackground,		// 背景など、バックグラウンドシステムなどに
	PrioOther,			// その他のオブジェクト
	PrioLinkTail		// LinkTaskのTail		常に最後

}typedef GglLinkPriority;





/**************************************** 構造体(共用体)定義 ****************************************/

/*********************************************************************************
								ベクトル関係
*********************************************************************************/

/****
 * GglVector2f共用体
 * ベクトルを表す共用体
**********************************************************/
union GglVector2f
{
	struct
	{
		float x;	// X座標
		float y;	// Y座標
	};

	float array[2];	// 配列([0] = x, [1] = y)

}typedef GglVector2f;

/****
 * GglVector2d共用体
 * ベクトルを表す共用体
**********************************************************/
union GglVector2d
{
	struct
	{
		double x;			// X座標
		double y;			// Y座標
	};

	double array[2];		// 配列([0] = x, [1] = y)

}typedef GglVector2d;

/****
 * GglVector2i共用体
 * ベクトルを表す共用体
**********************************************************/
union GglVector2i
{
	struct
	{
		int x;		// X座標
		int y;		// Y座標
	};

	int array[2];	// 配列([0] = x, [1] = y)

}typedef GglVector2i;




/****
 * GglVector3f共用体
 * ベクトルを表す共用体
 * typedefによって法線情報も表す
**********************************************************/
union GglVector3f
{
	struct
	{
		float x;	// x座標
		float y;	// y座標
		float z;	// z座標
	};

	float array[3];	// 配列([0] = x, [1] = y, [2] = z)

}typedef GglVector3f, GglNormal3f;

/****
 * GglVector3d共用体
 * ベクトルを表す共用体
 * typedefによって法線情報も表す
**********************************************************/
union GglVector3d
{
	struct
	{
		double x;		// x座標
		double y;		// y座標
		double z;		// z座標
	};

	double array[3];	// 配列([0] = x, [1] = y, [2] = z)

}typedef GglVector3d, GglNormal3d;

/****
 * GglVector3i共用体
 * ベクトルを表す共用体
 * typedefによって法線情報も表す
**********************************************************/
union GglVector3i
{
	struct
	{
		int x;		// x座標
		int y;		// y座標
		int z;		// z座標
	};

	int array[3];	// 配列([0] = x, [1] = y, [2] = z)

}typedef GglVector3i, GglNormal3i;



/****
 * GglVector4f共用体
 * ベクトルを表す共用体
**********************************************************/
union GglVector4f
{
	struct
	{
		float x;	// x座標
		float y;	// y座標
		float z;	// z座標
		
		float q;	// クオータニオン等
	};

	float array[4];	// 配列([0] = x, [1] = y, [2] = z, [3] = q)

}typedef GglVector4f;

/****
 * GglVector4d共用体
 * ベクトルを表す共用体
**********************************************************/
union GglVector4d
{
	struct
	{
		double x;		// x座標
		double y;		// y座標
		double z;		// z座標
		
		double q;		// クオータニオン等

	};

	double array[4];	// 配列([0] = x, [1] = y, [2] = z, [3] = q)

}typedef GglVector4d;

/****
 * GglVector4i共用体
 * ベクトルを表す共用体
**********************************************************/
union GglVector4i
{
	struct
	{
		int x;		// x座標
		int y;		// y座標
		int z;		// z座標
		
		int q;		// クオータニオン等
	};

	int array[4];	// 配列([0] = x, [1] = y, [2] = z, [3] = q)

}typedef GglVector4i;



/****
 * GglColor3共用体
 * 色情報を32bitカラーで纏められている
**********************************************************/
union GglColor3
{
	struct
	{
		float r;	// Red
		float g;	// Green
		float b;	// Blue
	};

	float array[3];	// 配列([0] = red, [1] = green, [2] = blue)

}typedef GglColor3;

/****
 * GglColor4共用体
 * 色情報を32bitカラーで纏められている
**********************************************************/
union GglColor4
{
	struct
	{
		float r;	// Red
		float g;	// Green
		float b;	// Blue
		float a;	// Alpha
	};

	float array[4];	// 配列([0] = red, [1] = green, [2] = blue, [3] = alpha)

}typedef GglColor4;




/****
 * GglFps構造体
 * 画面更新時間情報をまとめている
**********************************************************/
struct GglFps
{
	GglClock	countMode;			// １秒間に何度更新するかを保存する
	GglClock	leaveTime;			// 前回の更新の時間を保存する
	GglClock	secondTime;			// １秒前の更新の時間を保存する
	int			nowCount	: 8;	// １秒間に何度Fpsを更新したかをカウントする
	int			secondCount	: 8;	// 前回の１秒間にどれくらい更新されたかを保存する

}typedef GglFps;




/****
 * GglRectangle構造体
 * 矩形を表す構造体
**********************************************************/
union GglRectangle
{
	struct
	{
		int t;		// top		上
		int l;		// left		左
		int b;		// bottom	下
		int r;		// right	右
	};

	int array[4];	// 配列([0] = top, [1] = left, [2] = bottom, [3] = right)

}typedef GglRectangle;




/****
 * GglHit構造体
 * 当たり判定に必要な変数、関数ポインタを持つ
**********************************************************/
struct GglHit
{
	GglBoolean		hitUse;								// 当たり判定を使用するかどうかをフラグとして扱う
	GglBoolean		SphereUse;							// 円形、球形当たり判定を使用するかどうかをフラグとして扱う

	GglVector3f*	hitPosition;						// インスタンスのポジション
	float			hitRadius;							// 当たり判定の半径（当たり判定はすべて円形で行う）
	GglRectangle	hitRect;							// 当たり判定の矩形

	GglObject*		(*HitEventArray)(GglObject, GglObject);	// 当たり判定時に呼ばれる関数アレイ
	int				HitEventFuncCount;					// 当たり判定時に呼ばれる関数アレイのアレイ最大数

}typedef GglHit;




/****
 * GglImage構造体
 * png画像やRAWなど、イメージ情報を扱う
**********************************************************/
struct GglImage
{
	// ピクセル毎の色情報
	GglUByte*			rows;		// 画像情報

	// 画像の大きさ
	union
	{
		GglVector2i		size;
		unsigned int	array[2];
	};

	// チャンネル数(グレースケール、RGB、RGBA、etc...
	char				depth;		// 色深度
	char				colorType;
	char				channles;	// カラーチャンネル

	// OpenGLに登録されたテクスチャID
	int					id;

}typedef GglImage;




/****
 * GglInputDevice構造体
 * glutKeyboardFuncなどで取得されるキーボード情報や
 * マウスのボタン情報などを取得します
**********************************************************/
struct GglInputDevice
{
	GglByte	keyState[256];	// キーボードの入力情報を保持します
	int		mouseButton;	// マウスの入力情報を保持します
	int		mouseState;		// マウスのボタンの状態を保持します
	int		mouseX;			// それぞれの操作時のマウスのX座標を保持します
	int		mouseY;			// それぞれの操作時のマウスのY座標を保持します

}typedef GglInputDevice;




/****
 * GglMatrix3x3構造体
 * 行列を表す
**********************************************************/
union GglMatrix3x3
{
	struct
	{
		double _11, _12, _13;	//[0a][0b][0c]
		double _21, _22, _23;	//[1a][1b][1c]
		double _31, _32, _33;	//[2a][2b][2c]
		double _41, _42, _43;	//[3a][3b][3c] このような3x3行列である
	};

	double array[3][3];

}typedef GglMatrix3x3;

/****
 * GglMatrix4x4構造体
 * 行列を表す
**********************************************************/
union GglMatrix4x4
{
	struct
	{
		double _11, _12, _13, _14;	//[0a][0b][0c][0d]
		double _21, _22, _23, _24;	//[1a][1b][1c][1d]
		double _31, _32, _33, _34;	//[2a][2b][2c][2d]
		double _41, _42, _43, _44;	//[3a][3b][3c][3d] このような4x4行列である
	};

	double array[4][4];

}typedef GglMatrix4x4;




/****
 * GglMemory構造体
 * メモリ管理のベースとなる構造体である
**********************************************************/
struct GglMemory					// メモリ管理構造体
{
	struct GglMemory*	next;		// 次のメモリを参照
	struct GglMemory*	prev;		// 前のメモリを参照

	GglObject			object;		// メモリ管理にヒモ付するオブジェクト
	GglSize				memorySize;	// メンバ「object」のサイズ

}typedef GglMemory;

/****
 * GglMemoryList構造体
 * メモリ管理の中枢となる構造体
**********************************************************/
struct GglMemoryList
{
	GglMemory*	head;		// 先頭 
	GglMemory*	tail;		// 終端

	GglSize		maxRegist;	// メモリ登録数
	GglSize		memorySum;	// 登録メモリの量

}typedef GglMemoryList;



/**************************************************************************************************************************
*
*	3Dモデルを構成する構造体群
**************************************************************************************************************************/

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

/**
 * GglVertex構造体
 * バーテクス(頂点)情報を持つ
*/
struct GglVertex
{
	unsigned int	max;	// バーテクス情報最大数
	GglVector3d*	index;	// バーテクス情報本体(動的配列)
	GglColor4*		color;	// バーテクスカラー情報(動的配列 NULLで不使用)

}typedef GglVertex;

/**
 * GglFace構造体
 * フェイス(面)情報を持つ
*/
struct GglFace
{
	unsigned int	max;		// 麺最大数
	GglPolygonFace*	index;		// 麺情報本体(動的配列)
	GglNormal3d*	normals;	// 法線情報(動的配列)

}typedef GglFace;

/**
 * GglMaterial構造体
 * マテリアル情報を持つ
*/
struct GglMaterial
{
	unsigned int		max;			// マテリアル情報最大数(-1で不使用)
	GglMaterialList*	index;			// マテリアルリスト本体

}typedef GglMaterial;

/**
 * GglModel
 * 3Dモデル情報
************************************************************/
struct GglModel
{
	GglString		name;					// モデルの名前

	// Vertex関連情報
	GglVertex		vertex;
	
	// Face関連情報
	GglFace			face;

	// Material and VertexColor関連情報
	GglMaterial		material;

	// SkinAnimation関連情報
	GglBoolean		useSkinAnimationFlag;	// スキンアニメーション使用フラグ

}typedef GglModel;


/****
 * GglThread構造体
 * マルチスレッドを使用する時にスレッドを保持するための構造体
 * リスト構造となる
************************************************************/
struct GglThread
{
	struct GglThread*	prev;		// リストの前へのポインタ
	struct GglThread*	next;		// リストの次へのポインタ

	GglObject			thread;		// スレッド(関数)へのポインタ
	GglObject			argument;	// マルチスレッドの関数への引数ポインタ
	GglBoolean			loopFlag;	// ループから抜け出すフラグ Falseでループ終了

}typedef GglThread;

/****
 * GglMultiThreadList構造体
 * 作成されたスレッドを管理する構造体
************************************************************/
struct GglMultiThreadList
{
	GglThread*		head;				// リストの先頭を表すポインタ
	GglThread*		tail;				// リストの末尾を表すポインタ

	GglObject*	array;				// リストを配列化

	int			count;				// リスト登録数
	GglBoolean	useMultiThreadFlag;	// マルチスレッド使用フラグ

}typedef GglMultiThreadList;


/****
 * GglLink構造体
 * 数珠繋ぎ状のタスクシステムを構築する基底構造体であると同時に
 * 外部オブジェクトをGglObjectによって保持することができ、
 * 関数ポインタを持たせることで外部オブジェクトの実行と管理を
 * 簡単にすることができる
 * C言語で抽象化を実現した、C++でいうスーパークラスに当たる構造体
 ************************************************************/
struct GglLink
{
	struct GglLink*		next;		// 次のノードを参照
	struct GglLink*		prev;		// 前のノードを参照

	GglObject			object;		// 外部オブジェクト
	GglString			name;		// オブジェクトの名前
	GglLinkStatus		status;		// オブジェクトの状態
	GglLinkPriority	priority;	// オブジェクトの描画順番
	GglHit				hit;		// 当たり判定機能

	// 関数ポインタ、それぞれobjectの実行と描画を行う
	void				(*Update)(struct GglLink* io_pLink, GglObject io_object);
	void				(*Draw)(GglObject io_object);

}typedef GglLink;

/****
 * GglLinkList構造体
 * リンクリストを管理
************************************************************/
struct GglLinkList
{
	GglLink* head;		// リストの先頭
	GglLink* tail;		// リストの末尾

	int count;			// リスト登録数

}typedef GglLinkList;




/****
 * GglSocketNode構造体
 * ネットワークの通信単位、ソケットを保持する
************************************************************/
struct GglSocketNode
{
	struct GglSocketNode* next;				// リストの次を表すポインタ
	struct GglSocketNode* prev;				// リストの前を表すポインタ

	GglSocket			socket;				// ソケット
	SOCKADDR_IN			address;			// アドレス
	CRITICAL_SECTION	criticalSection;	// クリティカルセクション

	GglSize				maxDataSize;		// データのサイズ
	GglString			recvObject;			// 受信情報
	GglString			sendObject;			// 送信情報
	GglBoolean			recvDataUsedFlag;	// 受信データ利用フラグ

}typedef GglSocketNode;

/****
 * GglSocketList構造体
 * ソケットのリスト
************************************************************/
struct GglNetworkList
{
	GglSocketNode*	head;				// 通信リストの先端
	GglSocketNode*	tail;				// 通信リストの最後尾

	GglSocketNode*	hostServerModule;	// ホスト、あるいはサーバを作った時のソケット

	unsigned int	count;				// 通信している数
	GglBoolean		useNetworkFlag;		// ネットワーク使用フラグ

}typedef GglNetworkList;


/*
**************** 関数 ****************
*/
// 画像付加色セット
GglColor4 GglColor4_Initialize(const unsigned char in_r256, const unsigned char in_g256, const unsigned char in_b256, const unsigned char in_a256);
GglColor4 GglColor4_LoadIdentity();

// 現在のカウントを追加する
void GglFps_Initialize(const GglClock in_countMode);

// Fpsのカウントを更新する
GglBoolean GglFps_Update(void);

// ゲームが１秒経ったときの処理
void GglFps_OneSecond(void);

// 現在のFPSをコンソールに表示
void GglFps_ConsoleDraw(void);

// 円形当たり判定(3D)
GglBoolean GglHit_CircleHit(GglVector3f* in_pV1, const float in_r1, GglVector3f* in_pV2, const float in_r2);

// 矩形当たり判定(2D)
GglBoolean GglHit_RectangleHit(GglVector3f* _v1, GglRectangle _r1, GglVector3f* _v2, GglRectangle _r2);

// 円形当たり判定拡張 入射角取得
void GglHit_CircleGetIncidenceReflex(GglVector3f* in_pPos1, GglVector3f* in_pPos2, GglVector3f* in_pVec1, GglVector3f* out_v1, GglVector3f* out_v2);

/*
	Image.c
*/
// PNGイメージ読み込み
GglImage* GglImage_LoadPng(GglImage* out_pImage, GglString in_fileName);
// PNG読み込みコールバック
void GglImage_ReadPng(png_structp in_pPng, png_bytep out_data, png_size_t in_length);

//// イメージセット
//GglImage GglImage_AssembleElements(unsigned int* in_pImage, pngRawInfo* in_pInfo, GglImage* out_pImage);
//
////イメージ情報を登録する関数
//GglBoolean GglImage_RegistImage(GglImage* out_pImage, GglString in_string);


void GglInputDevice_GetKeyboardState(void);
void GglInputDevice_Mouse(int in_button, int in_state, int in_x, int in_y);

// Escapeキーでゲームを終了させる関数
void GglInputDevice_ShutDownKey(void);

// システム起動時に行うg_inputDeviceの初期化関数群
void GglInputDevice_MouseInit(void);
void GglInputDevice_AllInitialize(void);

/* 四則演算 */
void GglMatrix4x4_Add(GglMatrix4x4* out_pM, const GglMatrix4x4* in_pM1, const GglMatrix4x4* in_pM2);	// 足し算
void GglMatrix4x4_Sub(GglMatrix4x4* out_pM, const GglMatrix4x4* in_pM1, const GglMatrix4x4* in_pM2);	// 引き算
void GglMatrix4x4_Mul(GglMatrix4x4* out_pM, const GglMatrix4x4* in_pM1, const GglMatrix4x4* in_pM2);	// 掛け算

/* 四則演算 先頭アドレス用 */
void GglMatrix4x4_AddF(double* out_pMFAdr, const double* in_pMFAdr1, const double* in_pMFAdr2);
void GglMatrix4x4_SubF(double* out_pMFAdr, const double* in_pMFAdr1, const double* in_pMFAdr2);
void GglMatrix4x4_MulF(double* out_pMFAdr, const double* in_pMFAdr1, const double* in_pMFAdr2);


/* 特殊演算 */
void GglMatrix4x4_DotVector(GglVector3f* out_pVec, const GglMatrix4x4* in_pMat, const GglVector3f* in_pVec);	// スカラー倍
void GglMatrix4x4_DotScalar(GglMatrix4x4* out_pMat, const GglMatrix4x4* in_pMat, const double in_scalar);	// ベクトル倍

// ワールド行列初期化(単位行列を上書き)
void GglMatrix4x4_SetIdentity(GglMatrix4x4* out_pMat);

/* 回転 */
GglMatrix4x4 GglMatrix4x4_GetRotatePitch(const double in_rad);	// X軸
GglMatrix4x4 GglMatrix4x4_GetRotateYaw(const double in_rad);	// Y軸
GglMatrix4x4 GglMatrix4x4_GetRotateRoll(const double in_rad);	// Z軸

/* 拡縮 */
GglMatrix4x4 GglMatrix4x4_GetScale(const GglVector3d* in_pV);

/* 平行移動 */
GglMatrix4x4 GglMatrix4x4_GetTranslation(const GglVector3d* in_pV);

GglBoolean	GglMemory_Initialize(void);
GglBoolean	GglMemory_Shutdown(void);

GglObject	GglMemory_New(GglSize _size);
GglBoolean	GglMemory_Delete(GglObject _object);
GglBoolean	GglMemory_AllDelete(void);
GglBoolean	GglMemory_DeleteMemoryAndReconnect(GglMemory* _this);


void		GglMemory_ReconnectList(GglMemory* _first, GglMemory* _end);
GglMemory*	GglMemory_SearchNull2First(void);
GglMemory*	GglMemory_SearchNull2End(void);

GglModel* GglModel_Initialize(GglModel* out_model);		// モデル初期化

// モデルロード関数群
GglModel*	GglModel_LoadModel(const GglString in_fileName, GglModel* out_model);	// モデルロード
GglBoolean	GglModel_LoadModel2X(const GglString in_fileName, GglModel* _pModel);							// Xファイルロード
void		GglModel_LoadModel2X_ReadMesh(FILE* _pFile, GglModel* _pModel, GglString _buffer);				// Xファイルメッシュデータロード

void		GglModel_LoadModel2X_ReadMaterialList(FILE* _pFile, GglModel* _pModel);		// Xファイルマテリアルリストデータロード
//void		GglModel_LoadModel2X_ReadMaterial(FILE*_pFile, GglModel* _pModel);			// Xファイルマテリアルデータロード
void		GglModel_LoadModel2X_ReadMeshVertexColors(FILE* _pFile, GglModel* _pModel);	// Xファイルバーテックスカラーデータロード

void		GglModel_LoadModel2X_ReadMeshNormals(FILE* _pFile, GglModel* _pModel, long* _pos);			// Xファイルメッシュノーマルデータロード
void		GglModel_LoadModel2X_ReadMeshTextureCoords(FILE* _pFile, GglModel* _pModel, long* _pos);	// Xファイルテクスチャーコードデータロード

GglBoolean	GglModel_LoadModel2Mqo(const GglString in_fileName, GglModel** _pModel);						// MQOファイルロード

// その他
void		GglModel_DeleteModel(GglModel* _this);		// モデル削除

GglBoolean	GglMultiThread_Initialize(void);
void		GglMultiThread_Shutdown(void);

GglBoolean	GglMultiThread_AddThread(GglThread* _pThreadInst);
GglBoolean	GglMultiThread_AddNewThread(void(*_funcName)(GglObject), unsigned _stackSize, GglObject _argStructInstance);

GglBoolean	GglMultiThread_RemoveThread(GglThread* _pThreadInst);
GglBoolean	GglMultiThread_RemoveAllThread(void);
GglBoolean	GglMultiThread_LoopFlagSwitch(GglThread* _this);

GglBoolean	GglString_ExtractErase(const int ic_count, GglString o_str, const int tgtlen, const GglString ic_target, ...);
GglString	GglString_EraseFirst(int _eraseLength, GglString _target);
GglString	GglString_MakeString(GglString str, GglSize length);

// 画像サイズ、範囲セット
GglRectangle GglRectangle_Initialize(const int in_top, const int in_bottom, const int in_left, const int in_right);
GglRectangle GglRectangle_LoadIdentity();

//// GglRectangle情報をVertex2dなどの閾値(0.0~1.0)へ変換する
//void GglRectangle_ExchangeIdentity(GglRectangle* out_pRect, const GglRectangle* in_pRect, const pngInfo* in_pInfo);



//// ベクトルセット
//GglVector2i GglVector2i_Set(const int in_x, const int in_y);
//GglVector2i GglVector2i_SetInitialize(void);
//
//// 足し算
//GglVector2i GglVector2i_Add(GglVector2i in_v1, GglVector2i in_v2);
//void GglVector2i_AddEquals(GglVector2i* io_pV1, GglVector2i in_v2);
//
//// 引き算
//GglVector2i GglVector2i_Sub(GglVector2i in_v1, GglVector2i in_v2);
//void GglVector2i_SubEquals(GglVector2i* io_pV1, GglVector2i in_v2);
//
//// 内積
//int GglVector2i_Dot(GglVector2i in_v1, GglVector2i in_v2);
//
//int GglVector2i_Dotp(GglVector2i* in_v1, GglVector2i* in_v2);
//
//// ベクトルの大きさを取得します
//int GglVector2i_GetLength(GglVector2i* in_pV);
//
//// ベクトルをスカラー倍します
//void GglVector2i_SetMultipleScalar(GglVector2i* in_pV, const int in_scalar, GglVector2i* out_pV);
//
//void GglVector2i_Vertex2dv(GglVector2i* in_pV);
//
////平行移動
//void GglVector2i_Translatef(GglVector2i* in_pVec);
//
//// ベクトル正規化
//void GglVector2i_Normalize3D(GglVector2i in_vec, GglVector2i* out_pv);
//
//// 加速度計算
//int GglVector2i_Accel(int in_vi,int in_accel, int in_time);
//
//// 重力加速度計算
//int GglVector2i_GravityAccel(int in_viy, int in_time);
//
//
//
//// ベクトルセット
//GglVector2f GglVector2fSet(const float in_x, const float in_y, const float in_z);
//GglVector2f GglVector2fSetInitialize(void);
//
//// 足し算
//GglVector2f GglVector2fAdd(GglVector2f in_v1, GglVector2f in_v2);
//void GglVector2fAddEquals(GglVector2f* io_pV1, GglVector2f in_v2);
//
//// 引き算
//GglVector2f GglVector2fSub(GglVector2f in_v1, GglVector2f in_v2);
//void GglVector2fSubEquals(GglVector2f* io_pV1, GglVector2f in_v2);
//
//// 内積
//float GglVector2fDot(GglVector2f in_v1, GglVector2f in_v2);
//float GglVector2fDotp(GglVector2f* in_v1, GglVector2f* in_v2);
//
//// ベクトルの大きさを取得します
//float GglVector2fGetLength(GglVector2f* in_pV);
//
//// ベクトルをスカラー倍します
//void GglVector2fSetMultipleScalar(GglVector2f* in_pV, const float in_scalar, GglVector2f* out_pV);
//
//void GglVector2fVertex2dv(GglVector2f* in_pV);
//
////平行移動
//void GglVector2fTranslatef(GglVector2f* in_pVec);
//
//// ベクトル正規化
//void GglVector2fNormalize3D(GglVector2f in_vec, GglVector2f* out_pv);
//
//// 加速度計算
//float GglVector2fAccel(float in_vi,float in_accel, int in_time);
//
//// 重力加速度計算
//float GglVector2fGravityAccel(float in_viy, float in_time);
//
//
//
//// ベクトルゼロ初期化
//GglVector2d GglVector2d_SetInitialize(void);
//
//// ベクトルセット
//GglVector2d GglVector2d_Set(const double in_x, const double in_y);
//
//// 足し算
//GglVector2d GglVector2d_Add(GglVector2d in_v1, GglVector2d in_v2);
//void GglVector2d_AddEquals(GglVector2d* io_pV1, GglVector2d in_v2);
//
//// 引き算
//GglVector2d GglVector2d_Sub(GglVector2d in_v1, GglVector2d in_v2);
//void GglVector2d_SubEquals(GglVector2d* io_pV1, GglVector2d in_v2);
//
//// 内積
//double GglVector2d_Dot(GglVector2d in_v1, GglVector2d in_v2);
//double GglVector2d_Dotp(GglVector2d* in_v1, GglVector2d* in_v2);
//
//// ベクトルの大きさを取得
//double GglVector2d_GetLength(GglVector2d* in_pV);
//
//// ベクトルをスカラー倍
//void GglVector2d_SetMultipleScalar(GglVector2d* in_pV, double in_scalar, GglVector2d* out_pV);
//
///* GL用関数 */
//// バーテックス設定
//void GglVector2d_Vertex2dv(GglVector2d* in_pV);
//
//// 平行移動
//void GglVector2d_Translated(GglVector2d* in_pVec);
//
//
///* ゲーム用関数 */
//// ベクトル正規化
//void GglVector2d_Normalize3D(GglVector2d in_vec, GglVector2d* out_pv);
//
//// 加速度計算
//double GglVector2d_Accel(double in_vi,double in_accel, int in_time);
//
//// 重力加速度計算
//double GglVector2d_GravityAccel(double in_viy, double in_time);
//
//
//
//
//
//// ベクトルゼロ初期化
//GglVector3d GglVector3d_SetInitialize(void);
//
//// ベクトルセット
//GglVector3d GglVector3d_Set(const double in_x, const double in_y, const double in_z);
//
//// 足し算
//GglVector3d GglVector3d_Add(GglVector3d in_v1, GglVector3d in_v2);
//void GglVector3d_AddEquals(GglVector3d* io_pV1, GglVector3d in_v2);
//
//// 引き算
//GglVector3d GglVector3d_Sub(GglVector3d in_v1, GglVector3d in_v2);
//void GglVector3d_SubEquals(GglVector3d* io_pV1, GglVector3d in_v2);
//
//// 内積
//double GglVector3d_Dot(GglVector3d in_v1, GglVector3d in_v2);
//double GglVector3d_Dotp(GglVector3d* in_v1, GglVector3d* in_v2);
//
//// 外積
//GglVector3d GglVector3d_Cross(GglVector3d in_v1, GglVector3d in_v2);
//
//// ベクトルの大きさを取得
//double GglVector3d_GetLength(GglVector3d* in_pV);
//
//// ベクトルをスカラー倍
//void GglVector3d_SetMultipleScalar(GglVector3d* in_pV, double in_scalar, GglVector3d* out_pV);
//
///* GL用関数 */
//// バーテックス設定
//void GglVector3d_Vertex3dv(GglVector3d* in_pV);
//void GglVector3d_Vertex2dv(GglVector3d* in_pV);
//
//// 法線設定
//void GglVector3d_Normal3dv(GglNormal3d* in_pN);
//
//// 平行移動
//void GglVector3d_Translated(GglVector3d* in_pVec);
//
//
///* ゲーム用関数 */
//// ベクトル正規化
//void GglVector3d_Normalize3D(GglVector3d in_vec, GglVector3d* out_pv);
//
//// 加速度計算
//double GglVector3d_Accel(double in_vi,double in_accel, int in_time);
//
//// 重力加速度計算
//double GglVector3d_GravityAccel(double in_viy, double in_time);
//
//
//
//
//
//
//
//// ベクトルゼロ初期化
//GglVector3f GglVector3f_SetInitialize(void);
//
//// ベクトルセット
//GglVector3f GglVector3f_Set(const double in_x, const double in_y, const double in_z);
//
//// 足し算
//GglVector3f GglVector3f_Add(GglVector3f in_v1, GglVector3f in_v2);
//void GglVector3f_AddEquals(GglVector3f* io_pV1, GglVector3f in_v2);
//
//// 引き算
//GglVector3f GglVector3f_Sub(GglVector3f in_v1, GglVector3f in_v2);
//void GglVector3f_SubEquals(GglVector3f* io_pV1, GglVector3f in_v2);
//
//// 内積
//double GglVector3f_Dot(GglVector3f in_v1, GglVector3f in_v2);
//double GglVector3f_Dotp(GglVector3f* in_v1, GglVector3f* in_v2);
//
//// 外積
//GglVector3f GglVector3f_Cross(GglVector3f in_v1, GglVector3f in_v2);
//
//// ベクトルの大きさを取得
//float GglVector3f_GetLength(GglVector3f* in_pV);
//
//// ベクトルをスカラー倍
//void GglVector3f_SetMultipleScalar(GglVector3f* in_pV, double in_scalar, GglVector3f* out_pV);
//
///* GL用関数 */
//// バーテックス設定
//void GglVector3f_Vertex3dv(GglVector3f* in_pV);
//void GglVector3f_Vertex2dv(GglVector3f* in_pV);
//
//// 法線設定
//void GglVector3f_Normal3dv(GglNormal3f* in_pN);
//
//// 平行移動
//void GglVector3f_Translatef(GglVector3f* in_pVec);
//
//
///* ゲーム用関数 */
//// ベクトル正規化
//void GglVector3f_Normalize3D(GglVector3f in_vec, GglVector3f* out_pv);
//
//// 加速度計算
//double GglVector3f_Accel(double in_vi,double in_accel, int in_time);
//
//// 重力加速度計算
//double GglVector3f_GravityAccel(double in_viy, double in_time);
//
//
//
//// ベクトルセット
//GglVector3i GglVector3i_SetInitialize(void);
//
//// ベクトルセット
//GglVector3i GglVector3i_Set(const int in_x, const int in_y, const int in_z);
//
//// 足し算
//GglVector3i GglVector3i_Add(GglVector3i in_v1, GglVector3i in_v2);
//void GglVector3i_AddEquals(GglVector3i* io_pV1, GglVector3i in_v2);
//
//// 引き算
//GglVector3i GglVector3i_Sub(GglVector3i in_v1, GglVector3i in_v2);
//void GglVector3i_SubEquals(GglVector3i* io_pV1, GglVector3i in_v2);
//
//// 内積
//double GglVector3i_Dot(GglVector3i in_v1, GglVector3i in_v2);
//double GglVector3i_Dotp(GglVector3i* in_v1, GglVector3i* in_v2);
//
//// 外積
//GglVector3i GglVector3i_Cross(GglVector3i in_v1, GglVector3i in_v2);
//
//// ベクトルの大きさを取得します
//float GglVector3i_GetLength(GglVector3i* in_pV);
//
//// ベクトルをスカラー倍します
//void GglVector3i_SetMultipleScalar(GglVector3i* in_pV, int in_scalar, GglVector3i* out_pV);
//
//// バーテックス設定
//void GglVector3i_Vertex3dv(GglVector3i* in_pV);
//void GglVector3i_Vertex2dv(GglVector3i* in_pV);
//
//// 法線設定
//void GglVector3i_Normal3dv(GglNormal3f* in_pN);
//
//// 平行移動
//void GglVector3i_Translatef(GglVector3i* in_pVec);
//
//// ベクトル正規化
//void GglVector3i_Normalize3D(GglVector3i in_vec, GglVector3i* out_pv);
//
//// 加速度計算
//double GglVector3i_Accel(double in_vi,double in_accel, int in_time);
//
//// 重力加速度計算
//double GglVector3i_GravityAccel(double in_viy, double in_time);
//
//
//
//
//
//
//// ベクトルゼロ初期化
//GglVector4d GglVector4d_SetInitialize(void);
//
//// ベクトルセット
//GglVector4d GglVector4d_Set(const double in_x, const double in_y, const double in_z, const double in_q);
//
//// 足し算
//GglVector4d GglVector4d_Add(GglVector4d in_v1, GglVector4d in_v2);
//void GglVector4d_AddEquals(GglVector4d* io_pV1, GglVector4d in_v2);
//
//// 引き算
//GglVector4d GglVector4d_Sub(GglVector4d in_v1, GglVector4d in_v2);
//void GglVector4d_SubEquals(GglVector4d* io_pV1, GglVector4d in_v2);
//
//// 内積
//double GglVector4d_Dot(GglVector4d in_v1, GglVector4d in_v2);
//double GglVector4d_Dotp(GglVector4d* in_v1, GglVector4d* in_v2);
//
//// ベクトルの大きさを取得
//double GglVector4d_GetLength(GglVector4d* in_pV);
//
//// ベクトルをスカラー倍
//void GglVector4d_SetMultipleScalar(GglVector4d* in_pV, double in_scalar, GglVector4d* out_pV);
//
//// ベクトル正規化
//void GglVector4d_Normalize4d(GglVector4d in_vec, GglVector4d* out_pv);
//
//
//
//
//
//
//
//
//// ベクトルゼロ初期化
//GglVector4f GglVector4f_SetInitialize(void);
//
//// ベクトルセット
//GglVector4f GglVector4f_Set(const float in_x, const float in_y, const float in_z, const float in_q);
//
//// 足し算
//GglVector4f GglVector4f_Add(GglVector4f in_v1, GglVector4f in_v2);
//void GglVector4f_AddEquals(GglVector4f* io_pV1, GglVector4f in_v2);
//
//// 引き算
//GglVector4f GglVector4f_Sub(GglVector4f in_v1, GglVector4f in_v2);
//void GglVector4f_SubEquals(GglVector4f* io_pV1, GglVector4f in_v2);
//
//// 内積
//float GglVector4f_Dot(GglVector4f in_v1, GglVector4f in_v2);
//float GglVector4f_Dotp(GglVector4f* in_v1, GglVector4f* in_v2);
//
//
//// ベクトルの大きさを取得
//float GglVector4f_GetLength(GglVector4f* in_pV);
//
//// ベクトルをスカラー倍
//void GglVector4f_SetMultipleScalar(GglVector4f* in_pV, float in_scalar, GglVector4f* out_pV);
//
///* ゲーム用関数 */
//// ベクトル正規化
//void GglVector4f_Normalize3D(GglVector4f in_vec, GglVector4f* out_pv);
//
//
//
//
//
//
//// ベクトルセット
//GglVector4i GglVector4i_SetInitialize(void);
//
//// ベクトルセット
//GglVector4i GglVector4i_Set(const int in_x, const int in_y, const int in_z, const int in_q);
//
//// 足し算
//GglVector4i GglVector4i_Add(GglVector4i in_v1, GglVector4i in_v2);
//void GglVector4i_AddEquals(GglVector4i* io_pV1, GglVector4i in_v2);
//
//// 引き算
//GglVector4i GglVector4i_Sub(GglVector4i in_v1, GglVector4i in_v2);
//void GglVector4i_SubEquals(GglVector4i* io_pV1, GglVector4i in_v2);
//
//// 内積
//double GglVector4i_Dot(GglVector4i in_v1, GglVector4i in_v2);
//double GglVector4i_Dotp(GglVector4i* in_v1, GglVector4i* in_v2);
//
//// ベクトルの大きさを取得します
//float GglVector4i_GetLength(GglVector4i* in_pV);
//
//// ベクトルをスカラー倍します
//void GglVector4i_SetMultipleScalar(GglVector4i* in_pV, int in_scalar, GglVector4i* out_pV);








//// 2D描画
void GglGraphic2d_DrawSprite(GglImage* in_pImage, GglVector2i* in_pSize, GglRectangle* in_pRect, GglVector3f* in_pVec, GglColor4* in_pColor);
//
//// 2D線描画
//void GglGraphic2d_DrawLine2d(GglVector3f* in_pOrigin, GglVector3f* in_pEndPoint, GglColor4* in_pColor);

// 色設定
void GglGraphic2d_Color3dv(const GglColor4* in_pColor);	//アルファ無し
void GglGraphic2d_Color4dv(const GglColor4* in_pColor);	//アルファあり

// マテリアル設定
void GglGraphic2d_Materialfv(const GLenum in_targetFace, const GLenum in_lightingMaterial, const GglColor4* in_pColor);

// 3D描画
void GglGraphic3d_Render(const GglModel* in_pModel, const GglVector3d* in_pTranslate, const GglVector3d* in_pRotate, const GglVector3d* in_pScale);

// 描画視野をPerspectiveにする
void GglGraphic_Perspective(void);

// 描画視野をOrtho2Dにする
void GglGraphic_Ortho2d(void);

void GglGraphic_DrawSpriteBegin(void);
void GglGraphic_DrawSpriteEnd(void);


GglBoolean GglNetworkList_Initialize(void);
GglBoolean GglNetworkList_Shutdown(void);

GglBoolean GglNetworkList_AddElement(GglSocketNode* _this);
GglBoolean GglNetworkList_RemoveElement(GglSocketNode* _this);
GglBoolean GglNetworkList_RemoveElementAt(unsigned int _elements);
GglBoolean GglNetworkList_RemoveAllElements(void);

GglBoolean	GglNetwork_Initialize(void);		// 初期化
GglBoolean	GglNetwork_Shutdown(void);		// 終了

void		GglNetwork_GetIpAddress(GglString out_ipAddr);	// 自己IP取得
GglBoolean	GglNetwork_MakeSocket(GglSocketNode* _pModule, GglString _addressString, int _usePort);

//void		GglNetwork_HostServerWaitGuestClient(GglObject _object);
GglBoolean	GglNetwork_HostServerWaitGuestClientOnce(GglObject _object);

void		GglNetwork_ReceiveData(GglObject _object);
void		GglNetwork_SendData(GglObject _object);

/* Debug */
void		GglNetwork_PrintError(void);
void		GglNetwork_Winsock2PrintErrorSelect(int _exception);

void		GglSystem_Initialize(const GglString ic_windowName, void (*GameInit)(void));
void		GglSystem_Shutdown(void);
void		GglSystem_MainLoopUpdate(void);
void		GglSystem_MainLoopDraw(void);
void		GglSystem_WindowResize(const int _w, const int _h);

void		GglSystem_InitializeGlut(void);
void		GglSystem_InitializeSystem(void);
void		GglSystem_UnLoadContent(void);


// LinkTaskSystem 関数
void		GglLinkList_Initialize(void);						//LinkTask起動
void		GglLinkList_Shutdown(void);							//LinkTask終了
GglBoolean	GglLinkList_AddElement(GglLink* _new);				//LinkTaskに新しいノードを追加
GglBoolean	GglLinkList_RemoveElement(GglLink* _del);			//LinkTaskから指定したノードを削除
GglBoolean	GglLinkList_RemoveElementAt(const int ic_element);	//LinkTaskから指定したノードを削除
void		GglLinkList_RemoveAllElements(void);					//LinkTaskに登録されているノード全削除
void		GglLinkList_Update(void);							//LinkTask内に登録されているノードの実行関数実行
void		GglLinkList_Draw(void);								//LinkTask内に登録されているノードの描画関数実行




/*
************************************  Global Variable  *****************************************
*/
extern GglInputDevice			g_inputDevice;		// 入力デバイス管理
extern GglFps					g_fps;				// Fps構造体のグローバル変数
//extern GglImage*				g_imageArray;		// イメージデータ格納配列

extern GglLinkList			g_linkList;		// タスクシステム

extern GglMemoryList			g_memoryList;	// メモリ管理リスト
extern GglNetworkList		g_networkList;	// ネットワーク用ソケット構造体
extern GglMultiThreadList	g_multiThread;		// マルチスレッドハンドルリンクリスト

//extern GglVector2d			g:

#endif