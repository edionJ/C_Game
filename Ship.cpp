#include "Ship.h"

extern IMAGE boom1, boom2, boom3, boom4;
extern IMAGE smallboom1, smallboom2, smallboom3, smallboom4;
extern IMAGE background, ship, ship1, enemy, enemy1, smallenemy, smallenemy1;

Ship::Ship(int nRow, int nCol, int nLife)
{
	m_nRow = nRow;
	m_nCol = nCol;
	m_nLife = nLife;
}

Ship::~Ship()
{

}

void Ship::ShowClear()				// ÑÚ¸Ç·É´¬
{
	putimage(m_nRow, m_nCol, &ship1, SRCAND);
}

void Ship::ShowClearLife()			// ÑÚ¸Ç·É´¬ÑªÁ¿
{
	setfillcolor(BLACK);
	fillrectangle(GAMEWIDTH / 2 - 50, GAMEHIGHT - 10, GAMEWIDTH / 2 - 50 + m_nLife, GAMEHIGHT - 5);
}

void Ship::ShowLife()				// ÏÔÊ¾·É´¬ÑªÁ¿
{
	setfillcolor(BLUE);
	fillrectangle(GAMEWIDTH / 2 - 50, GAMEHIGHT - 10, GAMEWIDTH / 2 - 50 + m_nLife, GAMEHIGHT - 5);
}

void Ship::GetHit()				// ·É´¬ÊÜµ½ÉËº¦
{
	if (m_nLife > 0)
	{
		m_nLife -= 25;
	}
}

void Ship::Show()					// ÏÔÊ¾·É´¬
{
	putimage(m_nRow, m_nCol, &ship, SRCPAINT);
}

void Ship::ShowBoom()				// ÏÔÊ¾±¬Õ¨
{
	if (m_Boom >= 1 && m_Boom <= 3)
	{
		putimage(m_nRow, m_nCol, ship.getwidth(),
			ship.getheight(), &smallboom1, 0, 0);
	}

	if (m_Boom >= 4 && m_Boom <= 6)
	{
		putimage(m_nRow, m_nCol, ship.getwidth(),
			ship.getheight(), &smallboom2, 0, 0);
	}

	if (m_Boom >= 7 && m_Boom <= 9)
	{
		putimage(m_nRow, m_nCol, ship.getwidth(),
			ship.getheight(), &smallboom3, 0, 0);
	}

	if (m_Boom >= 10 && m_Boom <= 12)
	{
		putimage(m_nRow, m_nCol, ship.getwidth(),
			ship.getheight(), &smallboom4, 0, 0);
	}

	if (m_Boom == 14)
	{
		cleardevice();
		m_Boom = 15;
	}
}