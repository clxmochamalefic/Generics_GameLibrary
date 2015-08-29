#ifndef Link_h__
#define Link_h__

#include "Definition.h"
#include "LinkPriority.h"
#include "LinkStatus.h"
#include "Hit.h"

/**
 * GglLink構造体
 * 数珠繋ぎ状のタスクシステムを構築する基底構造体であると同時に
 * 外部オブジェクトをGglObjectによって保持することができ、
 * 関数ポインタを持たせることで外部オブジェクトの実行と管理を
 * 簡単にすることができる
 * C言語で抽象化を実現した、オブジェクト指向言語でいうスーパークラスに当たる構造体
 */
struct GglLink
{
	struct GglLink*		next;		// 次のノードを参照
	struct GglLink*		prev;		// 前のノードを参照

	GglObject			object;		// 外部オブジェクト
	GglString			name;		// オブジェクトの名前
	GglLinkStatus		status;		// オブジェクトの状態
	GglLinkPriority		priority;	// オブジェクトの描画順番
	GglHit				hit;		// 当たり判定機能

	// Update関数 利用者はこれに実行する処理を記述した関数を渡す。 オーバーライドのイメージ。
	void(*Update)(struct GglLink* io_pLink, GglObject io_object);
	
	// Draw関数 利用者はこれに描画する処理を記述した関数を渡す。 同じくオーバーライドのイメージ。
	void(*Draw)(GglObject io_object);

}typedef GglLink;

#endif