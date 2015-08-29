#ifndef LinkPriority_h__
#define LinkPriority_h__

/**
 * GglLinkPriority列挙体
 * オブジェクトの描画順番を表現する
 */
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

#endif