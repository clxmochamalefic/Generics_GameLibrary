#include "Generic_GameLibrary.h"

/**********************************************************
 * FpsInitialize関数
 * FPS計測システムを初期化します
 *
 * 戻り値：なし
 * 引数：
 * 1.const FpsCountMode in_countMode	Fps計測モードの設定
*/
void GglFps_Initialize(const GglClock in_countMode)
{
	g_fps.countMode		= in_countMode;	//引数で渡されたFPS値にて初期化
	g_fps.leaveTime		= clock();		//現在時刻にて初期化
	g_fps.secondTime	= clock();		//現在時刻にて初期化
	g_fps.nowCount		= 0;			//ゼロ初期化
	g_fps.secondCount	= 0;			//ゼロ初期化

	return ;
}

/**********************************************************
 * FpsUpdate関数
 * FPSの計測を更新します
 * 更新できる場合はタスクの実行も行えるよう、GglTrueを返します
 *
 * 戻り値：GglBoolean型、GglTrueかGglFalseを返す
 * 引数：なし
*/
GglBoolean GglFps_Update(void)
{
	GglClock t = clock();

	// 実行できるかどうかを比較する。不可の場合return GglFalse;
	if( clock() - g_fps.leaveTime > g_fps.countMode)
	{
		g_fps.leaveTime = clock();						//現在時間を前回時間として保存
		g_fps.nowCount++;								//FPSをカウント

		if(g_fps.leaveTime >= g_fps.secondTime + 1000)	//基準の1秒が経っていた場合
			GglFps_OneSecond();								//1秒経ったときの処理へ移動

		return GglTrue;
	}
	
	return GglFalse;
}

/************************************************************
 * FpsOneSecond関数
 * FPSの1秒間カウントを更新します
 *
 * 戻り値、引数：なし
*/
void GglFps_OneSecond(void)
{
	g_fps.secondTime	= g_fps.leaveTime;
	g_fps.secondCount	= g_fps.nowCount;
	g_fps.nowCount		= 0;

//	GglFps_ConsoleDraw();
	return ;
}

/************************************************************
 * FpsDraw関数
 * 現在のFPSカウントをコンソールに表示します
 * 
 * 戻り値、引数：なし
*/
void GglFps_ConsoleDraw(void)
{
	printf("FPS = %d\n", g_fps.secondCount);
	printf("NowRegistTask = %d\n", g_linkList.count);
	return;
}