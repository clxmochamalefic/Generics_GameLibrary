#include "Generic_GameLibrary.h"
#include <math.h>

/************************************************************
 * GglHit_Circle関数
 * 3D円形の当たり判定を行います
 *
 * 戻り値：GglBoolean		GglTrue = HIT, GglFalse = NOT HIT
 * 引数：
 * 1.const GglVector3f* in_v1	物体1の位置ベクトル
 * 2.const float in_r1	物体1の当たり判定を取る半径
 * 3.const GglVector3f* in_v2	物体2の位置ベクトル
 * 4.const float in_r2	物体2の当たり判定を取る半径
*/
GglBoolean GglHit_CircleHit(GglVector3f* in_pV1, const float in_r1,
							GglVector3f* in_pV2, const float in_r2)
{
	GglVector3f vec		= GglVector3_SubEqual(*in_pV1, *in_pV2);
	float	length		= GglVector3_GetLength(vec);

	if(length <= -1)
	{
		length *= -1;
	}

	if( ( length - (in_r1 + in_r2) ) <= 0 )
	{
		return GglTrue;
	}

	return GglFalse;
}


/*****************************************************************************
 * GglHit_RectangleHit関数
 * 矩形当たり判定を行います
 * 当たっている状態が関数により確認されている場合、GglTrueを、
 * そうでない場合はGglFalseを返します
 *
 * 戻り値：GglBoolean(boolと等価)
 * 引数 :
 * 1. GglVector3f*		_v1		比較対照1の位置ベクトル
 * 2. GglRectangle	_r1		比較対照1の矩形サイズ
 * 3. GglVector3f*	_v1		比較対照2の位置ベクトル
 * 4. GglRectangle	_r1		比較対照2の矩形サイズ
*/
GglBoolean GglHit_RectangleHit(GglVector3f* _v1, GglRectangle _r1,
							   GglVector3f* _v2, GglRectangle _r2)
{
	if(  ( (_v1->x + _r1.r) >= (_v2->x + _r2.l) )    &&    ( (_v1->x + _r1.l) <= (_v2->x + _r2.l) )  )
	{
		if(  ( (_v1->y + _r1.b) >= (_v2->y + _r2.t) )    &&    ( (_v1->y + _r1.t) <= (_v2->y + _r2.t) )  )
		{
			return GglTrue;
		}
		else if(  ( (_v1->y + _r1.b) >= (_v2->y + _r2.b) )    &&    ( (_v1->y + _r1.t) <= (_v2->y + _r2.b) )  )
		{
			return GglTrue;
		}
	}
	else if(  ( (_v1->x + _r1.r) >= (_v2->x + _r2.r) )    &&    ( (_v1->x + _r1.l) <= (_v2->x + _r2.r) )  )
	{
		if(  ( (_v1->y + _r1.b) >= (_v2->y + _r2.t) )    &&    ( (_v1->y + _r1.t) <= (_v2->y + _r2.t) )  )
		{
			return GglTrue;
		}
		else if(  ( (_v1->y + _r1.b) >= (_v2->y + _r2.b) )    &&    ( (_v1->y + _r1.t) <= (_v2->y + _r2.b) )  )
		{
			return GglTrue;
		}
	}

	return GglFalse;
}

/***********************************************************
 * GglHit_CircleGetIncidence関数
 * 3D円形当たり判定において、位置Aの物体が
 * 位置Bにある物体に進入する時、
 * 位置Bの反射ベクトルと
 * 位置Aの反射ベクトルを算出します
 *
 * 戻り値：なし
 * 引数：
 * const GglVector3f* in_pPosA	物体Aの位置ベクトル
 * const GglVector3f* in_pPosB	物体Bの位置ベクトル
 * const GglVector3f* in_pVecA	物体Aの移動方向ベクトル
 * GglVector3f* out_pVA		物体Aの反射ベクトル
 * GglVector3f* out_pVA		物体Bの反射ベクトル
*/
void GglHit_CircleGetIncidenceReflex(GglVector3f* in_pPosA,
									 GglVector3f* in_pPosB,
									 GglVector3f* in_pVecA,
									 GglVector3f* out_pVA,
									 GglVector3f* out_pVB)
{
	GglVector3f vABsub		= GglVector3_SubEqual(*in_pPosA, *in_pPosB);		// vAとvBの差分ベクトル
	GglVector3f vABsubNormal;												// vA-vB Normalize
	GglVector3f vecANormal;													// in_pVecA Normalize
	GglVector3f vecAnDotvABsubNnormal;										// vVecAnDotvABsubNormal Normalize
	GglVector3f	subed;
	
	float	vVecAnDotvABsubN;											// vecANormal DOT vABsubNoraml
	float	vABdot		= (float)GglVector3_Dot(*in_pPosA, *in_pPosB);	// vAとvBの内積
	float	vAvecLength	= (float)GglVector3_GetLength(*in_pVecA);		// vAの移動方向ベクトルの大きさ

	// Normalize
	GglVector3_Normalize(vABsub, vABsub);
	GglVector3_Normalize(*in_pVecA, *in_pVecA);

	vVecAnDotvABsubN = (float)GglVector3_Dot(vecANormal, vABsubNormal);
	GglVector3_MulScalar(vABsubNormal, vecAnDotvABsubNnormal, 2.0 * vVecAnDotvABsubN);

	GglVector3_MulScalar(vABsubNormal, *out_pVB, vABdot * vAvecLength);

	//vector - float * vector
	//vector - (float * vector)
	//vector - vector
	//D3DXVector3Normalize(out,
	//	&(vVec - 2.0f * D3DXVector3Dot(&vNormal, &vVecNormalize) * vVecNormalize));

	// 物体Aが受ける反射ベクトルを代入
	GglVector3_Sub(subed, vABsub, vecAnDotvABsubNnormal);
	GglVector3_Normalize(subed, *out_pVB);

	return ;
}