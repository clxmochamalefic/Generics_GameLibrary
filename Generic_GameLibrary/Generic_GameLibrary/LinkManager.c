#include "Generic_GameLibrary.h"
#include <stdlib.h>

/****************************************
 * GglLinkList_Constracter関数
 * LinkListシステムを起動します
 * プログラム起動時に起動するだけでOKです
 * 
 * 戻り値：GglBoolean GglTrueで成功, GglFalseで失敗
 * 引数：
*/
void GglLinkList_Initialize(void)
{
	// headとtailの動的メモリ確保
	g_linkList.head = (GglLink*)GglMemory_New(sizeof(GglLink));
	g_linkList.tail = (GglLink*)GglMemory_New(sizeof(GglLink));

	// headの初期設定
	g_linkList.head->prev		= NULL;
	g_linkList.head->next		= g_linkList.tail;
	g_linkList.head->object		= NULL;
	g_linkList.head->priority	= PrioLinkHead;
	g_linkList.head->status		= StatusLive;
	g_linkList.head->name		= "LinkHead\0";

	g_linkList.head->hit.hitUse	= GglFalse;
	
	g_linkList.head->Update		= NULL;
	g_linkList.head->Draw		= NULL;

	// tailの初期設定
	g_linkList.tail->next		= NULL;
	g_linkList.tail->prev		= g_linkList.head;
	g_linkList.tail->object		= NULL;
	g_linkList.tail->priority	= PrioLinkTail;
	g_linkList.tail->status		= StatusLive;
	g_linkList.tail->name		= "LinkTail\0";

	g_linkList.tail->hit.hitUse	= GglFalse;

	g_linkList.tail->Update		= NULL;
	g_linkList.tail->Draw		= NULL;

	// 現在のタスク最大数初期化
	g_linkList.count			= 0;

	return ;
}

void GglLinkList_Shutdown(void)
{
	GglLinkList_RemoveAllElements();

	GglMemory_Delete(g_linkList.head);
	g_linkList.head = NULL;

	GglMemory_Delete(g_linkList.tail);
	g_linkList.tail = NULL;

	return ;
}

GglBoolean GglLinkList_AddElement(GglLink* _new)
{
	if(_new == NULL)	return GglFalse;

	g_linkList.head->next->prev = _new;
	_new->next			= g_linkList.head->next; 
	g_linkList.head->next		= _new;
	_new->prev			= g_linkList.head;

	g_linkList.count++;

	return GglTrue;
}

GglBoolean GglLinkList_RemoveElement(GglLink* _del)
{
	GglLink* seek;

	if(_del == NULL)				return GglFalse;
	if(_del == g_linkList.head)	return GglFalse;
	if(_del == g_linkList.tail)	return GglFalse;

	for(seek = g_linkList.head; seek != _del; seek = seek = seek->next)
	{
		if(seek == g_linkList.tail)
			return GglFalse;
	}

	_del->prev->next = _del->next;
	_del->next->prev = _del->prev;

	GglMemory_Delete(_del->object);
	_del->object = NULL;

	GglMemory_Delete(_del);
	_del = NULL;

	g_linkList.count--;

	return GglTrue;
}

GglBoolean GglLinkList_RemoveElementAt(const int ic_element)	//LinkTaskから指定したノードを削除
{
	GglLink*	seek;
	int			count = 0;

	if(ic_element >= g_linkList.count)
		return GglFalse;

	//for(seek = g_linkList.head->next; _element != 0; _element--, seek = seek->next){}
	GGL_FOREACH(seek, g_linkList.head->next, g_linkList.tail, next)
	{
		if( (count++) == ic_element)
		{
			break;
		}
	}

	if(seek == NULL)
		return GglFalse;

	seek->prev->next = seek->next;
	seek->next->prev = seek->prev;

	GglMemory_Delete(seek->object);
	seek->object = NULL;

	GglMemory_Delete(seek);
	seek = NULL;

	g_linkList.count--;

	return GglTrue;
}

void GglLinkList_RemoveAllElements(void)
{
	//while(g_linkList.head->next != g_linkList.tail)
	//	GglLinkList_RemoveElement(g_linkList.head->next);

	for(;g_linkList.head->next != g_linkList.tail;)
		GglLinkList_RemoveElement(g_linkList.head->next);

	g_linkList.count = 0;

	return ;
}

void GglLinkList_Update(void)
{
	GglLink* pThis;	// 参照しているタスク

	GGL_FOREACH(pThis, g_linkList.head->next, g_linkList.tail, next)
	{
		if(pThis == NULL)
		{
			GglDebug_PrintAlertLine("実行中にリストが切断されていることを確認");
			break;
		}

		if(pThis->status == StatusDelete)
		{
			pThis = pThis->prev;
			GglLinkList_RemoveElement(pThis->next);
			continue;
		}

		if(pThis->Update != NULL)
		{
			pThis->Update(pThis, pThis->object);
		}

		pThis = pThis->next;
	};

	return ;
}

void GglLinkList_Draw(void)
{
	GglLink* pThis;	// 参照しているタスク

	GGL_FOREACH(pThis, g_linkList.head->next, g_linkList.tail, next)
	{
		if(pThis == NULL)
		{
			GglDebug_PrintAlertLine("描画中にリストが切断されていることを確認");
			return ;
		}

		if(pThis->Draw != NULL)
		{
			pThis->Draw(pThis->object);
		}
		
		pThis = pThis->next;
	};

	return ;
}