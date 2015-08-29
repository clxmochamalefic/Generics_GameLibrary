#ifndef GglRectangle_h__
#define GglRectangle_h__

/**
 * GglRectangle構造体
 * 矩形を表す構造体
 */
union GglRectangle
{
	struct
	{
		int t;		// top		上
		int l;		// left		左
		int b;		// bottom	下
		int r;		// right	右
	};

	int array[4];	// 配列([0] = top, [1] = left, [2] = bottom, [3] = right)

}typedef GglRectangle;

#endif