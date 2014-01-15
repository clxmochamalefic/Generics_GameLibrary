#include "Generic_GameLibrary.h"

GglBoolean GglNetworkList_Initialize(void)
{
	g_networkList.head				= (GglSocketNode*)GglMemory_New(sizeof(GglSocketNode));
	g_networkList.tail				= (GglSocketNode*)GglMemory_New(sizeof(GglSocketNode));

	g_networkList.head->next			= g_networkList.tail;
	g_networkList.head->prev			= NULL;
	g_networkList.head->socket		= (GglSocket)NULL;
	g_networkList.head->recvObject	= NULL;
	g_networkList.head->sendObject	= NULL;

	g_networkList.tail->next			= NULL;
	g_networkList.tail->prev			= g_networkList.head;
	g_networkList.tail->socket		= (GglSocket)NULL;
	g_networkList.tail->recvObject	= NULL;
	g_networkList.tail->sendObject	= NULL;

	g_networkList.hostServerModule	= NULL;

	g_networkList.count			= 0;
	g_networkList.useNetworkFlag		= GglTrue;

	return GglTrue;
}

GglBoolean GglNetworkList_Shutdown(void)
{
	if(g_networkList.useNetworkFlag == GglFalse)
	{
		return GglTrue;
	}

	GglNetworkList_RemoveAllElements();

	if(g_networkList.hostServerModule != NULL)
	{
		GglMemory_Delete(g_networkList.hostServerModule);
		g_networkList.hostServerModule = NULL;
	}

	return GglTrue;
}

GglBoolean GglNetworkList_AddElement(GglSocketNode* _this)
{
	if(_this == NULL)
	{
		GglDebug_PrintAlertLine("_this‚ªNULL‚Á‚Ä‚é");
		return GglFalse;
	}

	g_networkList.head->next->prev	= _this;
	_this->next							= g_networkList.head->next;
	g_networkList.head->next			= _this;
	_this->prev							= g_networkList.head;

	g_networkList.count++;

	GglDebug_PrintInformationLine("Success Add Network List");
	return GglTrue;
}

GglBoolean GglNetworkList_RemoveElement(GglSocketNode* _this)
{
	if(_this == NULL)
	{
		GglDebug_PrintAlertLine("_this‚ªNULL‚Á‚Ä‚é");
		return GglFalse;
	}

	_this->prev->next	= _this->next;
	_this->next->prev	= _this->prev;

	_this->next			= NULL;
	_this->prev			= NULL;

	GglMemory_Delete(_this);
	_this				= NULL;

	g_networkList.count--;
	return GglTrue;
}

GglBoolean GglNetworkList_RemoveElementAt(unsigned int _elements)
{
	GglSocketNode* _this;

	if(_elements >= g_networkList.count)
		return GglFalse;

	for(_this = g_networkList.head->next; _elements != 0; _this = _this->next, _elements--)
	{
		if(_this == g_networkList.tail)
			return GglFalse;

		if(_this == NULL)
		{
			GglDebug_PrintExceptionLine();
			return GglFalse;
		}
	}

	if(GglNetworkList_RemoveElement(_this) == GglFalse)
	{
		return GglFalse;
	}

	return GglTrue;
}

GglBoolean GglNetworkList_RemoveAllElements(void)
{
	for(;g_networkList.count != 0;)
		GglNetworkList_RemoveElement(g_networkList.head->next);

	return GglTrue;

}