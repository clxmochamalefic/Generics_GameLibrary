#include "Generic_GameLibrary.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>

//#include <ctype.h>

#pragma warning(disable : 4996)

/**
 * GglModel_Initialize
 * モデルデータを初期化する
 * @return	初期化したモデルデータを返す
 * @param	初期化したモデルデータを渡す
*/
GglModel* GglModel_Initialize(GglModel* out_model)
{
	GglModel* model = (GglModel*)GglMemory_New(sizeof(GglModel));
	
	model->face.index			= NULL;
	model->face.max				= 0;
	model->material.index		= NULL;
	model->material.max			= 0;
	model->name					= NULL;
	model->face.normals			= NULL;
	model->useSkinAnimationFlag	= GglFalse;
	model->vertex.color			= NULL;
	model->vertex.index			= NULL;
	model->vertex.max			= 0;

	if(out_model)
	{
		model = out_model;
	}

	return model;
}

/**
 * GglModel_LoadModel関数
 * モデルデータを拡張子から判別して読み込む関数
 * @return	読み込んだモデルデータを返す
 * @param	ファイル名
 * @param	読み込んだモデルデータを渡す
*/
GglModel* GglModel_LoadModel(const GglString in_fileName, GglModel* out_model)
{
	GglModel* model = GglModel_Initialize(NULL);

	if(strstr(in_fileName, ".x") != NULL)
	{
		GglModel_LoadModel2X(in_fileName, model);
	}
	else if(strstr(in_fileName, ".mqo") != NULL)
	{
		GglModel_LoadModel2X(in_fileName, model);
	}
	else
	{
		out_model = NULL;
		return NULL;
	}

	if(out_model)
	{
		out_model = model;
	}

	return model;
}


GglBoolean GglModel_LoadModel2X(const GglString in_fileName, GglModel* _pModel)
{
	FILE*			pFile;
	char			buffer[256];
	int				num						= 0;
	GglSize			deleteSize				= 0;
	GglSize			nameLength				= 0;
	
	//long			meshAddressPos;
	//long			materialListAddressPos;
	long			meshNormalsPos			= -1;
	long			meshTextureCoordsPos	= -1;

	/* Xファイルの読み込み開始 */
	pFile = fopen(in_fileName, "r");
	if(pFile == NULL)
	{
		GglDebug_PrintExceptionLine();
		printf("Failed File Open...\n");
		_pModel->name = "null\0";
		return GglFalse;
	}

	//while( fgets(buffer, 256, pFile) != NULL)
	for(fgets(buffer, 256, pFile); feof(pFile) == GglFalse; fgets(buffer, 256, pFile))
	{
		if(strstr(buffer,"template") != NULL)
		{
			continue;																		// テンプレート読み飛ばし
		}
		
		if(strstr(buffer,"Mesh ") != NULL)														
		{
			GglModel_LoadModel2X_ReadMesh(pFile, _pModel, buffer);
		}
		else if(strstr(buffer, "MeshMaterialList ") != NULL)
		{
			GglModel_LoadModel2X_ReadMaterialList(pFile, _pModel);
		}
		else if(strstr(buffer, "MeshVertexColors") != NULL)
		{
			GglModel_LoadModel2X_ReadMeshVertexColors(pFile, _pModel);
		}
		else if(strstr(buffer, "MeshNormals") != NULL)
		{
			GglModel_LoadModel2X_ReadMeshNormals(pFile, _pModel, &meshNormalsPos);
		}
		else if(strstr(buffer, "MeshTextureCoords") != NULL)
		{
			GglModel_LoadModel2X_ReadMeshTextureCoords(pFile, _pModel, &meshTextureCoordsPos);
		}
	}

	//if(meshNormalsPos != -1)
	//{
	//	GglModel_LoadModel2X_ReadMeshNormals(pFile, _pModel, &meshNormalsPos);
	//}

	//if(meshTextureCoordsPos != -1)
	//{
	//	GglModel_LoadModel2X_ReadMeshTextureCoords(pFile, _pModel, &meshTextureCoordsPos);
	//}

	fclose(pFile);
	return GglTrue;
}

static void GglModel_LoadModel2X_ReadMesh(FILE* _pFile, GglModel* _pModel, GglString _buffer)
{
	char		buffer[256];
	GglString	pBuf = &buffer[0];
	int			i;
	int			nameLength;
	GglBoolean	useNameFlag	= GglFalse;

	memset(buffer, '\0', 256);
	strncpy(buffer, _buffer, strlen(_buffer));

	GglString_EraseFirst((int)strlen(" Mesh "), pBuf);

	nameLength = (unsigned int)strlen( strtok(buffer, " {") ) + 1;

	if(nameLength <= 2)
	{
		nameLength	= 10;
		useNameFlag	= GglFalse;
	}
	else
	{
		useNameFlag = GglTrue;
	}

	// 区切り文字まで抜き出し
	_pModel->name = GglString_MakeString(useNameFlag ? buffer : "Anonymous\0", useNameFlag ? strlen(buffer) : 10);

	// 総頂点数獲得
	fgets(buffer, 256, _pFile);
	_pModel->vertex.max = atoi( strtok( buffer, ";" ) );	// 文字列を数値として代入

	// 頂点座標取得
	_pModel->vertex.index = (GglVector3d*)GglMemory_New(sizeof(GglVector3d) * _pModel->vertex.max);	// 格納する動的配列確保
	for(i=0; i<(int)_pModel->vertex.max; i++)
	{
		fgets(buffer, 256, _pFile);	// 1行進める
		_pModel->vertex.index[i].x = atof( strtok(buffer, ";") );
		_pModel->vertex.index[i].y = atof( strtok(NULL, ";") );
		_pModel->vertex.index[i].z = atof( strtok(NULL, ";") );
	}

	// 総面数取得
	fgets(buffer, 256, _pFile);
	_pModel->face.max	= atoi( strtok(buffer, ";") );
	_pModel->face.index	= (GglPolygonFace*)GglMemory_New(sizeof(GglPolygonFace) * _pModel->face.max);			// 格納する動的配列確保

	// 面インデックス取得
	for(i=0; i<(int)_pModel->face.max; i++)
	{
		fgets(buffer, 256, _pFile);	// １行進める
		_pModel->face.index[i].useFourPolygon = (atoi( strtok(buffer, ";") ) == 3) ? GglFalse : GglTrue;	// 先頭のポリゴン数を表す文字列の取得

		if(_pModel->face.index[i].useFourPolygon == GglFalse)
		{
			_pModel->face.index[i].index[0] = atoi( strtok(NULL, ",") );
			_pModel->face.index[i].index[1] = atoi( strtok(NULL, ",") );
			_pModel->face.index[i].index[2] = atoi( strtok(NULL, ";") );
		}
		else if(_pModel->face.index[i].useFourPolygon == GglTrue)
		{
			_pModel->face.index[i].index[0] = atoi( strtok(NULL, ",") );
			_pModel->face.index[i].index[1] = atoi( strtok(NULL, ",") );
			_pModel->face.index[i].index[2] = atoi( strtok(NULL, ",") );
			_pModel->face.index[i].index[3] = atoi( strtok(NULL, ";") );
		}
	}

	return ;
}

static void GglModel_LoadModel2X_ReadMaterialList(FILE* _pFile, GglModel* _pModel)
{
	int i;
	int stringLength;
	char buffer[256];
	GglString	pBuf = &buffer[0];

	memset(buffer, '\0', 256);

	// マテリアルの総数を取得
	fgets(buffer, 256, _pFile);
	_pModel->material.max	= atoi( strtok(buffer, ";") );	// マテリアル総数を整数として代入

	// マテリアルがあるとき
	if(_pModel->material.max)
	{
		_pModel->material.index			= (GglMaterialList*)GglMemory_New(sizeof(GglMaterialList) * _pModel->material.max);
		fgets(buffer, 256, _pFile);
	}
	else	// ないとき
	{
		fgets(buffer, 256, _pFile);
		_pModel->material.max	= atoi( strtok(buffer, ";") );
		_pModel->material.index	= (GglMaterialList*)GglMemory_New( sizeof(GglMaterialList) * _pModel->material.max );
	}

	// マテリアルインデックス取得
	for(fgets(buffer, 256, _pFile), i=0; (unsigned int)i<_pModel->face.max; i++, fgets(buffer, 256, _pFile))
	{
		_pModel->face.index[i].materialIndex = atoi( strtok(buffer, ",") );
	}

	// マテリアル取得
	for(i=0; i<(int)_pModel->material.max; i++)
	{
		for(;strstr(buffer, " Material ") == NULL;)
		{
			fgets(buffer, 256, _pFile);
		}

		// 拡散光（ディフューズ）取得
		fgets(buffer, 256, _pFile);
		_pModel->material.index[i].colorType.array[0] = atof( strtok(buffer, ";") );
		_pModel->material.index[i].colorType.array[1] = atof( strtok(NULL, ";") );
		_pModel->material.index[i].colorType.array[2] = atof( strtok(NULL, ";") );
		_pModel->material.index[i].colorType.array[3] = atof( strtok(NULL, ";;") );

		// 鏡面光指数取得
		fgets(buffer, 256, _pFile);
		_pModel->material.index[i].lightPower = atoi( strtok(buffer, ";") );

		// 鏡面光（スペキュラ）取得
		fgets(buffer, 256, _pFile);
		_pModel->material.index[i].specularColor.array[0] = atof( strtok(buffer, ";") );
		_pModel->material.index[i].specularColor.array[1] = atof( strtok(NULL, ";") );
		_pModel->material.index[i].specularColor.array[2] = atof( strtok(NULL, ";") );
		_pModel->material.index[i].specularColor.array[3] = 1;

		// 放射輝度（自己発光）
		fgets(buffer, 256, _pFile);
		_pModel->material.index[i].emissionColor.array[0] = atof( strtok(buffer, ";") );
		_pModel->material.index[i].emissionColor.array[1] = atof( strtok(NULL, ";") );
		_pModel->material.index[i].emissionColor.array[2] = atof( strtok(NULL, ";") );
		_pModel->material.index[i].emissionColor.array[3] = 1.0f;
		fgets(buffer, 256, _pFile);
		fgets(buffer, 256, _pFile);

		if(strstr(buffer, "TextureFilename") != NULL)
		{
			fgets(buffer, 256, _pFile);
			pBuf			= GglString_EraseFirst(5, buffer);
			stringLength	= (int)strlen( strtok(pBuf, "\"") )+1;
			_pModel->material.index[i].textureName = (GglString)GglMemory_New( sizeof(char) * stringLength );
			strcpy(_pModel->material.index[i].textureName, buffer);
		}
		else
		{
			_pModel->material.index[i].textureName = NULL;
		}

	}

	return ;
}

static void GglModel_LoadModel2X_ReadMeshVertexColors(FILE* _pFile, GglModel* _pModel)
{
	int			i, count;
	char buffer[256];
	GglString	pBuf = &buffer[0];

	memset(buffer, '\0', 256);

	// 数の取得
	fgets(buffer, 256, _pFile);
	count = atoi( strtok(buffer, ";") );

	_pModel->vertex.color = (GglColor4*)GglMemory_New( sizeof(GglColor4) * count );

	// 頂点カラーの取得
	for(i=0; i<count; i++)
	{
		fgets(buffer, 256, _pFile);
		strtok(buffer, ";");

		_pModel->vertex.color[i].array[0] = atof( strtok(NULL, ";") );
		_pModel->vertex.color[i].array[1] = atof( strtok(NULL, ";") );
		_pModel->vertex.color[i].array[2] = atof( strtok(NULL, ";") );
		_pModel->vertex.color[i].array[3] = atof( strtok(NULL, ";;,") );
	}

	return ;
}

// 頂点の法線ベクトル取得
static void GglModel_LoadModel2X_ReadMeshNormals(FILE* _pFile, GglModel* _pModel, long* _pos)
{
	int			i;
	char		buffer[256];

	if(_pModel->vertex.max == 0)
	{
		*_pos = (long)_pFile;
		return ;
	}
	
	fgets(buffer, 256, _pFile);

	_pModel->face.normals = NULL;
	_pModel->face.normals = (GglNormal3d*)GglMemory_New(sizeof(GglNormal3d) * _pModel->vertex.max);

	for(i=0; i<(int)_pModel->vertex.max; i++)
	{
		fgets(buffer, 256, _pFile);

		_pModel->face.normals[i].x = atof( strtok(buffer, ";") );
		_pModel->face.normals[i].y = atof( strtok(NULL, ";") );
		_pModel->face.normals[i].z = atof( strtok(NULL, ";") );
	}

	return ;
}

// UV座標取得
static void GglModel_LoadModel2X_ReadMeshTextureCoords(FILE* _pFile, GglModel* _pModel, long* _pos)
{
	int			i;
	char		buffer[256];

	if(_pModel->vertex.max == 0)
	{
		*_pos = (long)_pFile;
		return ;
	}

	fgets(buffer, 256, _pFile);

	for(fgets(buffer, 256, _pFile), i=0; i<(int)_pModel->face.max; fgets(buffer, 256, _pFile), i++)
	{
		_pModel->face.index[i].uv.x = atof( strtok(buffer, ";") );
		_pModel->face.index[i].uv.y = atof( strtok(NULL, ";") );
	}
}

// モデル削除
void GglModel_DeleteModel(GglModel* _this)
{
	GglMemory_Delete(_this->face.normals);
	GglMemory_Delete(_this->face.index);
	GglMemory_Delete(_this->vertex.index);
	
	GglMemory_Delete(_this->name);
	GglMemory_Delete(_this->vertex.color);
	GglMemory_Delete(_this->vertex.index);
	GglMemory_Delete(_this->material.index);
	GglMemory_Delete(_this->material.index);

	return ;
}