#include <conio.h>
#include "Game.h"
#include "easyx.h"
#include "Control.h"
#include "Enemy.h"
#include "Ship.h"
#include "SmallEnemy.h"
#include "Bullet.h"

Ship myship(GAMEWIDTH / 2 - 20, GAMEHIGHT - 60, 100);		// 飞船位置，血量
Enemy myenemy(GAMEWIDTH / 2 - 50, 0, 100);					// 敌机位置，血量
SmallEnemy mysmallenemy(0, 0);							// 小敌机

vector<Bullet*> VectorBullets;
vector<Bullet*> VectorEnenyBullets;
vector<Bullet*>::iterator Iter;						//迭代器
vector<GameRole*> RoleVector;

clock_t ClkMakeBulletStart = clock();
clock_t ClkMakeBulletFinish = clock();						// 飞船产生子弹

IMAGE boom1, boom2, boom3, boom4;
IMAGE smallboom1, smallboom2, smallboom3, smallboom4;
IMAGE background, ship, ship1, enemy, enemy1, smallenemy, smallenemy1;

enum Direction
{
	DOWN,
	Left,
	Right
};

enum GAMEINPUT
{
	UPINPUT = 0X1,
	DOWNINPUT = 0X2,
	LEFTINPUT = 0X4,
	RIGHTINPUT = 0X8,
	FIREINPUT = 0X10,
	ESCINPUT = 0X20,
	SPACEINPUT = 0X40,
	NOINPUT = 0X80
};

int myinput = NOINPUT;

void Game::LoadRes() {
	//加载爆炸效果
	loadimage(&boom1, _T("res\\boom\\boom1.png"));
	loadimage(&boom2, _T("res\\boom\\boom2.png"));
	loadimage(&boom3, _T("res\\boom\\boom3.png"));
	loadimage(&boom4, _T("res\\boom\\boom4.png"));
	loadimage(&smallboom1, _T("res\\boom\\smallboom1.png"));
	loadimage(&smallboom2, _T("res\\boom\\smallboom2.png"));
	loadimage(&smallboom3, _T("res\\boom\\smallboom3.png"));
	loadimage(&smallboom4, _T("res\\boom\\smallboom4.png"));
	//加载背景
	loadimage(&background, _T("res\\background.jpg"), GAMEWIDTH, GAMEHIGHT, true);
	// 加载飞机
	loadimage(&ship, _T("res\\redship.png"));
	loadimage(&ship1, _T("res\\redship1.png"));
	// 加载敌机
	loadimage(&enemy, _T("res\\enemy.png"));
	loadimage(&enemy1, _T("res\\enemy1.png"));
	// 加载小敌机
	loadimage(&smallenemy, _T("res\\smallenemy.png"));
	loadimage(&smallenemy1, _T("res\\smallenemy1.png"));
	//加载背景音乐
	mciSendString(L"open res\\music.mp3 alias mysong", NULL, 0, NULL);		
	//加载开始界面音乐
	mciSendString(L"open res\\start.mp3 alias startsong", NULL, 0, NULL);		
}

void Game::InitAttribute() {
	Score = 0;
	myenemy.direction = DOWN;
	myenemy.m_nStartHight = 0;
	myenemy.m_Move = 0;
	myenemy.m_Fire = 0;
	myenemy.m_Boom = 0;
	GetNewShip();
	GetNewEnemy();
	GetNewSmallEnemy();
	RoleVector.push_back(&myship);			//在尾部加数据
	RoleVector.push_back(&myenemy);
	RoleVector.push_back(&mysmallenemy);
}

void Game::GameStart() {
	// 初始化开始界面窗口
	mciSendString(L"play startsong repeat", NULL, 0, NULL);         
	putimage(0, 0, &background);		
	system("pause");
	cleardevice();
	mciSendString(L"stop startsong", NULL, 0, NULL);         	
	mciSendString(L"play mysong repeat", NULL, 0, NULL);
	//初始化基本数据
	InitAttribute();
}

void Game::GetNewShip()
{
	// 产生新飞船
	myship.m_nRow = GAMEWIDTH / 2 - 20;
	myship.m_nCol = GAMEHIGHT - 60;
	myship.m_nLife = 100;
	myship.m_Boom = 0;
}

void Game::GetNewEnemy()
{
	// 敌机摧毁后新建一个敌机
	// 产生新敌机
	setfillcolor(BLACK);
	solidrectangle(myenemy.m_nRow, myenemy.m_nCol - 10, myenemy.m_nRow + myenemy.m_nLife, myenemy.m_nCol - 5);
	myenemy.m_nRow = rand() % (GAMEWIDTH - enemy.getwidth());
	myenemy.m_nCol = -enemy.getheight();

	myenemy.m_nLife = 100;
	myenemy.direction = DOWN;
	myenemy.m_nStartHight = myenemy.m_nCol;
	myenemy.m_Boom = 0;
	myenemy.m_Move = 0;
	myenemy.m_Fire = 0;
}

void Game::GetNewSmallEnemy()
{
	// 产生新小敌机
	mysmallenemy.m_nRow = rand() % (GAMEWIDTH - smallenemy.getwidth());
	mysmallenemy.m_nCol = 0;
	mysmallenemy.m_Boom = 0;
}

void Game::HandleBoom()
{
	if (myenemy.m_Boom >= 1 && myenemy.m_Boom <= 14)
	{
		myenemy.m_Boom++;
	}

	if (mysmallenemy.m_Boom >= 1 && mysmallenemy.m_Boom <= 13)
	{
		mysmallenemy.m_Boom++;
	}

	// 获得新敌机
	if (myenemy.m_nLife <= 0 && myenemy.m_Boom == 15)
	{
		//cleardevice();
		myenemy.ShowClear();
		GetNewEnemy();
	}

	// 敌机爆炸开始条件
	if (myenemy.m_nLife <= 0 && myenemy.m_Boom == 0)
	{

		Score += 100;
		myenemy.m_Boom = 1;
	}

	if (mysmallenemy.m_Boom == 0 && IsSmallHitLow() == true)
	{
		GetNewSmallEnemy();
	}

	if (mysmallenemy.m_Boom == 14)
	{
		// 产生新小敌机
		GetNewSmallEnemy();
	}

	// 显示敌机和飞船
	if (myenemy.m_Boom == 0)
	{
		myenemy.Show();
	}

	// 显示随机小敌机		
	if (mysmallenemy.m_Boom == 0)
	{
		mysmallenemy.Show();
	}

	if (myship.m_Boom >= 1 && myship.m_Boom <= 13)
	{
		myship.m_Boom++;
	}

	myenemy.m_Move++;
	myenemy.m_Fire++;
}

int Game::HandleGameOver()
{
	if (IsGameOver())
	{
		mciSendString(_T("close MySong"), NULL, 0, NULL);

		// 清空数组
		for (size_t i = 0; i < VectorBullets.size(); i++)
		{
			VectorBullets.pop_back();
		}

		// 清空数组
		for (size_t i = 0; i < VectorEnenyBullets.size(); i++)
		{
			VectorEnenyBullets.pop_back();
		}

		cleardevice();

		// 游戏结束提示
		ShowScore();
		setbkmode(TRANSPARENT);			// 字体透明
		settextcolor(RED);
		settextstyle(40, 30, _T("宋体"));
		outtextxy(GAMEWIDTH / 2 - 140, 20, _T("GAME OVER"));
		outtextxy(GAMEWIDTH / 2 - 160, 320, _T("ESC退出"));
		outtextxy(GAMEWIDTH / 2 - 160, 380, _T("R重新开始"));
		while (_kbhit())
		{
			_getch();
		}

		char chInPut = '\0';
		chInPut = _getch();

		if (chInPut == 'R' || chInPut == 'r')
		{
			return -2;
		}
		if (chInPut == 27)
		{
			return -1;
		}
	}
	return 1;
}

void Game::GetOrder()
{
	ClkMakeBulletFinish = clock();		// 飞船子弹产生时间

	if (GetAsyncKeyState('W') & 0x8000)
	{
		myinput |= UPINPUT;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		myinput |= DOWNINPUT;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		myinput |= LEFTINPUT;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		myinput |= RIGHTINPUT;
	}

	if (GetAsyncKeyState('K') & 0x8000 && (ClkMakeBulletFinish - ClkMakeBulletStart > 200))
	{
		// 飞船子弹
		myinput |= FIREINPUT;
		ClkMakeBulletStart = ClkMakeBulletFinish;
	}

	if (GetAsyncKeyState(' ') & 0x8000)
	{
		myinput |= SPACEINPUT;
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		myinput |= ESCINPUT;
	}
}

void Game::CoverShip()
{
	//移动时覆盖
	if (myinput & UPINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & DOWNINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & LEFTINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & RIGHTINPUT)
	{
		myship.ShowClear();
	}
}

void Game::DealInPut()
{
	if ((myinput & UPINPUT) && (myship.m_nCol >= 10))
	{
		myship.m_nCol -= 2;
	}

	if ((myinput & DOWNINPUT) && (myship.m_nCol <= GAMEHIGHT - ship.getheight() - 10))
	{
		myship.m_nCol += 2;
	}

	if ((myinput & LEFTINPUT) && (myship.m_nRow >= 10))
	{
		myship.m_nRow -= 2;
	}

	if ((myinput & RIGHTINPUT) && (myship.m_nRow <= GAMEWIDTH - ship.getwidth() - 10))
	{
		myship.m_nRow += 2;
	}

	if (myinput & FIREINPUT)
	{
		Bullet* pNewBullet = new Bullet(myship.m_nRow + ((ship.getwidth() / 2)), myship.m_nCol - 5);
		VectorBullets.push_back(pNewBullet);
	}

	if (myinput & SPACEINPUT)
	{
		_getch();
	}

	if (myinput & ESCINPUT)
	{
		exit(0);
	}

	myinput = NOINPUT;
}

void Game::EnemyMove()
{
	// 掩盖敌机
	myenemy.ShowClear();

	// 掩盖敌机的血量
	myenemy.ShowClearLife();

	if (myenemy.m_Move % 10 == 0)
	{
		cleardevice();
		if (myenemy.m_nCol < 0)
		{
			myenemy.MoveDown();
		}

		if (myenemy.direction == DOWN)
		{
			myenemy.MoveDown();

			if (myenemy.m_nCol >= myenemy.m_nStartHight + 20)
			{
				myenemy.direction = Right;
			}
		}

		if (myenemy.direction == Right)
		{
			myenemy.MoveRight();

			if (myenemy.m_nRow >= GAMEWIDTH - enemy.getwidth())
			{
				myenemy.direction = Left;
			}
		}

		if (myenemy.direction == Left)
		{
			myenemy.MoveLeft();

			if (myenemy.m_nRow <= 0)
			{
				myenemy.direction = DOWN;
				myenemy.m_nStartHight = myenemy.m_nCol;
			}
		}
		// 掩盖小敌机
		mysmallenemy.ShowClear();

		// 随机小敌机的自动下移
		if (mysmallenemy.m_Boom == 0)
		{
			mysmallenemy.MoveDown();
		}
	}
}

void Game::DeleteMemory()
{
	// 飞船子弹到上边界释放
	for (vector<Bullet*>::iterator Iter = VectorBullets.begin(); Iter != VectorBullets.end();)
	{
		if (VectorBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if ((*Iter)->m_nCol < 0)
		{
			(*Iter)->ShowClear();
			delete* Iter;
			*Iter = nullptr;
			VectorBullets.erase(Iter);
			Iter = VectorBullets.begin();
		}

		if (VectorBullets.size() != 0)
		{
			Iter++;
		}
	}

	// 敌机子弹到底部释放
	for (vector<Bullet*>::iterator Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end();)
	{
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if ((*Iter)->m_nCol > GAMEHIGHT)
		{
			(*Iter)->ShowClear();
			delete* Iter;
			*Iter = nullptr;
			VectorEnenyBullets.erase(Iter);
			Iter = VectorEnenyBullets.begin();
		}

		if (VectorEnenyBullets.size() != 0)
		{
			Iter++;
		}
	}
}

void Game::ShowBullet()
{
	// 显示飞船子弹
	for (Iter = VectorBullets.begin(); Iter != VectorBullets.end(); Iter++)
	{
		if (VectorBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		(*Iter)->ShowClear();
		(*Iter)->MoveUp();
		(*Iter)->ShowYellow();
	}

	// 显示敌机子弹
	for (Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end(); Iter++)
	{
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		(*Iter)->ShowClear();
		(*Iter)->MoveDown();
		(*Iter)->ShowRed();
	}
}

void Game::HpSleep(int ms)
{
	static clock_t ClkGameFinish = clock();
	ClkGameFinish += ms * CLOCKS_PER_SEC / 1000;

	if (clock() > ClkGameFinish)
	{
		ClkGameFinish = clock();
	}
	else
	{
		while (clock() < ClkGameFinish)
		{
			Sleep(1);
		}
	}
}

bool Game::IsBullertHitSmall()
{
	// 小敌机的再次产生，当中弹或者到达屏幕底部
	for (vector<Bullet*>::iterator Iter = VectorBullets.begin(); Iter != VectorBullets.end(); Iter++)
	{
		if (VectorBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if (((*Iter)->m_nRow >= mysmallenemy.m_nRow && (*Iter)->m_nRow <= mysmallenemy.m_nRow + smallenemy.getwidth())
			&& ((*Iter)->m_nCol <= mysmallenemy.m_nCol + smallenemy.getheight() && (*Iter)->m_nCol >= mysmallenemy.m_nCol))
		{
			(*Iter)->ShowClear();
			delete* Iter;
			*Iter = nullptr;
			VectorBullets.erase(Iter);
			if (mysmallenemy.m_Boom == 0)
			{
				mysmallenemy.m_Boom = 1;
			}
			//mygamecontrol.m_nScore += 10;
			Score += 10;
			return true;
		}
	}
	return false;
}

void Game::IsSmallHitShip()
{
	// 判断小敌机是否撞到飞船，撞到后飞船血量减少，小敌机消失重建
	if (((myship.m_nRow + (ship.getwidth() / 2) >= mysmallenemy.m_nRow) && (myship.m_nRow <= mysmallenemy.m_nRow + smallenemy.getwidth()))
		&& ((myship.m_nCol <= mysmallenemy.m_nCol + smallenemy.getheight()) && ((myship.m_nCol >= mysmallenemy.m_nCol))))
	{
		// 掩盖小敌机
		mysmallenemy.ShowClear();

		// 产生新小敌机
		mysmallenemy.m_nRow = rand() % (GAMEWIDTH - smallenemy.getwidth());
		mysmallenemy.m_nCol = 0;

		// 掩盖飞船血量
		myship.ShowClearLife();
		// 飞船血量减少
		myship.GetHit();
		cleardevice();
	}
}

void Game::IsShipHurt()
{
	// 判断飞船是否中弹	
	for (vector<Bullet*>::iterator Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end(); Iter++)
	{
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if (((*Iter)->m_nRow >= myship.m_nRow && (*Iter)->m_nRow <= myship.m_nRow + ship.getwidth())
			&& ((*Iter)->m_nCol <= myship.m_nCol + ship.getheight() && (*Iter)->m_nCol >= myship.m_nCol))
		{
			(*Iter)->ShowClear();
			delete* Iter;
			*Iter = nullptr;
			VectorEnenyBullets.erase(Iter);
			Iter = VectorEnenyBullets.begin();

			// 掩盖飞船血量		
			myship.ShowClearLife();
			myship.GetHit();
			cleardevice();
			if (VectorEnenyBullets.size() == 0)
			{
				break;
			}
		}
	}
}

void Game::IsEnenmyHurt()
{
	// 判断敌机是否中弹
	for (vector<Bullet*>::iterator Iter = VectorBullets.begin(); Iter != VectorBullets.end(); Iter++)
	{
		if (VectorBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if (((*Iter)->m_nRow >= myenemy.m_nRow && (*Iter)->m_nRow <= myenemy.m_nRow + enemy.getwidth())
			&& ((*Iter)->m_nCol <= myenemy.m_nCol + enemy.getheight() && (*Iter)->m_nCol >= myenemy.m_nCol))
		{
			if (VectorBullets.size() == 0)
			{
				break;
			}
			if (*Iter == nullptr)
			{
				break;
			}
			(*Iter)->ShowClear();
			delete* Iter;
			*Iter = nullptr;
			VectorBullets.erase(Iter);
			Iter = VectorBullets.begin();
			// 掩盖敌机血量
			myenemy.ShowClearLife();
			// 敌机受伤血量减5
			myenemy.GetHit();
			break;
		}
	}
}

bool Game::IsGameOver()
{
	// 飞机和敌人碰撞
	if (((myship.m_nRow >= myenemy.m_nRow) && (myship.m_nRow <= myenemy.m_nRow + enemy.getwidth()))
		&& ((myship.m_nCol <= myenemy.m_nCol + enemy.getheight()) && ((myship.m_nCol >= myenemy.m_nCol))))
	{
		return true;
	}

	// 敌机碰到下边缘
	if (myenemy.m_nCol + enemy.getheight() > GAMEHIGHT)
	{
		return true;
	}

	// 飞船血量为0
	if (myship.m_nLife <= 0)
	{
		if (myship.m_Boom == 15)
		{
			return true;
		}
		if (myship.m_Boom == 0)
		{
			myship.m_Boom = 1;
		}
	}
	return false;
}

void Game::MakeEnemyBullet()
{
	if (myenemy.m_Fire % 50 == 0)
	{
		// 创造敌机子弹
		Bullet* pNewEnemyBullet = new Bullet((myenemy.m_nRow + enemy.getwidth() / 2), myenemy.m_nCol + enemy.getheight());
		VectorEnenyBullets.push_back(pNewEnemyBullet);
	}
}

bool Game::IsSmallHitLow()
{
	if (mysmallenemy.m_nCol >= GAMEHIGHT)
	{
		return true;
	}
	return false;
}

void Game::ShowScore()
{
	TCHAR scoretext[50];
	setfillcolor(BLACK);
	solidrectangle(0, 0, 100, 20);
	setbkmode(TRANSPARENT);				// 字体透明
	settextcolor(LIGHTBLUE);
	settextstyle(20, 10, _T("宋体"));
	swprintf(scoretext, 50, _T("Score:%d"), Score);
	outtextxy(0, 0, scoretext);
}