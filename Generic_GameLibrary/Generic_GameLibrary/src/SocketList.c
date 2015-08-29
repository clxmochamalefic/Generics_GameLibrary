#include "SocketList.h"

void GglSocketList_Initialize(GglSocketList* self)
{
	self->head				= (GglSocketNode*)GglMemory_New(sizeof(GglSocketNode));
	self->tail				= (GglSocketNode*)GglMemory_New(sizeof(GglSocketNode));

	self->head->next		= self->tail;
	self->head->prev		= NULL;
	self->head->socket		= (GglSocket)NULL;
	self->head->recvObject	= NULL;
	self->head->sendObject	= NULL;

	self->tail->next		= NULL;
	self->tail->prev		= self->head;
	self->tail->socket		= (GglSocket)NULL;
	self->tail->recvObject	= NULL;
	self->tail->sendObject	= NULL;

	self->hostServerModule	= NULL;

	self->count				= 0;
	self->useNetworkFlag	= GglTrue;
}

void GglSocketList_Shutdown(GglSocketList* self)
{
	if(self->useNetworkFlag == GglFalse)
	{
		return;
	}

	GglSocketList_RemoveAllElements(self);

	if(self->hostServerModule != NULL)
	{
		GglMemory_Delete(self->hostServerModule);
		self->hostServerModule = NULL;
	}

	return;
}

GglBoolean GglSocketList_AddElement(GglSocketList* self, GglSocketNode* _this)
{
	if(_this == NULL)
	{
		GglDebug_PrintAlertLine("_this‚ªNULL‚Á‚Ä‚é");
		return GglFalse;
	}

	self->head->next->prev	= _this;
	_this->next				= self->head->next;
	self->head->next		= _this;
	_this->prev				= self->head;

	self->count++;

	GglDebug_PrintInformationLine("Success Add Network List");
	return GglTrue;
}

GglBoolean GglSocketList_RemoveElement(GglSocketList* self, GglSocketNode* _this)
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

	self->count--;
	return GglTrue;
}

GglBoolean GglSocketList_RemoveElementAt(GglSocketList* self, unsigned int _element)
{
	GglSocketNode* node;

	if(_element >= self->count)	return GglFalse;

	for(node = self->head->next; _element != 0; node = node->next, _element--)
	{
		if(node == self->tail || node == NULL)
		{
			GglDebug_PrintExceptionLine();
			return GglFalse;
		}
	}

	if(GglSocketList_RemoveElement(self, node) == GglFalse)
	{
		return GglFalse;
	}

	return GglTrue;
}

GglBoolean GglSocketList_RemoveAllElements(GglSocketList* self)
{
	for(;self->count != 0;)	GglSocketList_RemoveElement(self, self->head->next);

	return GglTrue;
}