#include "Generic_GameLibrary.h"
#include <math.h>

#pragma warning(disable : 4090)

/******************************************************
 * GglMatrix4x4_Add関数		足し算
 * GglMatrix4x4_Sub関数		引き算
 * GglMatrix4x4_Mul関数		掛け算
 * 行列の計算を行う関数群
 *
 * 戻り値：なし
 * 引数：
 * 1.GglMatrix4x4*			out_m	行列の演算結果を出力
 * 2.const GglMatrix4x4*	in_pM1	演算させたい行列１
 * 3.const GglMatrix4x4*	in_pM2	演算させたい行列２
 * なお、行列の掛け算に於いてはin_pM1とin_pM2に
 * 入れる行列が反対だと結果がジャムることに留意されよ
*/

// 足し算
void GglMatrix4x4_Add(GglMatrix4x4* out_pM, const GglMatrix4x4* in_pM1, const GglMatrix4x4* in_pM2)
{
	GglMatrix4x4 mat;
	double* i;
	double* j;
	double* k;

	// バッファオーバーランの可能性あり
	for(i = &mat._11, j = &in_pM1->_11, k = &in_pM2->_11; i < &mat._11 + 16; i++, j++, k++)
		*i = *j + *k;

	*out_pM = mat;
	return ;
}

// 引き算
void GglMatrix4x4_Sub(GglMatrix4x4* out_pM, const GglMatrix4x4* in_pM1, const GglMatrix4x4* in_pM2)
{
	GglMatrix4x4 mat;
	double* i;
	double* j;
	double* k;

	// バッファオーバーランの可能性あり
	for(i = &mat._11, j = &in_pM1->_11, k = &in_pM2->_11; i < &mat._11 + 16; i++, j++, k++)
		*i = *j - *k;

	*out_pM = mat;
	return ;
}

// 掛け算
void GglMatrix4x4_Mul(GglMatrix4x4* out_pM, const GglMatrix4x4* in_pM1, const GglMatrix4x4* in_pM2)
{
	GglMatrix4x4	mat;
	double*	w1;
	double*	w2;
	double*	pO = &mat._11;

	GglByte	i,j,k;
	double	f = 0;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			w1 = &in_pM1->_11 + (sizeof(double*) * i);
			w2 = &in_pM2->_11 + j;

			for(k=0; k<4; k++)
			{
				f += (*w1 * *w2);
				w1++;
				w2 += sizeof(double*);
			}

			*pO = f;
			pO++;
			f = 0;
		}
	}

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			out_pM->array[i][j] = mat.array[i][j];
		}
	}
	return ;
}

/******************************************************
 * GglMatrix4x4_AddF関数		足し算
 * GglMatrix4x4_SubF関数		引き算
 * GglMatrix4x4_MulF関数		掛け算
 * 行列の計算を行う関数群
 *
 * 戻り値：なし
 * 引数：
 * 1.double* out_pMFAdr			行列の演算結果を出力
 * 2.const double* in_pMFAdr1	演算させたい行列１
 * 3.const double* in_pMFAdr2	演算させたい行列２
 * なお、行列の掛け算に於いてはin_pM1とin_pM2に
 * 入れる行列が反対だと結果がジャムることに留意されよ
*/

// 足し算
void GglMatrix4x4_AddF(double* out_pMFAdr, const double* in_pMFAdr1, const double* in_pMFAdr2)
{
	GglMatrix4x4 mat;
	double* matAdr;
	GglByte i;

	// バッファオーバーランの可能性あり
	for(i=0, matAdr = &mat._11; i<16; i++, matAdr++)
		*matAdr = *(in_pMFAdr1 + i) + *(in_pMFAdr2 + i);

	for(i=0, matAdr = &mat._11; i<16; i++, matAdr++, out_pMFAdr++)
		*out_pMFAdr = *matAdr;

	return ;
}

// 引き算
void GglMatrix4x4_SubF(double* out_pMFAdr, const double* in_pMFAdr1, const double* in_pMFAdr2)
{
	GglMatrix4x4 mat;
	double* matAdr;
	GglByte i;

	// バッファオーバーランの可能性あり
	for(i=0, matAdr = &mat._11; i<16; i++, matAdr++)
		*matAdr = *(in_pMFAdr1 + i) - *(in_pMFAdr2 + i);

	for(i=0, matAdr = &mat._11; i<16; i++, matAdr++, out_pMFAdr++)
		*out_pMFAdr = *matAdr;

	return ;
}

// 掛け算
void GglMatrix4x4_MulF(double* out_pMFAdr, const double* in_pMFAdr1, const double* in_pMFAdr2)
{
	GglMatrix4x4	mat;
	double*	w1;
	double*	w2;
	double*	pO = &mat._11;

	GglByte	i,j,k;
	double	f = 0;

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			w1 = in_pMFAdr1 + (sizeof(double*) * i);
			w2 = in_pMFAdr2 + j;

			for(k=0; k<4; k++){
				f += (*w1 * *w2);
				w1++;
				w2 += sizeof(double*);
			}

			*pO = f;
			pO++;
			f = 0;
		}
	}

	for(i=0, pO = &mat._11; i<16; i++, pO++, out_pMFAdr++)
		*out_pMFAdr = *pO;

	return ;
}

/*****************************************************************
 * GglMatrix4x4_DotScalar関数
 * 行列のスカラー倍の結果を行列で出力します
 *
 * 戻り値：なし
 * 引数：
 * 1.GglMatrix4x4* out_pMat			演算結果を格納
 * 2.const GglMatrix4x4* in_pMat	演算する行列
 * 3.const double in_scalar			スカラー値
*/
void GglMatrix4x4_DotScalar(GglMatrix4x4* out_pMat, const GglMatrix4x4* in_pMat, const double in_scalar)
{
	GglByte i;
	GglMatrix4x4 mat;
	double* j = &mat._11;

	for(i=0; i<16; i++)
		*j = (in_pMat->_11 + i) * in_scalar;

	*out_pMat = mat;
	return ;
}

/**************************************************************
 * GglMatrix4x4_DotVector関数
 * 行列とベクトルの演算を行います
 *
 * 戻り値：なし
 * 引数：
 * 1.GglMatrix4x4* out_pMat			演算結果を格納
 * 2.const GglMatrix4x4* in_pMat	演算対象の行列
 * 3.const GglVector3f* in_pVec		演算対象のベクトル
*/
void GglMatrix4x4_DotVector(GglVector3f* out_pVec, const GglMatrix4x4* in_pMat, const GglVector3f* in_pVec)
{
	GglVector3f	vec = GglVector3_SetInitializeEqual();
	GglByte	i,j;
	double*	pO = (double*)&vec.x;
	double*	pV = (double*)&in_pVec->x;
	double*	pM = &in_pMat->_11;

	for(i=0; i<3; i++){
		for(j=0; j<4; j++){
			if(j%4 != 0)
				*pO += (*pV) * (*pM);
			pM++;
		}

		pV++;
		pO++;
	}

	*out_pVec = vec;
	return ;
}

/*****************************************************
 * GglWorldMatrixLoadIdentity関数
 * 対象の行列を初期化（単位行列上書き）
 *
 * 戻り値、引数：なし
*/
void GglMatrix4x4_SetIdentity(GglMatrix4x4* out_pMat)
{
	//out_pMat->_11 = 1.0;
	//out_pMat->_12 = 0.0;
	//out_pMat->_13 = 0.0;
	//out_pMat->_14 = 0.0;

	//out_pMat->_21 = 0.0;
	//out_pMat->_22 = 1.0;
	//out_pMat->_23 = 0.0;
	//out_pMat->_24 = 0.0;

	//out_pMat->_31 = 0.0;
	//out_pMat->_32 = 0.0;
	//out_pMat->_33 = 1.0;
	//out_pMat->_34 = 0.0;

	//out_pMat->_41 = 0.0;
	//out_pMat->_42 = 0.0;
	//out_pMat->_43 = 0.0;
	//out_pMat->_44 = 1.0;

	double* pM = &out_pMat->_11;
	GglByte i;

	for(i=0; i<16; i++,pM++)
		if(i%5 == 0)
			*pM = 1.0f;
		else
			*pM = 0.0f;

	return ;
}

/***********************************************************
 * GglGetRotatePitchMatrix	関数
 * GglGetRotateYawMatrix	関数
 * GglGetRotateRollMatrix	関数
 * 引数に対してそれぞれ、X軸、Y軸、Z軸回転行列を返します
 *
 * 戻り値：	Matrix4x4			回転行列を返します
 * 引数：	const double in_rad	回転させたいラジアン角
*/
// X軸
GglMatrix4x4 GglMatrix4x4_GetRotatePitch(const double in_rad)
{
	GglMatrix4x4 m;
	GglMatrix4x4_SetIdentity(&m);

	m._22 = cos(in_rad);
	m._23 = sin(in_rad);
	m._32 = -sin(in_rad);
	m._33 = cos(in_rad);

	return m;
}

// Y軸
GglMatrix4x4 GglMatrix4x4_GetRotateYaw(const double in_rad)
{
	GglMatrix4x4 m;
	GglMatrix4x4_SetIdentity(&m);

	m._11 = cos(in_rad);
	m._13 = -sin(in_rad);
	m._31 = sin(in_rad);
	m._33 = cos(in_rad);

	return m;
}

// Z軸
GglMatrix4x4 GglMatrix4x4_GetRotateRoll(const double in_rad)
{
	GglMatrix4x4 m;
	GglMatrix4x4_SetIdentity(&m);

	m._11 = cos(in_rad);
	m._12 = sin(in_rad);
	m._21 = -sin(in_rad);
	m._22 = cos(in_rad);

	return m;
}

/**************************************************
 * GglGetScaleMatrix関数
 * 現在の座標とスケール倍率から拡縮行列を取得します
 *
 * 戻り値：GglMatrix4x4	拡大縮小後の行列を返す
 * 引数：
 * 1.const GglVector3f* in_pV		座標
 * 2.const double	in_scale	拡大縮小倍率
*/
GglMatrix4x4 GglMatrix4x4_GetScale(const GglVector3d* in_pV)
{
	GglMatrix4x4 m = {	in_pV->x,	0.0,					0.0,					0.0,
						0.0,					in_pV->y,	0.0,					0.0,
						0.0,					0.0,					in_pV->z,	0.0,
						0.0,					0.0,					0.0,					1.0
	};

	return m;
}

/**************************************************************
 * GglGetTranslationMatrix関数
 * ベクトルから平行移動行列を取得します
 *
 * 戻り値：	GglMatrix4x4					平行移動後の行列を返す
 * 引数：	const GglVector3f* in_pV	指定されたベクトル
*/
GglMatrix4x4 GglMatrix4x4_GetTranslation(const GglVector3d* in_pV)
{
	GglMatrix4x4 m;
	GglMatrix4x4_SetIdentity(&m);

	m._41 = in_pV->x;
	m._42 = in_pV->y;
	m._43 = in_pV->z;

	return m;
}