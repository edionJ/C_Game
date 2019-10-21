#pragma once
#include "Game.h"
#include "GameRole.h"
#include "easyx.h"

class Ship :public GameRole
{
public:
	Ship(int nRow, int nCol, int nLife);
	~Ship();
	void ShowClear();				// ÑÚ¸Ç·É´¬
	void Show();					// ÏÔÊ¾·É´¬
	void ShowClearLife();			// ÑÚ¸Ç·É´¬ÑªÁ¿
	void GetHit();					// ·É´¬ÊÕµ½ÉËº¦
	void ShowLife();				// ÏÔÊ¾·É´¬ÑªÁ¿
	void ShowBoom();                // ÏÔÊ¾±¬Õ¨	
};


