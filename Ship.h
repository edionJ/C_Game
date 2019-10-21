#pragma once
#include "Game.h"
#include "GameRole.h"
#include "easyx.h"

class Ship :public GameRole
{
public:
	Ship(int nRow, int nCol, int nLife);
	~Ship();
	void ShowClear();				// �ڸǷɴ�
	void Show();					// ��ʾ�ɴ�
	void ShowClearLife();			// �ڸǷɴ�Ѫ��
	void GetHit();					// �ɴ��յ��˺�
	void ShowLife();				// ��ʾ�ɴ�Ѫ��
	void ShowBoom();                // ��ʾ��ը	
};


