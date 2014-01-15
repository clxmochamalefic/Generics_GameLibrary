#include "Generic_GameLibrary.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

// 注意！
// この関数の戻り値は動的配列です！！
// 必ずFreeしてください
//
// GglString_ExtractErase関数
// 指定した文字列からいくつかの任意の文字列を抜き取った文字を返します
// 例えば、"sixaxis"という単語から"si"と"x"を抜きたいときは、
// GglString_ExtractErase(2, "sixaxis", "si", "x");
// と書きます
// なお、この場合の戻り値は"ais"です
GglBoolean GglString_ExtractErase(const int ic_count, GglString o_str, const int tgtlen, const GglString ic_target, ...)
{
	GglString	in;		// ic_targetとそこから削ぎ落とす前の文字列を置く
	GglString	out;	// 削ぎ落とした後の文字列を置く
	GglString	str;
	int			i;
	va_list		list;
	char*		pos;
	char*		prev = NULL;
	int			count= 0;

	if(ic_target == NULL)
	{
		if(o_str != NULL)
		{
			*o_str = 0;
		}

		return GglFalse;
	}

	if(o_str == NULL)
	{
		return GglFalse;
	}
	
	va_start(list, ic_target);
	in = (GglString)GglMemory_New(sizeof(char)*tgtlen);
	memset(in, 0, tgtlen);
	strncpy(in, ic_target, tgtlen);


	while( count++ < ic_count)
	{
		str = va_arg(list, GglString);
		i = 0;
		out = (GglString)malloc(sizeof(char)*strlen(in)+1);
		memset(out, 0, strlen(in)+1);

		for( (prev == NULL) ? (pos = in) : (pos = prev); pos != NULL; pos = prev+strlen(str))
		{
			prev = strstr(pos, str);
			
			if(prev == NULL)
			{
				for(;pos != (in + strlen(in)); pos++, i++)
				{
					*(out+i) = *pos;
				}

				break;
			}

			for(;pos != prev; pos++, i++)
			{
				*(out + i) = *pos;
			}
		}

		free(in);
		in = (GglString)malloc(sizeof(char)*(strlen(out)+1));
		memset(in, 0, strlen(out)+1);
		strncpy(in, out, strlen(out)+1);
	}

	free(out);
	va_end(list);

	strncpy(o_str, in, strlen(in)+1);
	free(in);
	return GglTrue;
}

GglString GglString_EraseFirst(int _eraseLength, GglString _target)
{
	int targetLength = (int)strlen(_target);
	int i,j;

	if(targetLength - _eraseLength <= 0)
	{
		return "\0";
	}

	for(i=0, j=0; i<targetLength; i++)
	{
		if( i < _eraseLength )
		{
			continue;
		}

		(_target[j]) = (_target[i]);
		j++;
	}

	(_target[j]) = '\0';

	return _target;
}

/**
 * 文字列生成関数
 *
 * @param	生成元文字列
 * @param	文字列長さ
 * @return	生成した文字列
*/
GglString GglString_MakeString(GglString str, GglSize length)
{
	return ( strncpy( (char*)GglMemory_New(length), str, length) );
}