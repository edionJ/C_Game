#pragma once
class GameRole{
public:
	int m_nRow;
	int m_nCol;
	int m_nLife;
	int m_Boom;								// ��ը״̬

	GameRole();
	~GameRole();
	virtual void ShowClear();				// �ڸǽ�ɫ
	virtual void Show();					// ��ʾ��ɫ
	virtual void ShowClearLife();			// �ڸǽ�ɫѪ��
	virtual void ShowLife();				// ��ʾ��ɫѪ��
	virtual void ShowBoom();				// ��ʾ��ը
};

