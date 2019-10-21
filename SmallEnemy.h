#pragma once
#include "Game.h"
#include "easyx.h"
#include "GameRole.h"

class SmallEnemy : public GameRole
{
public:
	SmallEnemy(int nRow, int nCol);
	~SmallEnemy();

	void ShowClear();				// �ڸǽ�ɫ
	void Show();					// ��ʾ��ɫ
	void ShowClearLife();			// �ڸǽ�ɫѪ��
	void ShowLife();				// ��ʾ��ɫѪ��
	void ShowBoom();				// ��ʾС�л���ը
	void GetNew();					// ��ȡ�µ�
	void MoveDown();				//����		
};

