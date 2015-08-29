#ifndef GglSocketList_h__
#define GglSocketList_h__

#include "Definition.h"
#include "Socket.h"

/**
 * GglSocketList構造体
 * ソケットのリスト
 */
struct GglSocketList
{
	GglSocketNode*	head;				// 通信リストの先端
	GglSocketNode*	tail;				// 通信リストの最後尾

	GglSocketNode*	hostServerModule;	// ホスト、あるいはサーバを作った時のソケット

	unsigned int	count;				// 通信している数
	GglBoolean		useNetworkFlag;		// ネットワーク使用フラグ

}typedef GglSocketList;


void GglSocketList_Initialize(GglSocketList* self);
void GglSocketList_Shutdown(GglSocketList* self);

GglBoolean GglSocketList_AddElement(GglSocketList* self, GglSocketNode* node);
GglBoolean GglSocketList_RemoveElement(GglSocketList* self, GglSocketNode* node);
GglBoolean GglSocketList_RemoveElementAt(GglSocketList* self, unsigned int element);
GglBoolean GglSocketList_RemoveAllElements(GglSocketList* self);

void		GglSocketList_GetIpAddress(GglSocketList* self, GglString out_ipAddr);	// 自己IP取得
GglBoolean	GglSocketList_MakeSocket(GglSocketList* self, GglSocketNode* _pModule, GglString _addressString, int _usePort);

//void		GglSocketList_HostServerWaitGuestClient(GglObject _object);
GglBoolean	GglSocketList_HostServerWaitGuestClientOnce(GglSocketList* self, GglObject _object);

void		GglSocketList_ReceiveData(GglSocketList* self, GglObject _object);
void		GglSocketList_SendData(GglSocketList* self, GglObject _object);

#endif