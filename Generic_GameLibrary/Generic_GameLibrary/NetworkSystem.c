#include <winsock2.h>
#include <string.h>
#include "Generic_GameLibrary.h"

#pragma warning(disable : 4996)

/***********************************************************
 * GglNetwork_Startup関数 
 * Winsock2を初期化します
 *
 * 戻り値：GglBoolean(ブール値)
 * 引数　：なし
*/
GglBoolean GglNetwork_Initialize(void)
{
	WSADATA wsaData;
	int exception = 0;

	exception = WSAStartup(MAKEWORD(2,0), &wsaData);
	
	if(exception != 0)
	{
		GglDebug_PrintExceptionLine();
		GglNetwork_Winsock2PrintErrorSelect(exception);
		return GglFalse;
	}

	return GglTrue;
}

/***********************************************************
 * GglNetwork_Shutdown関数 
 * Winsock2を終了します
 *
 * 戻り値：GglBoolean(ブール値)
 * 引数　：なし
*/
GglBoolean GglNetwork_Shutdown(void)
{
	int exception;

	exception = WSACleanup();

	if(exception != 0)
	{
		GglDebug_PrintExceptionLine();
		GglNetwork_Winsock2PrintErrorSelect(exception);
		return GglFalse;
	}

	return GglTrue;
}

/***********************************************************
 * GglNetwork_GetIpAddress関数 
 * 自身のIPアドレスを取得します
 *
 * 戻り値：GglString(typedef char*, 文字列)
 * 引数　：なし
*/
void GglNetwork_GetIpAddress(GglString out_ipAddr)
{
	char		ipAddress[256];
	PHOSTENT	pHostent;
	IN_ADDR		address;
	
	if(gethostname(ipAddress, sizeof(ipAddress)) != 0)
	{
		GglDebug_PrintExceptionLine();
		GglNetwork_PrintError();
		*out_ipAddr = 0;
		return ;
	}

	pHostent = gethostbyname(ipAddress);

	if(pHostent == NULL)
	{
		GglDebug_PrintExceptionLine();
		*out_ipAddr = 0;
		return ;
	}

	memcpy(&address, pHostent->h_addr_list[0], 4);
	strncpy(out_ipAddr, inet_ntoa(address), 256);

	*out_ipAddr = 0;
	return ;
}

/************************************************************************************
 * GglNetwork_MakeSocket関数 
 * Winsock2にてSocketを作成します
 * サーバとクライアント、
 * 或いはホストとゲストのMakeにも対応していますが、
 * サーバとホストをMakeする場合は第3引数に
 * "127.0.0.1"、或いは「GglNetwork_USE_LOCALHOST」を渡してください
 *
 * 戻り値：GglBoolean				成功時にGglTrueを、失敗時にGglFalseを返します
 * 引数　：
 * 1. GglSocket*	_pModule		接続用のソケット、アドレス等を保持する構造体
 * 3. GglString			_addressString	接続先のアドレスです
 * 4. int				_usePort		使用するポート番号です
*/
GglBoolean GglNetwork_MakeSocket(GglSocketNode* _pModule,
								 GglString _addressString,
								 int _usePort)
{
	// Make Socket
	_pModule->socket = (GglSocket)socket(AF_INET, SOCK_STREAM, 0);

	// ソケットのMakeに失敗した場合はエラー行とエラー理由をprintfしてMake終了
	if(_pModule->socket == (GglSocket)INVALID_SOCKET)
	{
		GglDebug_PrintExceptionLine();
		GglNetwork_PrintError();
		return GglFalse;
	}

	// Definition a host Address
	_pModule->address.sin_family	= AF_INET;
	_pModule->address.sin_port		= htons(_usePort);

	if( strcmp(_addressString, "127.0.0.1")				== 0 ||
		strcmp(_addressString, "0.0.0.0")				== 0 ||
		strcmp(_addressString, GglNetwork_USE_LOCALHOST)== 0 )
	{
		_pModule->address.sin_addr.S_un.S_addr = INADDR_ANY;

		// ホストのIPとソケットを関連付け
		if( bind( (SOCKET)_pModule->socket, (SOCKADDR*)&_pModule->address, sizeof(_pModule->address) ) != 0 )
		{
			GglDebug_PrintExceptionLine();
			GglNetwork_PrintError();
			return GglFalse;
		}

		printf("bind Entered...\n");
	}
	else
	{
		_pModule->address.sin_addr.S_un.S_addr = inet_addr(_addressString);
		
		if( connect( (SOCKET)_pModule->socket, (SOCKADDR*)&_pModule->address, sizeof(_pModule->address) ) == SOCKET_ERROR )
		{
			GglDebug_PrintExceptionLine();
			GglNetwork_PrintError();
			return GglFalse;
		}
	}

	return GglTrue;
}

// マルチスレッドでの運用を前提とする
GglBoolean GglNetwork_HostServerWaitGuestClientOnce(GglObject _object)
{
	GglThread* pThread		= _object;
	GglSocketNode* nModule	= (GglSocketNode*)pThread->argument;
	GglSocketNode* toClient = (GglSocketNode*)GglMemory_New(sizeof(GglSocket));
	int addressLength		= sizeof(SOCKADDR_IN);

	printf("Begin Connect Wait...\n");

	//EnterCriticalSection(&nModule->criticalSection);

	//WaitForSingleObject(pThread->thread, INFINITE);

	GglDebug_PrintInformationLine("Enter Listen...\n");
	if( listen( (SOCKET)nModule->socket, SOMAXCONN ) != 0 )
	{
		GglDebug_PrintExceptionLine();
		GglNetwork_PrintError();
		//LeaveCriticalSection(&nModule->criticalSection);
		return GglFalse;
	}

	GglDebug_PrintInformationLine("Enter Accept...\n");
	toClient->socket = (GglSocket)accept( (SOCKET)nModule->socket , (SOCKADDR*)&toClient->address , &addressLength );

	if(toClient->socket == (GglSocket)INVALID_SOCKET)
	{
		GglDebug_PrintExceptionLine();
		GglNetwork_PrintError();
		//LeaveCriticalSection(&nModule->criticalSection);
		return GglFalse;
	}

	GglNetworkList_AddElement(toClient);

	//LeaveCriticalSection(&nModule->criticalSection);

	GglDebug_PrintInformationLine("Success Accept!!\n");

	GglMultiThread_AddNewThread(GglNetwork_ReceiveData, 1, toClient);
	//GglMultiThread_AddNewThread(GglNetwork_SendData, 1, toClient);

	return GglTrue;
}

void GglNetwork_ReceiveData(GglObject _object)
{
	int result;
	GglThread*	_this			= _object;
	GglSocketNode* nModule	= _this->argument;
	char a[256] = "\0";

	while(1)
	{
		memset(a, 0, 1);
		if(nModule->maxDataSize <= 0)
		{
			GglDebug_PrintExceptionLine();
			break;
		}

		//EnterCriticalSection(&nModule->criticalSection);

		result = recv((SOCKET)nModule->socket, a, 256, 0);


		if(nModule->recvDataUsedFlag == GglTrue)
		{
			strncpy(nModule->recvObject, a, strlen(a));
			nModule->recvDataUsedFlag = GglFalse;
		}

		//nModule->recvObject = a;
		//strncpy(&g_recvData, &a, strlen(&a));
		//printf("result = %d\n", a);

		//LeaveCriticalSection(&nModule->criticalSection);

		if(result == SOCKET_ERROR)
		{
			GglDebug_PrintExceptionLine();
			GglNetwork_PrintError();
			break;
		}
		else if(result == 0)
		{
			GglDebug_PrintInformationLine("受信スレッド終了也");
			break;
		}
	}
	return ;
}

void GglNetwork_SendData(GglObject _object)
{
	int result;
	GglThread*	_this			= _object;
	GglSocketNode* nModule	= _this->argument;
	char a;

	while(1)
	{
		if(nModule->maxDataSize <= 0)
		{
			GglDebug_PrintExceptionLine();
			break;
		}

		//EnterCriticalSection(&nModule->criticalSection);

		printf("Begin Send\n");

		printf("send data = %c", (char)nModule->sendObject);
		printf("send size = %d", nModule->maxDataSize);

		a = (char)nModule->sendObject;

		result = send((SOCKET)nModule->socket, &a, 1, 0);

		printf("sended\n");

		//LeaveCriticalSection(&nModule->criticalSection);

		if(result == SOCKET_ERROR)
		{
			GglDebug_PrintExceptionLine();
			GglNetwork_PrintError();
			break;
		}
	}
	return ;
}

/**************************************************************
 * GglNetwork_PrintError関数 
 * Winsock2でのエラーをGglNetwork_Winsock2PrintErrorSelect経由で
 * printfで描画します
 *
 * 戻り値：なし
 * 引数　：なし
*/
void GglNetwork_PrintError(void)
{
	int error = WSAGetLastError();
	GglNetwork_Winsock2PrintErrorSelect(error);

	return ;
}

/***********************************************************
 * GglNetwork_Winsock2PrintErrorSelect関数
 * 引数で指定されたWinsock2でのエラーをprintfで描画します
 *
 * 戻り値：なし
 * 引数　：
 * 1. int _exception	エラー番号
*/
void GglNetwork_Winsock2PrintErrorSelect(int _exception)
{
	printf("Summary : ");
	switch(_exception)
	{
		case WSAEINTR:
			printf("connect呼び出し中に割り込みあり(WSAEINTR)\n");
			break;

		case WSAEACCES:
			printf("アクセス拒否(WSAEACCES)\n");
			break;

		case WSAEFAULT:
			printf("不正なアドレス、或いは不正なポインタ(WSAEFAULT)\n");
			break;

		case WSAEINVAL:
			printf("無効な引数(WSAEINVAL)\n");
			break;

		case WSAEMFILE:
			printf("ファイル開きすぎ(WSAEMFILE)\n");
			break;

		case WSAEWOULDBLOCK:
			printf("一時的にリソース使用不可(WSAEWOULDBLOCK)\n");
			break;

		case WSAEINPROGRESS:
			printf("現在実行中の操作(WSAEINPROGRESS)\n");
			break;

		case WSAEALREADY:
			printf("実行済みの操作(WSAEALREADY)\n");
			break;

		case WSAENOTSOCK:
			printf("ソケットに対してソケット操作を行なってください(WSAENOTSOCK)\n");
			break;

		case WSAEDESTADDRREQ:
			printf("送信先のアドレスが必要(WSAEDESTADDRREQ)\n");
			break;

		case WSAEMSGSIZE:
			printf("3行でおｋ(WSAEMSGSIZE)\n");
			break;

		case WSAEPROTOTYPE:
			printf("通信先ソケットに対するプロトコルの不一致(WSAEPROTOTYPE)\n");
			break;

		case WSAENOPROTOOPT:
			printf("不正なプロトコルオプション(WSAENOPROTOOPT)\n");
			break;

		case WSAEPROTONOSUPPORT:
			printf("サポートされていないプロトコル(WSAEPROTONOSUPPORT)\n");
			break;

		case WSAESOCKTNOSUPPORT:
			printf("サポートされていないソケットの種類(WSAESOCKTNOSUPPORT)\n");
			break;

		case WSAEOPNOTSUPP:
			printf("使用ソケットでサポートされていない操作(WSAEOPNOTSUPP)\n");
			break;

		case WSAEPFNOSUPPORT:
			printf("サポートされていないプロトコルファミリ(WSAEPFNOSUPPORT)\n");
			break;

		case WSAEAFNOSUPPORT:
			printf("プロトコルファミリはアドレスファミリをサポートしない(WSAEAFNOSUPPORT)\n");
			break;

		case WSAEADDRINUSE:
			printf("アドレス使用中(WSAEADDRINUSE)\n");
			break;

		case WSAEADDRNOTAVAIL:
			printf("要求されたアドレスは割り当てられない(WSAEADDRNOTAVAIL)\n");
			break;

		case WSAENETDOWN:
			printf("ネットワークダウンなう(WSAENETDOWN)\n");
			break;

		case WSAENETUNREACH:
			printf("ICMPネットワークへ到達できない(WSAENETUNREACH)\n");
			break;

		case WSAENETRESET:
			printf("ネットワークリセットによる切断(WSAENETRESET)\n");
			break;

		case WSAECONNABORTED:
			printf("ソフトウェアによる接続の中止(WSAECONNABORTED)\n");
			break;

		case WSAECONNRESET:
			printf("Pearによる接続のリセット(WSAECONNRESET)\n");
			break;

		case WSAENOBUFS:
			printf("サポートされていないバッファ領域(WSAENOBUFS)\n");
			break;

		case WSAEISCONN:
			printf("ソケットは既に接続済みである(WSAEISCONN)\n");
			break;

		case WSAENOTCONN:
			printf("ソケット未接続(WSAENOTCONN)\n");
			break;

		case WSAESHUTDOWN:
			printf("ソケットはシャットダウンしているというのに何を送ろうとしているのだい？(WSAESHUTDOWN)\n");
			break;

		case WSAETIMEDOUT:
			printf("接続のタイムアウト(WSAETIMEDOUT)\n");
			break;

		case WSAECONNREFUSED:
			printf("接続拒否されてやんの(WSAECONNREFUSED)\n");
			break;

		case WSAEHOSTDOWN:
			printf("ホストダウンしてるって知ってた？(WSAEHOSTDOWN)\n");
			break;

		case WSAEHOSTUNREACH:
			printf("ホストへのルートくらい確保しとけよ…(WSAEHOSTUNREACH)\n");
			break;

		case WSAEPROCLIM:
			printf("プロセス多すぎワロタ(WSAEPROCLIM)\n");
			break;

		case WSASYSNOTREADY:
			printf("ネットワークサブシステム利用不可(準備が完了していない)(WSASYSNOTREADY)\n");
			break;

		case WSAVERNOTSUPPORTED:
			printf("このバージョンのWinsock.dllはサポートされていない(WSAVERNOTSUPPORTED)\n");
			break;

		case WSANOTINITIALISED:
			printf("WSAStartupを成功させてからまたお越しくださいませお客様(WSANOTINITIALISED)\n");
			break;

		case WSAEDISCON:
			printf("正常なシャットダウン処理が進行中(WSAEDISCON)\n");
			break;

		case WSATYPE_NOT_FOUND:
			printf("この種類のクラスが見つからないっていう(WSATYPE_NOT_FOUND)\n");
			break;

		case WSAHOST_NOT_FOUND:
			printf("ホストが見つからないっていうか、そんなホストないんじゃね？再確認よろ(WSAHOST_NOT_FOUND)\n");
			break;

		case WSATRY_AGAIN:
			printf("ホストが見つからないっていうか、その手合いの権限持ってる鯖から応答ないんだよね(WSATRY_AGAIN)\n");
			break;

		case WSANO_RECOVERY:
			printf("誰かAEDもってこい！！(回復不能なエラーの発生)(WSANO_RECOVERY)\n");
			break;

		case WSANO_DATA:
			printf("名前は合ってる。が、そんな種類のデータレコードは無い(WSANO_DATA)\n");
			break;

		case WSA_INVALID_HANDLE:
			printf("指定されたイベントオブジェクトハンドルにNULLでも突っ込まれてるんじゃないか？(WSA_INVALID_HANDLE)\n");
			break;

		case WSA_INVALID_PARAMETER:
			printf("渡されたパラメータの幾つかは無効だぜ。ブレークポイント置いて確認汁(WSA_INVALID_PARAMETER)\n");
			break;

		case WSA_IO_INCOMPLETE:
			printf("重複したI/Oイベントはシグナルされていない(WSA_IO_INCOMPLETE)\n");
			break;

		case WSA_IO_PENDING:
			printf("重複した操作は後に完了するよー(WSA_IO_PENDING)\n");
			break;

		case WSA_NOT_ENOUGH_MEMORY:
			printf("メモリ不足してるぞ。余計なソフト落とすかメモリ増設するかページング容量増やそうぜ(WSA_NOT_ENOUGH_MEMORY)\n");
			break;

		case WSA_OPERATION_ABORTED:
			printf("重複した操作取り消されちゃったなう(WSA_OPERATION_ABORTED)\n");
			break;

		//case WSAINVALIDPROCTABLE:
		//	printf("サービス・プロバイダから帰ってきたプロシージャテーブルが無効(WSAINVALIDPROCTABLE)\n");
		//	break;

		//case WSAINVALIDPROVIDER:
		//	printf("サービスプロバイダのバージョン番号が無効(WSAINVALIDPROVIDER)\n");
		//	break;

		//case WSAPROVIDERFAILEDINIT:
		//	printf("サービスプロバイダ初期化不可能(WSAPROVIDERFAILEDINIT)\n");
		//	break;

		case WSASYSCALLFAILURE:
			printf("システムコール失敗なう(WSASYSCALLFAILURE)\n");
			break;
	}

	printf("エラータイプ : Network - winsock2\n");
	printf("エラーコード : %d\n\n", _exception);
	return ;
}

//#endif