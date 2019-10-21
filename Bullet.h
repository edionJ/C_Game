#pragma once
#include "easyx.h"
class Bullet
{
public:
	int m_nRow;
	int m_nCol;

	Bullet(int nRow, int nCol);
	void MoveUp();					
	void ShowYellow();
	void ShowClear();					// ¸²¸Ç×Óµ¯
	void MoveDown();					// ×Óµ¯ÏÂÒÆ
	void ShowRed();
};
