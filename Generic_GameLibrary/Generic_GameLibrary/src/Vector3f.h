#ifndef Vector3f_h__
#define Vector3f_h__

#define GglVector3f_Normal3(x, y, z)	GglVector3f_Set(x, y, z)	// 関数別名(GglVector3f.h)

/**
 * GglVector3f共用体
 * ベクトルを表す共用体
 * typedefによって法線情報も表す
 * 配列を使えるようにするために共用体を使用
 */
union GglVector3f
{
	struct
	{
		float x;	// x座標
		float y;	// y座標
		float z;	// z座標
	};

	float array[3];	// 配列([0] = x, [1] = y, [2] = z)

}typedef GglVector3f, GglNormal3f;

#endif