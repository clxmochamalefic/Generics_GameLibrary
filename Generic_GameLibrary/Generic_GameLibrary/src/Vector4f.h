#ifndef Vector4f_h__
#define Vector4f_h__

/**
 * GglVector4f共用体
 * ベクトルを表す共用体
 * 配列を使えるようにするために共用体を使用
 */
union GglVector4f
{
	struct
	{
		float x;	// x座標
		float y;	// y座標
		float z;	// z座標
		float q;	// クオータニオン等
	};

	float array[4];	// 配列([0] = x, [1] = y, [2] = z, [3] = q)

}typedef GglVector4f;

#endif