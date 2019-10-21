#pragma once
#include "easyx.h"
#include <time.h>
#include "GameRole.h"
#include "Control.h"

class Enemy :public GameRole
{
public:
	Enemy(int nRow, int nCol, int nLife);
	~Enemy();
	
	char direction;		        // �л�����
	int m_nStartHight;			// �л���ʼ�߶�
	int m_Move;					// �л��ƶ�״̬
	int m_Fire;                 // �л������ӵ�״̬

	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ShowClear();			// �ڸǵл�
	void Show();				// ���Ƶл�
	void ShowClearLife();		// �ڸǵл�Ѫ��
	void ShowLife();			// ��ʾ�л�Ѫ��
	void GetHit();				// �л��е�
	void ShowBoom();			// ��ʾ��ը	
};

