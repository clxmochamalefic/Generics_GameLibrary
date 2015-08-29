#ifndef Vector3i_h__
#define Vector3i_h__

/**
 * GglVector3i共用体
 * ベクトルを表す共用体
 * typedefによって法線情報も表す
 * 配列を使えるようにするために共用体を使用
 */
union GglVector3i
{
	struct
	{
		int x;		// x座標
		int y;		// y座標
		int z;		// z座標
	};

	int array[3];	// 配列([0] = x, [1] = y, [2] = z)

}typedef GglVector3i, GglNormal3i;

#endif