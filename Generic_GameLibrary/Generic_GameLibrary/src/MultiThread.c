#include "Generic_GameLibrary.h"

#include <process.h>

GglBoolean GglMultiThread_Initialize(void)
{
	g_multiThread.head = (GglThread*)GglMemory_New(sizeof(GglThread));
	g_multiThread.tail = (GglThread*)GglMemory_New(sizeof(GglThread));

	if(g_multiThread.tail == NULL || g_multiThread.head == NULL)
	{
		GglDebug_PrintExceptionLine();
		return GglFalse;
	}

	g_multiThread.head->next		= g_multiThread.tail;
	g_multiThread.head->prev		= NULL;
	g_multiThread.head->thread		= NULL;
	g_multiThread.head->argument	= "HEAD";
	g_multiThread.head->loopFlag	= GglFalse;

	g_multiThread.tail->next		= NULL;
	g_multiThread.tail->prev		= g_multiThread.head;
	g_multiThread.tail->thread		= NULL;
	g_multiThread.tail->argument	 = "TAIL";
	g_multiThread.tail->loopFlag	= GglFalse;

	g_multiThread.array			= NULL;
	g_multiThread.count			= 0;
	g_multiThread.useMultiThreadFlag= GglTrue;

	return GglTrue;
}

void GglMultiThread_Shutdown(void)
{
	if(g_multiThread.useMultiThreadFlag == GglFalse)
	{
		return ;
	}

	if(g_multiThread.count != 0 || g_multiThread.head->next != g_multiThread.tail)
	{
		GglMultiThread_RemoveAllThread();
	}

	g_multiThread.head->next = NULL;
	g_multiThread.head->prev = NULL;

	g_multiThread.tail->next = NULL;
	g_multiThread.tail->prev = NULL;

	if(g_multiThread.head != NULL)
		GglMemory_Delete(g_multiThread.head);

	if(g_multiThread.tail != NULL)
		GglMemory_Delete(g_multiThread.tail);

	g_multiThread.head = NULL;
	g_multiThread.tail = NULL;

	return ;
}

// Debug -- 書き直しの余地あり　ここからGglMemoryにてfreeバグが発生 ////////////////////////////////////
GglBoolean GglMultiThread_AddThread(GglThread* _pThreadInst)
{
	HANDLE* array = NULL;
	int i;
	_pThreadInst->loopFlag = GglTrue;

	if(g_multiThread.head == NULL || g_multiThread.tail == NULL)
	{
		// マルチスレッドシステム未初期化
		GglDebug_PrintExceptionLine();
		return GglFalse;
	}

	_pThreadInst->prev			= g_multiThread.tail->prev;
	g_multiThread.tail->prev->next	= _pThreadInst;
	g_multiThread.tail->prev			= _pThreadInst;
	_pThreadInst->next			= g_multiThread.tail;

	if( g_multiThread.array != NULL && g_multiThread.count == 0 )
	{
		array = (HANDLE*)GglMemory_New( sizeof( HANDLE ) * g_multiThread.count );

		for( i=0; i<g_multiThread.count; i++ )
		{
			array[i] = g_multiThread.array[i];
		}

		GglMemory_Delete( g_multiThread.array );
	}

	g_multiThread.array = (HANDLE*)GglMemory_New( sizeof( HANDLE ) * (g_multiThread.count + 1) );

	if( array != NULL )
	{
		for( i=0; i<g_multiThread.count; i++ )
		{
			g_multiThread.array[i] = array[i];
		}

		GglMemory_Delete( array );
		array = NULL;
	}

	g_multiThread.array[g_multiThread.count] = _pThreadInst->thread;

	g_multiThread.count++;

	return GglTrue;
}

GglBoolean GglMultiThread_AddNewThread(void(*_funcName)(void*),
									  unsigned _stackSize,
									  void* _argStructInstance)
{
	GglThread* pThread		= (GglThread*)GglMemory_New(sizeof(GglThread));
	pThread->argument	= _argStructInstance;

	pThread->thread		= (HANDLE)GglMultiThread_BeginThread(_funcName, _stackSize, pThread);

	if(pThread->thread == NULL)
	{
		// スレッドがMakeされなかった
		GglDebug_PrintExceptionLine();
		GglMemory_Delete(pThread);
		return GglFalse;
	}

	// スレッド登録試行
	if(GglMultiThread_AddThread(pThread) == GglFalse)
	{
		// スレッド登録失敗
		GglDebug_PrintExceptionLine();
		return GglFalse;
	}

	return GglTrue;
}

GglBoolean GglMultiThread_RemoveThread(GglThread* _pThreadInst)
{
	GglThread* __this;
	HANDLE*	array = NULL;
	int		i,j;

	if( _pThreadInst == NULL )
	{
		GglDebug_PrintExceptionLine();
		return GglFalse;
	}

	for( __this = g_multiThread.head->next; __this != g_multiThread.tail; __this = __this->next )
	{
		if( __this == _pThreadInst)
		{
			__this->prev->next	= __this->next;
			__this->next->prev	= __this->prev;

			__this->next		= NULL;
			__this->prev		= NULL;

			g_multiThread.count--;

			if(g_multiThread.count > 0)
			{
				GglMemory_Delete(g_multiThread.array);
				g_multiThread.array = NULL;
				g_multiThread.array = (HANDLE*)GglMemory_New( sizeof( HANDLE ) * g_multiThread.count );
				for(__this = g_multiThread.head->next, i = 0; __this != g_multiThread.tail; __this = __this->next, i++)
				{
					g_multiThread.array[i] = __this;
				}
			}


			// バグの可能性 //////////////////////////////////////////////////////////////////////////////////
			if( g_multiThread.count > 1 )
			{
				if( g_multiThread.array != NULL && g_multiThread.count == 0 )
				{
					array = (HANDLE*)GglMemory_New( sizeof( HANDLE ) * g_multiThread.count );

					for( i=0; i<g_multiThread.count; i++ )
					{
						array[i] = g_multiThread.array[i];
					}

					GglMemory_Delete( g_multiThread.array );
				}

				g_multiThread.array = (HANDLE*)GglMemory_New( sizeof( HANDLE ) * g_multiThread.count );

				if(array != NULL)
				{
					for( i=0, j=0; i<g_multiThread.count-1; i++ )
					{
						if( array[i] == _pThreadInst->thread )
						{
							continue;
						}

						g_multiThread.array[j] = array[i];
						j++;
					}
				}

				if( array != NULL )
				{
					GglMemory_Delete( array );
					array = NULL;
				}
			}
			else
			{
				GglMemory_Delete(g_multiThread.array);
			}

			GglMemory_Delete( _pThreadInst );

			g_multiThread.count--;


			return GglTrue;
		}
	}

	GglDebug_PrintExceptionLine();
	return GglFalse;
}

GglBoolean GglMultiThread_RemoveAllThread(void)
{
	for(; g_multiThread.head->next != g_multiThread.tail;)
	{
		GglMultiThread_RemoveThread(g_multiThread.head->next);
	}

	return GglTrue;
}

GglBoolean GglMultiThread_LoopFlagSwitch(GglThread* _this)
{
	_this->loopFlag = GglFalse;

	return GglTrue;
}