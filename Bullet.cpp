#include "Bullet.h"

void Bullet::MoveUp()
{
	m_nCol -= 3;
}

void Bullet::ShowYellow()
{
	setfillcolor(YELLOW);
	solidcircle(m_nRow, m_nCol, 5);
}

void Bullet::ShowClear()				// ¸²¸Ç×Óµ¯
{
	setfillcolor(BLACK);
	solidcircle(m_nRow, m_nCol, 5);
}

void Bullet::MoveDown()
{
	m_nCol += 3;
}

Bullet::Bullet(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
}

void Bullet::ShowRed()
{
	setfillcolor(RED);
	solidcircle(m_nRow, m_nCol, 5);
}

