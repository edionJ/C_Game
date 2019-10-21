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
	
	char direction;		        // 敌机方向
	int m_nStartHight;			// 敌机起始高度
	int m_Move;					// 敌机移动状态
	int m_Fire;                 // 敌机发射子弹状态

	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ShowClear();			// 掩盖敌机
	void Show();				// 绘制敌机
	void ShowClearLife();		// 掩盖敌机血量
	void ShowLife();			// 显示敌机血量
	void GetHit();				// 敌机中弹
	void ShowBoom();			// 显示爆炸	
};

