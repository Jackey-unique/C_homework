#define _CRT_SECURE_NO_WARNINGS

/*
* ������־
* 1.��������Ŀ
* 2.�����ز�
* 3.������Ϸ��ʼ��������ͼ��ֲ�￨�ۣ�
* 4.��ֲֲ�����ֲ��ҡ���ٶ�
* 5.�Ż���Ϸѭ������Ϸ��Ⱦ˳��
* 6.���������˵�
* 7.�����������
*/


#include"game.h"


int main()
{
	gameInit();
	startUI();

	int timer = 0;
	bool flag = true;
	while (1)
	{
		userClick();
		timer += getDelay();//��ȡ�ӳ�ʱ��,�жϸ�����Ϸ����
		if (timer > 80)//100�ӽ�ԭ�棬����֡��̫��
		{
			flag = true;
			timer = 0;
		}

		if (flag)
		{
			flag = false;
			updateWindow();
			updateGame();

		}

	}

	

	system("pause");
	return 0;
}