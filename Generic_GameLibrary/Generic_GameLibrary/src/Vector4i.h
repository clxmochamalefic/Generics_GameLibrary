#ifndef Vector4i_h__
#define Vector4i_h__

/**
 * GglVector4i共用体
 * ベクトルを表す共用体
 * 配列を使えるようにするために共用体を使用
 */
union GglVector4i
{
	struct
	{
		int x;		// x座標
		int y;		// y座標
		int z;		// z座標
		int q;		// クオータニオン等
	};

	int array[4];	// 配列([0] = x, [1] = y, [2] = z, [3] = q)

}typedef GglVector4i;

#endif