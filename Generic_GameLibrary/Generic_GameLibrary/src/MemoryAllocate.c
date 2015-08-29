#include "Generic_GameLibrary.h"
#include <limits.h>

GglBoolean GglMemory_Initialize(void)
{
	g_memoryList.head = (GglMemory*)malloc(sizeof(GglMemory));
	g_memoryList.tail = (GglMemory*)malloc(sizeof(GglMemory));

	g_memoryList.head->prev			= NULL;
	g_memoryList.head->next			= g_memoryList.tail;
	g_memoryList.head->memorySize	= UINT_MAX;
	g_memoryList.head->object		= "Head";

	g_memoryList.tail->prev			= g_memoryList.head;
	g_memoryList.tail->next			= NULL;
	g_memoryList.tail->memorySize	= UINT_MAX;
	g_memoryList.tail->object		= "Tail";

	g_memoryList.maxRegist			= 0;
	g_memoryList.memorySum			= 0;

	return GglTrue;
}

GglBoolean GglMemory_Shutdown(void)
{
	GglMemory_AllDelete();

	free(g_memoryList.head);
	free(g_memoryList.tail);

	g_memoryList.head = NULL;
	g_memoryList.tail = NULL;
	
	return GglTrue;
}

GglObject GglMemory_New(GglSize _size)
{
	GglMemory* memory					= (GglMemory*)malloc(sizeof(GglMemory));

	if(memory == NULL)
	{
		GglDebug_PrintExceptionLine();
		return NULL;
	}

	memory->object						= malloc(_size);

	if(memory->object == NULL)
	{
		GglDebug_PrintExceptionLine();
		GglMemory_Delete(memory);
		return NULL;
	}

	memory->next						= g_memoryList.head->next;
	memory->prev						= g_memoryList.head;
	g_memoryList.head->next->prev	= memory;
	g_memoryList.head->next			= memory;

	g_memoryList.memorySum			+= (_size + sizeof(GglMemory));
	memory->memorySize					= _size;

	g_memoryList.maxRegist++;

	return memory->object;
}

static GglBoolean GglMemory_DeleteAndReconnect(GglMemory* _this)
{
	if(_this == NULL)
	{
		GglDebug_PrintExceptionLine();
		return GglFalse;
	}

	_this->prev->next	= _this->next;
	_this->next->prev	= _this->prev;
	_this->next			= NULL;
	_this->prev			= NULL;

	if(_this->object != NULL)
	{
		free(_this->object);
		_this->object = NULL;
	}

	g_memoryList.memorySum -= (_this->memorySize + sizeof(GglMemory));
	free(_this);
	_this = NULL;

	g_memoryList.maxRegist--;

	return GglTrue;
}

GglBoolean GglMemory_Delete(GglObject _object)
{
	GglMemory* _this;

	if(_object == NULL)
	{
		GglDebug_PrintExceptionLine();
		return GglFalse;
	}

	GGL_FOREACH(_this, g_memoryList.head->next, g_memoryList.tail, next)
	{
		if(_this->object == _object)
		{
			if(GglMemory_DeleteAndReconnect(_this) == GglTrue)
			{
				return GglTrue;
			}
			else
			{
				break;
			}
		}

		if(_this->next == NULL && _this->prev == NULL)
		{
			GglMemory_ReconnectList(NULL, NULL);
			_this = g_memoryList.head;
			continue;
		}

		if(_this->next == NULL)
		{
			GglMemory_ReconnectList(_this, NULL);
		}
		else if(_this->prev == NULL)
		{
				GglMemory_ReconnectList(NULL, _this);
		}
	}

	GglDebug_PrintExceptionLine();
	return GglFalse;
}

static GglBoolean GglMemory_DeleteSearchTask(GglMemory* _memory)
{
	GglMemory* _this;

	if(_memory == NULL)
	{
		GglDebug_PrintExceptionLine();
		return GglFalse;
	}

	for(_this = g_memoryList.head->next; _this != g_memoryList.tail; _this = _this->next)
	{
		if(_this == _memory)
		{
			if(GglMemory_DeleteAndReconnect(_this) == GglTrue)
				return GglTrue;
			else
				return GglFalse;
		}

		if(_this->next == NULL)
		{
			GglMemory_ReconnectList(_this, NULL);
		}
	}

	GglDebug_PrintExceptionLine();
	return GglFalse;
}

GglBoolean GglMemory_AllDelete(void)
{
	for(;g_memoryList.head->next != g_memoryList.tail;)
	{
		if(GglMemory_DeleteSearchTask(g_memoryList.head->next) == GglFalse)
		{
			return GglFalse;
		}
	}

	return GglTrue;
}

void GglMemory_ReconnectList(GglMemory* _first, GglMemory* _end)
{
	if(_first == NULL)
		_first = GglMemory_SearchNull2First();

	if(_end == NULL)
		_end = GglMemory_SearchNull2End();

	if(_first == NULL && _end == NULL)
	{
		return ;
	}
	else if(_first == NULL || _end == NULL)
	{
		GglDebug_PrintExceptionLine();
		return ;
	}

	_first->next	= _end;
	_end->prev		= _first;

	return ;
}

static GglMemory* GglMemory_SearchNull2First(void)
{
	GglMemory* _this;
	GglMemory* _back = NULL;

	GGL_FOREACH(_this, g_memoryList.head, g_memoryList.tail, next)
	{
		if(_this->next == NULL)
		{
			return _back;
		}

		_back = _this;
	}

	return NULL;
}

static GglMemory* GglMemory_SearchNull2End(void)
{
	GglMemory* _this;
	GglMemory* _back = NULL;

	GGL_FOREACH(_this, g_memoryList.tail, g_memoryList.head, prev)
	{
		if(_this->prev == NULL)
		{
			return _back;
		}

		_back = _this;
	}

	return NULL;
}