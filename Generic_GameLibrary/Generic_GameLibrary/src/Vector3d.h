#ifndef Vector3d_h__
#define Vector3d_h__

#define GglVector3d_Normal3(x, y, z)	GglVector3d_Set(x, y, z)	// 関数別名(Vector3d.h)

/**
 * GglVector3d共用体
 * ベクトルを表す共用体
 * typedefによって法線情報も表す
 * 配列を使えるようにするために共用体を使用
 */
union GglVector3d
{
	struct
	{
		double x;		// x座標
		double y;		// y座標
		double z;		// z座標
	};

	double array[3];	// 配列([0] = x, [1] = y, [2] = z)

}typedef GglVector3d, GglNormal3d;


#endif