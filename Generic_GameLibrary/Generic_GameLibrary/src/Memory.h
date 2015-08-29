#ifndef GglMemory_h__
#define GglMemory_h__

#include "Definition.h"

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

#endif