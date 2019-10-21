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
	mGame.LoadRes();							//������Ϸ��Դ
	initgraph(GAMEWIDTH, GAMEHIGHT);			//��ʼ��ͼ�λ���

	int nSign = 1;								//���

	while (nSign != -1)
	{
		mGame.GameStart();						//��Ϸ��ʼ��
		while (nSign > 0)
		{
			//״̬���ݴ���
			mGame.GetOrder();
			mGame.CoverShip();					// �ڸǷɴ�
			mGame.DealInPut();
			mGame.EnemyMove();
			//��ʾ����
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


			mGame.MakeEnemyBullet();// �����л��ӵ�
			mGame.DeleteMemory();// �ͷ��ڴ�
			mGame.IsEnenmyHurt();// �жϵл��Ƿ��е�
			mGame.IsShipHurt();// �жϷɴ��Ƿ��е�
			mGame.IsSmallHitShip();// �ж�С�л��Ƿ�ײ���ɴ�
			mGame.IsBullertHitSmall();// С�л��Ƿ񱻻���
			mGame.HandleBoom();// ����ը״̬
			nSign = mGame.HandleGameOver();
			mGame.HpSleep(10);// ��ʱ
		}
				
		RoleVector.pop_back();
		RoleVector.pop_back();
		RoleVector.pop_back();
		nSign = 1;
		
	}	
	//��Ϸ����
	closegraph();
	return 0;
}