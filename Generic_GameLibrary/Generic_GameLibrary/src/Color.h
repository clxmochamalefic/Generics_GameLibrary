#ifndef GglColor4_h__
#define GglColor4_h__

/**
 * GglColor4共用体
 * 色情報を32bitカラーで纏められている
 */
union GglColor4
{
	struct
	{
		float r;	// Red
		float g;	// Green
		float b;	// Blue
		float a;	// Alpha
	};

	float array[4];	// 配列([0] = red, [1] = green, [2] = blue, [3] = alpha)

}typedef GglColor4;

#endif