#ifndef GglImage_h__
#define GglImage_h__

#include "Definition.h"
#include "Vector2.h"
#include "Color.h"

/**
 * GglImage構造体
 * png画像やRAWなど、イメージ情報を扱う
 */
struct GglImage
{
	// ピクセル毎の色情報
	GglUByte*			rows;		// 画像情報

	// 画像の大きさ
	union
	{
		GglVector2i		size;
		unsigned int	array[2];
	};

	// チャンネル数(グレースケール、RGB、RGBA、etc...
	char				depth;		// 色深度
	char				colorType;	// 画像のカラータイプ(グレースケール、パレット、etc...
	char				channles;	// カラーチャンネル

	// パレット画像の場合、パレット情報、バックグラウンドカラー、パレット数を持つ
	size_t				maxPalette;			// パレットの最大数
	GglColor4*			palette;			// パレットの内容
	GglColor4			backgroundColor;	// パレットのバックグラウンドカラー

	// OpenGLに登録されたテクスチャID
	int					id;

}typedef GglImage;

#endif