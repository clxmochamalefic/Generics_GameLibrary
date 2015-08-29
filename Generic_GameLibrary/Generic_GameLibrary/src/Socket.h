#ifndef GglSocket_h__
#define GglSocket_h__

#include <WinSock2.h>
#include "Definition.h"

// Network
#define GglNetwork_CloseSocket(x)						closesocket(x)

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

#endif