#include "Generic_GameLibrary.h"
#include "png.h"
#include <cv.h>
#include <highgui.h>
#pragma warning(disable:4996)
//
///***************************************************************************
// * GglImage_AssembleElements関数
// * uintの画像情報とpngInfo情報をGglImage構造体に統一して出力します
// * 
// * 戻り値：画像イメージ出力
// * 引数：
// * 1.const unsigned int*	in_image	//GglImage型に突っ込みたいイメージ
// * 2.const pngInfo*			in_info		//GglImage型に突っ込みたいイメージ情報
// * 3.GglImage*					out_pImage	//イメージ出力
//*/
//GglImage GglImage_AssembleElements(unsigned int* in_pImage,
//								pngRawInfo* in_pInfo,
//								GglImage* out_pImage)
//{
//	GglImage img;
//	img.image	= *in_pImage;
//	img.info	= *in_pInfo;
//
//	if(out_pImage != NULL)
//		*out_pImage = img;
//
//	return img;
//}
//
///************************************************************************************
// * GglImage_RegistImage関数
// * g_imageArray動的配列にイメージ情報を挿入する
// * あるいは、GglImage型であればどんなものでも挿入することが可能である
// * 
// * 戻り値：GglBoolean(GglTrue = 1, GglFalse = 0、ユーザー設定)
// * 引数：
// * 1.GglImage* out_pImage	イメージ型へのポインタを指定、普通はg_imageArray配列を入れる
// * 2.GglString in_string	イメージ型へ挿入したいファイルの名前を相対パスで入れる
// * 
// ************************************************************************************
// * バージョン情報 *******************************************************************
// * @Ver.1.0.0.ALPHA
// * ☆第二引数 - GglString in_string
// *   は相対パスの対象フォルダをいちいち指定する必要がある
// *   は拡張子をいちいち指定する必要がある(扱えるのはpngのみ)
// * 改善予定は未定だが設計として見直す余地あり？
//*/
//GglBoolean GglImage_RegistImage(GglImage* out_pImage, GglString in_fileName)
//{
//	if(out_pImage == NULL)
//		return GglFalse;
//
//	//out_pImage->image = pngBind(in_fileName,
//	//							PNG_BUILDMIPMAP,
//	//							PNG_ALPHA,
//	//							&out_pImage->info,
//	//							GL_CLAMP,
//	//							GL_NEAREST,
//	//							GL_NEAREST);
//
//	return GglTrue;
//}

#ifndef PNG_STDIO_SUPPORTED

static void GglImage_PngReadData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	png_size_t check;

	/* fread() returns 0 on error, so it is OK to store this in a png_size_t
	* instead of an int, which is what fread() actually returns.
	*/
	check = (png_size_t)fread(data, (png_size_t)1, length, (FILE *)png_ptr->io_ptr);

	if (check != length)
	{
		png_error(png_ptr, "Read Error");
	}

	return ;
}

static void GglImage_PngWriteData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	png_uint_32 check;

	check = fwrite(data, 1, length, (FILE *)(png_ptr->io_ptr));
	if (check != length)
	{
		png_error(png_ptr, "Write Error");
	}

	return ;
}

static void GglImage_PngFlush(png_structp png_ptr)
{
	FILE *io_ptr;
	io_ptr = (FILE *)CVT_PTR((png_ptr->io_ptr));
	if (io_ptr != NULL)
	{
		fflush(io_ptr);
	}

	return ;
}

#endif

static void GglImage_LoadPngException(png_structp png_ptr, png_const_charp msg)
{
#ifdef PNG_CONSOLE_IO_SUPPORTED
	GglDebug_PrintExceptionLine();
#endif
}

/**
 * GglImage_LoadPng関数
 * PNGイメージを読み込む
 *
 * @param	読み込んだ画像 成功すれば動的メモリを入れる。失敗のときはNULL
 * @param	読み込んだファイルポインタ
 *
 * @return	関数の成功失敗
*/
GglImage* GglImage_LoadPng(GglImage* out_pImage, GglString in_fileName)
{
	FILE*			fp;
	png_structp		pPng;
	png_infop		pInfo;
	png_byte		pbSig[8];
	GglImage*		pImage;
	double			gamma;
	unsigned int	i=0, j=0;
	int				rb;
	GglUByte**		rows;
	int				imgid;
	png_bytep		test;
	png_color_16p	w;
	png_colorp		plte;
	int				pltemax;
	int				bgplte;

	// 引数チェック
	if(!in_fileName)
	{
		return NULL;
	}

	// 1. シグネチャ読み込み
	fp = fopen(in_fileName, GGL_FILE_READ_BINALY);
	
	if(fp == NULL)
	{
		return NULL;
	}

	fread(pbSig, 1, 8, fp);

	if(png_sig_cmp(pbSig, 0, 8))
	{
		out_pImage = NULL;
		return NULL;
	}

	// png構造体作成
	pPng = png_create_read_struct(	PNG_LIBPNG_VER_STRING,
									NULL,
									(png_error_ptr)GglImage_LoadPngException,
									(png_error_ptr)NULL);
	if(!pPng)
	{
		out_pImage = NULL;
		return NULL;
	}

	// info構造体作成
	pInfo = png_create_info_struct(pPng);
	if(!pInfo)
	{
		png_destroy_read_struct(&pPng, NULL, NULL);
		out_pImage = NULL;
		return NULL;
	}

	pImage = (GglImage*)GglMemory_New(sizeof(GglImage));
	pImage->id = 0;

	// 3. ファイルポインタのセット	
	png_init_io(pPng, fp);

	png_set_sig_bytes(pPng, 8);

	// 5. データ読み込み
	// PNGイメージからinfoデータ読み込み
	png_read_info(pPng, pInfo);

	// 画像から幅と高さ情報を取得
	png_get_IHDR(pPng, pInfo, &pImage->size.x, &pImage->size.y, &pImage->depth, &pImage->colorType, NULL, NULL, NULL);

	if(pImage->depth < 8)
	{
		png_set_expand(pPng);
	}

	if(pImage->depth == 16)
	{
		png_set_strip_16(pPng);
	}
	
	// カラータイプ
	switch(pImage->colorType)
	{
		case PNG_COLOR_TYPE_GRAY:
			png_set_gray_to_rgb(pPng);
			break;

		case PNG_COLOR_TYPE_GRAY_ALPHA:
			png_set_gray_to_rgb(pPng);
			png_set_tRNS_to_alpha(pPng);
			break;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			if(png_get_valid(pPng, pInfo, PNG_INFO_tRNS))
			{
				png_get_tRNS(pPng, pInfo, &test, &i, &w);
			}
			else if(png_get_valid(pPng, pInfo, PNG_INFO_bKGD))
			{
				png_get_bKGD(pPng, pInfo, &w);
			}
			break;

		case PNG_COLOR_TYPE_PALETTE:
			
			if(png_get_valid(pPng, pInfo, PNG_INFO_tRNS))
			{
				png_get_tRNS(pPng, pInfo, &test, &bgplte, &w);
				png_get_PLTE(pPng, pInfo, &plte, &pltemax);
				png_set_palette_to_rgb(pPng);
				png_set_add_alpha(pPng, 0xff, PNG_FILLER_AFTER);
			}
			else if(png_get_valid(pPng, pInfo, PNG_INFO_bKGD))
			{
				png_get_bKGD(pPng, pInfo, &w);
				png_set_palette_to_rgb(pPng);
				png_set_add_alpha(pPng, 0xff, PNG_FILLER_AFTER);
			}
			break;

		default:
			break;
	}

	if(png_get_gAMA(pPng, pInfo, &gamma))
	{
		png_set_gamma(pPng, (double)2.2, gamma);
	}

	png_read_update_info(pPng, pInfo);

	pImage->channles		= png_get_channels(pPng, pInfo);

	// 画像幅と高さの2次元配列を作成
	rb		= png_get_rowbytes(pPng, pInfo);
	pImage->rows	= (GglUByte*)GglMemory_New(sizeof(GglUByte*) * pImage->size.y * rb);
	
	for(i=0; i<pImage->size.y; i++)
	{
		png_read_row(pPng, pImage->rows + i*rb, NULL);
	}

	for(i=0; i<pImage->size.y; i++)
	{
		printf("\n");
		for(j=0; j<rb; j++)
		{
			printf("%x",pImage->rows[i*rb+j]);
			printf(j%4 == 3 ? "; " : ", ");
		}
	}

	if(pImage->colorType == PNG_COLOR_TYPE_PALETTE)
	{
		for(i=0; i<pImage->size.x * pImage->size.y; i++)
		{
			if(	pImage->rows[i*4]	== w->red &&
				pImage->rows[i*4+1] == w->green &&
				pImage->rows[i*4+2] == w->blue)
			{
				pImage->rows[i*4+3] = 0x00;
			}
			else
			{
				pImage->rows[i*4+3] = 0xff;
			}
		}
	}

	if(out_pImage)
	{
		out_pImage = pImage;
	}

	png_destroy_read_struct(&pPng, &pInfo, NULL);
	fclose(fp);

	// テクスチャへの登録
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &imgid);
	glBindTexture(GL_TEXTURE_2D, imgid);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImage->size.x, pImage->size.y, GL_RGBA, GL_UNSIGNED_BYTE, pImage->rows);
	glDisable(GL_TEXTURE_2D);

	pImage->id = imgid++;

	return pImage;
}

//GglImage* GglImage_LoadPng(GglImage* out_pImage, GglString in_fileName)
//{
//	IplImage* cvimg = cvLoadImage(in_fileName, CV_LOAD_IMAGE_ANYCOLOR);
//
//	if(cvimg == NULL)
//	{
//		out_pImage = NULL;
//		return NULL;
//	}
//
//	img = GglMemory_New(sizeof(GglImage));
//
//	cvimg->
//
////	/* ウインドウを準備して画像を表示する */
////    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
////    cvShowImage("Image",img);
//
// //   /* キー入力があるまで待つ */
// //   cvWaitKey(0); /* これがないと、1瞬だけ表示されて終わる */
//	//cvReleaseImage(&img);
//
//	img->
//
//	return NULL;
//}