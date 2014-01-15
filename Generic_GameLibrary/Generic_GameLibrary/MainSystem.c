#include "Generic_GameLibrary.h"

/**********************************************************
 * Initalize関数
 * Cocoalix_Library_4GLで利用するサービスを初期化します
 *
 * 戻り値 :
 * なし
 *
 * 引数 :
 * 1. const GglSftring ic_windowName	タイトルバーに表示させるウィンドウ名 NULLでライブラリ名をタイトルバーに表示
 * 2. void (*GameInit)(void)			ゲーム初期化関数の関数ポインタ
*/
void GglSystem_Initialize(const GglString ic_windowName, void (*GameInit)(void))
{
	GglString	name;			// ウィンドウ名
	int			argc = 1;		// 引数

	// ウィンドウタイトルを代入
	if(ic_windowName == NULL)
	{
		 name = "Generic_GameLibrary_Ver.1.0.0.PrivateBeta";
	}
	else
	{
		name = ic_windowName;
	}

	printf("Startup ");
	printf("%s\n\n", name);
	
	glutInitWindowPosition(100, 200);							
	glutInitWindowSize(800, 600);
	glutInit(&argc,&name);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(name);

	if( glewInit() != GLEW_OK )
	{
		exit(0);
	}

	glutReshapeFunc(GglSystem_WindowResize);

	printf("Initialize Generic_GameLibrary");

	GglMemory_Initialize();
	printf(".");
	GglSystem_InitializeGlut();
	printf(".");
	GglSystem_InitializeSystem();
	printf(".");
	if(GameInit != NULL)
	{
		GameInit();
	}
	printf("Done.\n");
	
	// 3D垂直同期設定
	wglSwapIntervalEXT(0);
	
	glutIdleFunc(GglSystem_MainLoopDraw);
	glutDisplayFunc(GglSystem_MainLoopDraw);
	glutMouseFunc(GglInputDevice_Mouse);
	glutMainLoop();
	
	return ;
}


/***************************************************************************************
 * GglSystem_Shutdown関数
 * Generic_GameLibraryの終了処理です
 * 具体的には、Generic_GameLibraryが作成したリソースやロードしたファイルの開放を行います
 * 
 * 戻り値 : なし
 * 引数   : なし
*/
static void GglSystem_Shutdown(void)
{
	GglClock waitTime = clock();

	GglLinkList_Shutdown();
	GglNetworkList_Shutdown();
	GglNetwork_Shutdown();
	GglMultiThread_Shutdown();
	GglSystem_UnLoadContent();
	GglMemory_Shutdown();

	printf("システムは正常に終了しました。\n");

	for(;waitTime+500 > clock();){}

	printf("Good bye...\n");
	
	return ;

}

void GglSystem_MainLoopUpdate(void)
{
	GetKeyboardState(g_inputDevice.keyState);
	GglInputDevice_ShutDownKey();
	GglMemory_ReconnectList(NULL, NULL);

	if(g_multiThread.count > 1)
	{
		WaitForMultipleObjects(g_multiThread.count, g_multiThread.array, FALSE, INFINITE);
	}
	else if(g_multiThread.count == 1)
	{
		WaitForSingleObject(&g_multiThread.array, INFINITE);
	}
	
	glutPostRedisplay();
}

void GglSystem_MainLoopDraw(void)
{
	//GetKeyboardState(g_inputDevice.keyState);
	//GglInputDevice_ShutDownKey();
	//GglMemory_ReconnectList(NULL, NULL);

	////if(g_multiThread.count > 1)
	////{
	////	WaitForMultipleObjects(g_multiThread.count, g_multiThread.array, FALSE, INFINITE);
	////}
	////else if(g_multiThread.count == 1)
	////{
	////	WaitForSingleObject(&g_multiThread.array, INFINITE);
	////}

	//glClear(GL_COLOR_BUFFER_BIT);

	//if(GglFps_Update() == GglTrue)
	//{
	//	GglLinkList_Update();	
	//}

	//GglLinkList_Draw();

	//GglInputDevice_AllInitialize();
	//glutSwapBuffers();
	//glutPostRedisplay();


	GetKeyboardState((PBYTE)&g_inputDevice.keyState);
	GglInputDevice_ShutDownKey();
	GglMemory_ReconnectList(NULL, NULL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//if(g_thread.maxThread > 1)
	//{
	//	WaitForMultipleObjects(g_thread.maxThread, &g_thread.hArray, FALSE, INFINITE);
	//}
	//else if(g_thread.maxThread == 1)
	//{
	//	WaitForSingleObject(&g_thread.hArray, INFINITE);
	//}

	if(GglFps_Update() == GglTrue)
	{
		GglLinkList_Update();
	}

	GglLinkList_Draw();

	GglInputDevice_AllInitialize();
	
	glutSwapBuffers();
	glutPostRedisplay();

	return ;
}

void GglSystem_WindowResize(const int _w, const int _h)
{
	//glViewport(0,0,_w,_h);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(GglGraphic_PERS_FOVY, (double)GglGraphic_PERS_WIDTH / GglGraphic_PERS_HEIGHT, GglGraphic_PERS_ZNEAR, GglGraphic_PERS_ZFAR);

	//glMatrixMode(GL_MODELVIEW);
//	glOrtho(-_w / 200.0, _w / 200.0, -_h / 200.0, _h / 200.0, -1.0, 1.0);
//	GglGraphic_Ortho2d();



	// ウィンドウ全体をビューポートへ
	glViewport(0, 0, _w, _h);

	// 変換行列初期化
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// スクリーン上の表示領域をビューポートの大きさに比例させる
	//glOrtho(-_w / 200.0, _w / 200.0, -_h / 200.0, _h / 200.0, -1.0, 1.0);
	//gluPerspective(30.0, (double)_w / (double)_h, 1.0, 100.0);
	gluPerspective(GglGraphic_PERS_FOVY, (double)GglGraphic_PERS_WIDTH / GglGraphic_PERS_HEIGHT, GglGraphic_PERS_ZNEAR, GglGraphic_PERS_ZFAR);
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	return ;
}

/**********************************************************
 * GlInit関数
 * OpenGLで利用するサービスを初期化します
 *
 * 戻り値、引数：なし
*/
void GglSystem_InitializeGlut(void)
{
	glClearColor(0.8,0.8,0.8,0.0);

	glLoadIdentity();
	gluPerspective(GglGraphic_PERS_FOVY, (double)GglGraphic_PERS_WIDTH / GglGraphic_PERS_HEIGHT, GglGraphic_PERS_ZNEAR, GglGraphic_PERS_ZFAR);
	gluLookAt(0,0,0,0,0,0,0,1,0);

	/* アルファテストの比較関数 */
	glAlphaFunc(GL_GREATER, 0.5);

	/* アルファブレンド用 */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	return ;
}

/**********************************************************
 * GglSystemInit関数
 * Genelic_GameLibrary固有の利用するサービスを初期化します
 *
 * 戻り値、引数：なし
*/
static void GglSystem_InitializeSystem(void)
{
	// 終了時に行う処理を設定
	atexit(GglSystem_Shutdown);
	
	// LinkTaskシステムを開始
	GglLinkList_Initialize();

	GglFps_Initialize(GglFps_ONE_FRAME_FOR_SIXTY);

	g_multiThread.useMultiThreadFlag	= GglFalse;
	g_networkList.useNetworkFlag		= GglFalse;

	return ;
}

static void GglSystem_UnLoadContent(void)
{
	//if(g_imageArray != NULL)
	//{
	//	GglMemory_Delete(g_imageArray);
	//	g_imageArray = NULL;
	//}

	return ;
}