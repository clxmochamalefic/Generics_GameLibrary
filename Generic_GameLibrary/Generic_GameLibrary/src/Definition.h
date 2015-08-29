#ifndef GglDefinition_h__
#define GglDefinition_h__

#include <time.h>

// foreach文
#define GGL_FOREACH(val, init, terms, cont)				if((init)!=NULL)	for((val)=(init);(val)!=(terms)&&(val)!=NULL;(val)=(val)->cont)

/**
 * 別名定義
 */
typedef char*			GglString;		// 文字列型
typedef char			GglByte;		// バイト型(1byte)
typedef unsigned char	GglUByte;		// 符号なしバイト型(1byte)
typedef void*			GglObject;		// オブジェクト型(注意、汎用ポインタ(void*)です)
typedef unsigned int	GglSize;		// サイズ型 32bitマシンでのsize_tと等価
typedef clock_t			GglClock;		// クロック型 Windowsのclock_tと等価
typedef unsigned int*	GglSocket;

/**
 * 定数 
 */
#define GGL_SYSTEMVER					("1.0.0.PrivateBeta")	// システムバージョン文字列

#define GGL_PI							(3.1416)				// 円周率
#define GGL_GRAVITY_FACTOR				(-0.098)					// 重力
#define GGL_MAX_STRING_LENGTH			(256)
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

/**
 * GglBoolean列挙体
 * ブーリアンを持つ
 */
enum GglBoolean			// ブーリアン
{
	GglFalse,			// 偽(=0)
	GglTrue				// 真(=1)

}typedef GglBoolean;



#endif