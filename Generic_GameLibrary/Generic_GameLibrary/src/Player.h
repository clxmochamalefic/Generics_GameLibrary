#ifndef PLAYER_H
#define PLAYER_H

#include "..\\Generic_GameLibrary.h"

struct Player
{
	GglVector3d		m_vMove;
	GglVector3d		m_vPos;
	GglVector3i		m_vRot;
	GglVector3d		m_vScale;
	GglVector3d		m_vPos2d;

	unsigned int	m_Life;
	GglModel*		m_model;
	GglModel*		m_planeMod;
	GglImage*		m_image;

}typedef Player;

void Player_Constractor(void);
void Player_Update(GglLink* _this, GglObject _obj);
void Player_Draw(GglObject* _obj);

#endif