#ifndef Vector2f_h__
#define Vector2f_h__

/**
 * GglVector2f共用体
 * ベクトルを表す共用体
 * 配列を使えるようにするために共用体を使用
 */
union GglVector2f
{
	struct
	{
		float x;	// X座標
		float y;	// Y座標
	};

	float array[2];	// 配列([0] = x, [1] = y)

}typedef GglVector2f;

#endif