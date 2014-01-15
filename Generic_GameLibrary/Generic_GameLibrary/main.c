#include "Generic_GameLibrary.h"
#include "src\\Player.h"
#include <stdlib.h>

#define GGL_USE_DEBUG
//struct A
//{
//	GglVector3f vec;
//
//}typedef A;
//
//void A_Update(GglLink* _this, GglObject _obj)
//{
//	A* self = (A*)_obj;
//	GglInputDevice_GetKeyboardState();
//
//	if(GglInputDevice_KeyDown(GIK_RIGHT))
//	{
//		self->vec.x+=0.1;
//	}
//	if(GglInputDevice_KeyDown(GIK_LEFT))
//	{
//		self->vec.x-=0.1;
//	}
//	if(GglInputDevice_KeyDown(GIK_UP))
//	{
//		self->vec.y-=0.1;
//	}
//	if(GglInputDevice_KeyDown(GIK_DOWN))
//	{
//		self->vec.y+=0.1;
//	}
//}
//
//void A_Draw(GglObject _obj)
//{
//	A* _this = _obj;
//	GglRectangle r = GglRectangle_AssembleElements(0,32,0,32);
//	
//	GglGraphic2d_DrawSprite(g_imageArray, &r, &_this->vec, NULL);
//}


void ThreadA(void* _arg)
{
	printf("GglThread A entered and will close.\n");
}

void ThreadB(void* _arg)
{
	while(1)
	{
		printf("GglThread B Updateing...\n");
	}
}

void GameInitialize(void)
{
	//GglMultiThread_Initialize();
	//GglMultiThread_AddNewThread(ThreadA, 0, NULL);
	//GglMultiThread_AddNewThread(ThreadB, 0, NULL);
	
	//GglModel* mod = NULL;
	//GglLink* l = (GglLink*)malloc(sizeof(GglLink));
	//A* a = (A*)malloc(sizeof(A));
	//
	//l->Update = A_Update;
	//l->Draw = A_Draw;
	//l->object = a;

	//GglModel_LoadModel("res\\cube.mqo", mod);
	//
	//a->vec = GglVector3f_Set(0.0, 0.0, 0.0);
	//
	//g_imageArray = (A*)malloc(sizeof(GglImage));
	//
	//GglImage_RegistImage(g_imageArray, "a.png");
	//
	//GglLinkList_AddElement(l);

	Player_Constractor();
	
	return ;
}

int main(void)
{
	GglSystem_Initialize(NULL, GameInitialize);
	return 0;
}