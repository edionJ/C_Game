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
	//�������
	void LoadRes();			//������Դ
	void InitAttribute();	//��ʼ������
	void GameStart();		//��ʼ����
	int  HandleGameOver();	//������Ϸ����
	void HandleBoom();		//����ը״̬
	void DeleteMemory();	//�ͷ��ڴ�
	void HpSleep(int ms);	//��ʱ
	//״̬��Ϣ����
	void GetNewShip();		//���ɷɴ�
	void GetNewEnemy();		//���ɵл�
	void GetNewSmallEnemy();//����С�л�
	void MakeEnemyBullet();						// �����ɴ��ӵ�
	void GetOrder();		//��ȡ����ָ��
	void CoverShip();		//���Ƿɴ�
	void DealInPut();		//�������
	void EnemyMove();		//�ɴ��ƶ�
	bool IsGameOver();							// �ж���Ϸ����
	bool IsBullertHitSmall();
	void IsSmallHitShip();						// �ж�С�л��Ƿ�ײ���ɴ�
	bool IsSmallHitLow();							// С�л����ײ�
	void IsShipHurt();							// �жϷɴ��Ƿ��е�
	void IsEnenmyHurt();						// �жϵл��Ƿ��е�
	//��ʾ����
	void ShowBullet();		//��ʾ�ӵ�
	void ShowScore();
private:
	int Score;
};
