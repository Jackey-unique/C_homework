#define _CRT_SECURE_NO_WARNINGS


#include"game.h"

void gameInit()
{
	//�����б���ͼƬ
	loadimage(&imgBg, "res/map0.jpg");
	//����ֲ����
	loadimage(&imgBar, "res/bar5.png");

	memset(imgPlant, 0, sizeof(imgPlant));//���ֽڸ�ֵ��ȫ��Ϊ��
	memset(map, 0, sizeof(map));

	//��ʼ��ֲ�￨��
	char name[64] = { 0 };
	for (int i = 0; i < PLANT_COUNT; i++)
	{
		//����ֲ�￨�Ƶ��ļ���
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);

		loadimage(&imgCards[i], name);
		for (int j = 0; j < 20; j++)
		{
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png",i,j+1);
			//���ж��ļ��Ƿ����
			if (fileExist(name))
			{
				imgPlant[i][j] = new IMAGE;
				loadimage(imgPlant[i][j],name);
			}
			else
			{
				break;
			}
		}

	}

	curPlant = 0;
	//������Ϸ��ͼ�δ���
	initgraph(WIN_WIDTH, WIN_HEIGHT, 1);
	//��ʬ����jackey
	memset(zms, 0, sizeof(zms));
	for (int i = 0; i < 22; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm/%d.png", i + 1);
		loadimage(&imgZM[i], name);
	}


}

void updateWindow()
{
	BeginBatchDraw();//��ʼ����

	putimage(0, 0, &imgBg);
	putimagePNG(250, 0, &imgBar);

	for (int i = 0; i < PLANT_COUNT; i++)
	{
		int x = 338 + i * 65;
		int y = 6;
		putimage(x, y, &imgCards[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type > 0)
			{
				int x = 256 + j * 81;
				int y = 80 + i * 97+ 14;
				int PlantType = map[i][j].type - 1;
				int index = map[i][j].frameIndex;
				putimagePNG(x, y, imgPlant[PlantType][index]);
			}
		}
	}

	//��Ⱦ �϶������е�ֲ��
	if (curPlant > 0)
	{
		IMAGE* img = imgPlant[curPlant - 1][0];
		putimagePNG(curX - img->getwidth() / 2, curY - img->getheight() / 2, img);//�����ʾ��ֲ��ͼ���м�
	}

	EndBatchDraw();//����˫����

}

void userClick()
{
	ExMessage msg;
	static int status = 0;
	if(peekmessage(&msg))//�ж�������
	{
		if (msg.message == WM_LBUTTONDOWN)//��곤����ק
		{
			if (msg.x > 338 && msg.x < 338 + 65 * PLANT_COUNT && msg.y < 96)
			{
				int index = (msg.x - 338) / 65;
				status = 1;
				curPlant = index + 1;
			}
		}
		else if (msg.message == WM_MOUSEMOVE && status == 1)//����ƶ�
		{
			curX = msg.x;
			curY = msg.y;
		}
		else if (msg.message == WM_LBUTTONUP)//�ɿ�������
		{
			if (msg.x > 256 && msg.y > 80 && msg.y < 570)
			{
				int row = (msg.y - 80) / 97;
				int col = (msg.x - 256) / 81;
				
				if(map[row][col].type==0)
				{
					map[row][col].type = curPlant;
					map[row][col].frameIndex = 0;
				}
				
			}
			

			curPlant = 0;
			status = 0; 
		}
	}
}

bool fileExist(const char* name)
{
	FILE* fp = fopen(name, "r");
	if (fp == NULL)
	{
		return false;
	}
	else
	{
		fclose(fp);
		return true;
	}
}
/**/
void creatZM()
{
	static int zmFre = 500;//��ʬ����Ƶ��
	static int count = 0;//��ʬ������
	count++;
	if (count > zmFre)
	{
		count = 0;
		zmFre = rand() % 200 + 300;
		int i;
		int zmMAX = sizeof(zms) / sizeof(zms[0]);
		for (i = 0; i < zmMAX && zms[i].used; i++);
		if (i < zmMAX)
		{
			zms[i].used = true;
			zms[i].x = WIN_WIDTH;
			zms[i].y = 17 + (1 + rand() % 3) * 100;
			zms[i].speed = 1;
		}
	}
}
void updateZM()
{
	int zmMax = sizeof(zms) / sizeof(zms[0]);

	//���½�ʬ��λ��
	for (int i = 0; i < zmMax; i++)
	{
		if (zms[i].used)
		{
			zms[i].x -= zms[i].speed;//��ʬ����
			if (zms[i].x < 170)
			{
				printf("gameover\n");
				MessageBox(NULL, "over", "over", 0);//���Ż�
				exit(0);//���Ż�
			}
		}
	}

}


void updateGame()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type > 0)
			{
				map[i][j].frameIndex++;
				int PlantType = map[i][j].type - 1;
				int index = map[i][j].frameIndex;
				if (imgPlant[PlantType][index] == NULL)
				{
					map[i][j].frameIndex = 0;
				}
			}
		}
	}
	creatZM();//������ʬ
	updateZM();//���½�ʬ״̬

}

void startUI()
{
	IMAGE imgBg, imgMenu1, imgMenu2;
	loadimage(&imgBg, "res/Screen/MainMenu.png");
	loadimage(&imgMenu1, "res/menu1.png");
	loadimage(&imgMenu2, "res/menu2.png");
	int flag = 0;//δѡ����ʾ

	while (1)
	{
		BeginBatchDraw();
		putimage(0, 0, &imgBg);
		putimagePNG(474, 75, flag ? &imgMenu1 : &imgMenu2);//�ж��Ƿ�ѡ�У�ѡ��ǰ��ͼƬ��һ��

		ExMessage msg;
		if (peekmessage(&msg))//�ж�������
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x > 474 && msg.x < 474 + 300 && msg.y > 75 && msg.y < 75 + 145)
			{
				flag = 1;
				//EndBatchDraw();
			}
			else if (msg.message == WM_LBUTTONUP && flag==1)
			{
				return;
			}
		}
		EndBatchDraw();
	}
}