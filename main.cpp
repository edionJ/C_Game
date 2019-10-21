#pragma comment(lib, "WINMM.LIB")
#include "easyx.h"
#include "Enemy.h"
#include "Ship.h"
#include "Bullet.h"
#include "GameRole.h"
#include "Game.h"


int main()
{
	Game mGame;
	mGame.LoadRes();							//加载游戏资源
	initgraph(GAMEWIDTH, GAMEHIGHT);			//初始化图形环境

	int nSign = 1;								//标记

	while (nSign != -1)
	{
		mGame.GameStart();						//游戏初始化
		while (nSign > 0)
		{
			//状态数据处理
			mGame.GetOrder();
			mGame.CoverShip();					// 掩盖飞船
			mGame.DealInPut();
			mGame.EnemyMove();
			//显示处理
			for (size_t i = 0; i < RoleVector.size(); i++)
			{
				RoleVector[i]->ShowClearLife();
				RoleVector[i]->ShowLife();
				RoleVector[i]->ShowClear();
				RoleVector[i]->Show();
				RoleVector[i]->ShowBoom();
			}
			mGame.ShowBullet();
			mGame.ShowScore();


			mGame.MakeEnemyBullet();// 产生敌机子弹
			mGame.DeleteMemory();// 释放内存
			mGame.IsEnenmyHurt();// 判断敌机是否中弹
			mGame.IsShipHurt();// 判断飞船是否中弹
			mGame.IsSmallHitShip();// 判断小敌机是否撞到飞船
			mGame.IsBullertHitSmall();// 小敌机是否被击中
			mGame.HandleBoom();// 处理爆炸状态
			nSign = mGame.HandleGameOver();
			mGame.HpSleep(10);// 延时
		}
				
		RoleVector.pop_back();
		RoleVector.pop_back();
		RoleVector.pop_back();
		nSign = 1;
		
	}	
	//游戏结束
	closegraph();
	return 0;
}