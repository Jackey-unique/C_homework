#define _CRT_SECURE_NO_WARNINGS

/*
* 开发日志
* 1.创建新项目
* 2.导入素材
* 3.创建游戏初始场景（地图，植物卡槽）
* 4.种植植物，更改植物摇摆速度
* 5.优化游戏循环和游戏渲染顺序
* 6.制作启动菜单
* 7.生成随机阳光
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
		timer += getDelay();//获取延迟时间,判断更新游戏窗口
		if (timer > 80)//100接近原版，但是帧数太低
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