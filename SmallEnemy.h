#pragma once
#include "Game.h"
#include "easyx.h"
#include "GameRole.h"

class SmallEnemy : public GameRole
{
public:
	SmallEnemy(int nRow, int nCol);
	~SmallEnemy();

	void ShowClear();				// 掩盖角色
	void Show();					// 显示角色
	void ShowClearLife();			// 掩盖角色血量
	void ShowLife();				// 显示角色血量
	void ShowBoom();				// 显示小敌机爆炸
	void GetNew();					// 获取新的
	void MoveDown();				//下移		
};

