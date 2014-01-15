#include "Player.h"
#include "..\\Generic_GameLibrary.h"

void Player_Constractor(void)
{
	Player* player;
	GglLink* link;

	link = (GglLink*)GglMemory_New(sizeof(GglLink));
	player = (Player*)GglMemory_New(sizeof(Player));

	player->m_model		= GglModel_LoadModel("Debug\\cube2.x", NULL);
	player->m_planeMod	= GglModel_LoadModel("Debug\\hikouki_tes01.x", NULL);
	player->m_image		= GglImage_LoadPng(NULL, "c.png");
	player->m_Life		= 10;

	GglVector3_SetInitialize(player->m_vMove);
	GglVector3_SetInitialize(player->m_vPos);
	GglVector3_SetInitialize(player->m_vPos2d);
	GglVector3_SetInitialize(player->m_vRot);
	GglVector3_Set(player->m_vScale, 5.0, 5.0, 5.0);

	link->object	= player;
	link->Update	= Player_Update;
	link->Draw		= Player_Draw;
	link->name		= GglString_MakeString("Player", 7);

	GglLinkList_AddElement(link);
}

void Player_Update(GglLink* _this, GglObject _obj)
{
	Player* player = (Player*)_obj;
	player->m_Life++;

	GglInputDevice_GetKeyboardState();

	// •½sˆÚ“®
	if(GglInputDevice_KeyDown(GIK_S))
	{
		player->m_vPos.z+=0.1f;
		player->m_vPos2d.y++;
	}
	if(GglInputDevice_KeyDown(GIK_W))
	{
		player->m_vPos.z-=0.1f;
		player->m_vPos2d.y--;
	}
	if(GglInputDevice_KeyDown(GIK_A))
	{
		player->m_vPos.x-=0.1f;
		player->m_vPos2d.x--;
	}
	if(GglInputDevice_KeyDown(GIK_D))
	{
		player->m_vPos.x+=0.1f;
		player->m_vPos2d.x++;
	}
	if(GglInputDevice_KeyDown(GIK_Q))
	{
		player->m_vPos.y-=0.1f;
	}
	if(GglInputDevice_KeyDown(GIK_E))
	{
		player->m_vPos.y+=0.1f;
	}

	// ‰ñ“]
	if(GglInputDevice_KeyDown(GIK_J))
	{
		player->m_vRot.x--;
	}
	if(GglInputDevice_KeyDown(GIK_L))
	{
		player->m_vRot.x++;
	}
	if(GglInputDevice_KeyDown(GIK_I))
	{
		player->m_vRot.y--;
	}
	if(GglInputDevice_KeyDown(GIK_K))
	{
		player->m_vRot.y++;
	}
	if(GglInputDevice_KeyDown(GIK_U))
	{
		player->m_vRot.z--;
	}
	if(GglInputDevice_KeyDown(GIK_O))
	{
		player->m_vRot.z++;
	}

	// Šgk
	if(GglInputDevice_KeyDown(GIK_Z))
	{
		player->m_vScale.x-=0.1;
	}
	if(GglInputDevice_KeyDown(GIK_X))
	{
		player->m_vScale.x+=0.1;
	}
	if(GglInputDevice_KeyDown(GIK_C))
	{
		player->m_vScale.y-=0.1;
	}
	if(GglInputDevice_KeyDown(GIK_V))
	{
		player->m_vScale.y+=0.1;
	}
	if(GglInputDevice_KeyDown(GIK_B))
	{
		player->m_vScale.z-=0.1;
	}
	if(GglInputDevice_KeyDown(GIK_N))
	{
		player->m_vScale.z+=0.1;
	}

	// ‰ñ“]Šp“x’²®
	if(!(player->m_vRot.x % 360))
	{
		player->m_vRot.x = 0;
	}
	if(player->m_vRot.x < 0)
	{
		player->m_vRot.x += 360;
	}
	if(!(player->m_vRot.y % 360))
	{
		player->m_vRot.y = 0;
	}
	if(player->m_vRot.y < 0)
	{
		player->m_vRot.y += 360;
	}
	if(!(player->m_vRot.z % 360))
	{
		player->m_vRot.z = 0;
	}
	if(player->m_vRot.z < 0)
	{
		player->m_vRot.z += 360;
	}

	player->m_vPos2d.x+=2;

	//glMatrixMode(GL_PROJECTION);
	//gluLookAt(player->m_vPos.x, player->m_vPos.y, player->m_vPos.z, player->m_vPos.x, player->m_vPos.y-1.0, player->m_vPos.z, 0, 1, 0);
	//gluLookAt(player->m_vPos.x, player->m_vPos.y, player->m_vPos.z, player->m_vPos.x, player->m_vPos.y-1.0, player->m_vPos.z, 0, 1, 0);
}

void Player_Draw(GglObject* _obj)
{
	Player* player		= (Player*)_obj;
	GglVector3d rot		= GglVector3_SetEqual(GGL_TORAD(player->m_vRot.x), GGL_TORAD(player->m_vRot.y), GGL_TORAD(player->m_vRot.z));
	GglVector3d vec		= GglVector3_SetEqual(1.0, 1.0, 1.0);
	GglRectangle rect	= GglRectangle_Initialize(0,0,2,2);
	GglVector3f drawpos	= GglVector3_SetInitializeEqual();
	
	//glEnable(GL_BLEND);
	//
	//glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	//GglGraphic3d_Render(player->m_planeMod, &player->m_vPos, &rot, &player->m_vScale);

	//glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	//GglGraphic3d_Render(player->m_model, &vec, NULL, NULL);

	//glDisable(GL_BLEND);

	GglGraphic2d_DrawSprite(player->m_image, &player->m_image->size ,&rect, &player->m_vPos2d, NULL);

	return ;
}