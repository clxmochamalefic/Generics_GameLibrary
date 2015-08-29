#ifndef GglLinkStatus_h__
#define GglLinkStatus_h__

/**
 * GglLinkStatus列挙体
 * オブジェクトの状態を表現する
 */
enum GglLinkStatus
{
	Delete,	//オブジェクト削除
	Sleep,	//オブジェクトは実行から外されるが削除されない
	Live	//オブジェクト実行

}typedef GglLinkStatus;


#endif