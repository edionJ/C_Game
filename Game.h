#pragma once
#include <vector>
#include <time.h>
#include "easyx.h"
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"
#include "SmallEnemy.h"
#include "Control.h"
using namespace std;

#define GAMEWIDTH 640
#define GAMEHIGHT 480

extern IMAGE boom1, boom2, boom3, boom4;
extern IMAGE smallboom1, smallboom2, smallboom3, smallboom4;
extern IMAGE background, ship, ship1, enemy, enemy1, smallenemy, smallenemy1;

extern vector<Bullet*> VectorBullets;
extern vector<Bullet*> VectorEnenyBullets;
extern vector<Bullet*>::iterator Iter;
extern vector<GameRole*> RoleVector;


class Game{
public:
	//管理操作
	void LoadRes();			//加载资源
	void InitAttribute();	//初始化属性
	void GameStart();		//初始界面
	int  HandleGameOver();	//处理游戏结束
	void HandleBoom();		//处理爆炸状态
	void DeleteMemory();	//释放内存
	void HpSleep(int ms);	//延时
	//状态信息操作
	void GetNewShip();		//生成飞船
	void GetNewEnemy();		//生成敌机
	void GetNewSmallEnemy();//生成小敌机
	void MakeEnemyBullet();						// 产生飞船子弹
	void GetOrder();		//获取键盘指令
	void CoverShip();		//覆盖飞船
	void DealInPut();		//处理操作
	void EnemyMove();		//飞船移动
	bool IsGameOver();							// 判断游戏结束
	bool IsBullertHitSmall();
	void IsSmallHitShip();						// 判断小敌机是否撞到飞船
	bool IsSmallHitLow();							// 小敌机到底部
	void IsShipHurt();							// 判断飞船是否中弹
	void IsEnenmyHurt();						// 判断敌机是否中弹
	//显示操作
	void ShowBullet();		//显示子弹
	void ShowScore();
private:
	int Score;
};
