#ifndef Vector4d_h__
#define Vector4d_h__

/**
 * GglVector4d共用体
 * ベクトルを表す共用体
 * 配列を使えるようにするために共用体を使用
 */
union GglVector4d
{
	struct
	{
		double x;		// x座標
		double y;		// y座標
		double z;		// z座標
		double q;		// クオータニオン等

	};

	double array[4];	// 配列([0] = x, [1] = y, [2] = z, [3] = q)

}typedef GglVector4d;

#endif