#ifndef Vector2i_h__
#define Vector2i_h__

/****
 * GglVector2i共用体
 * ベクトルを表す共用体
 * 配列としても扱えるように共用体を使用
 */
union GglVector2i
{
	struct
	{
		int x;		// X座標
		int y;		// Y座標
	};

	int array[2];	// 配列([0] = x, [1] = y)

}typedef GglVector2i;

#endif