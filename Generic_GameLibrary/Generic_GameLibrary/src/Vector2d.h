#ifndef Vector2d_h__
#define Vector2d_h__

/**
 * GglVector2d共用体
 * ベクトルを表す共用体
 * 配列を使えるようにするために共用体を使用
 */
union GglVector2d
{
	struct
	{
		double x;			// X座標
		double y;			// Y座標
	};

	double array[2];		// 配列([0] = x, [1] = y)

}typedef GglVector2d;

#endif