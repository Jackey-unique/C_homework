#pragma once

#include<stdio.h>
#include<graphics.h>


#define WIN_WIDTH 900
#define WIN_HEIGHT 600

enum {WAN_DOU, XIANG_RI_KUI_, PLANT_COUNT};

IMAGE static imgBg;
IMAGE static imgBar;
IMAGE static imgCards[PLANT_COUNT];
IMAGE static* imgPlant[PLANT_COUNT][20];

int static curX, curY;//��ǰѡ�е�ֲ����ƶ������е�λ��
int static curPlant;//0:û��ѡ�У�1��ѡ���˵�һ��ֲ��

static struct plant
{
	int type;       //0��û��ֲ��    1��ѡ���˵�һ��ֲ��
	int frameIndex;//����֡���
};

static struct plant map[5][9];

static struct sunshineBall//��������
{
	int x, y;//��������Ʈ������е�����λ�ã�x���䣩
	int frameIndex;//��ǰ��ʾ��ͼƬ֡�����
	int destY;//Ʈ���Ŀ��λ�õ�y����
};

//�� 10����������һ����һ�������껹��ȥ
//struct sunshineBall balls


//��Ϸ����
void gameInit();
//���´���
void updateWindow();
//����͸��
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);
int getDelay();
//�û����
void userClick();
//�ж��ļ��Ƿ����
bool fileExist(const char* name);
//������Ϸ���ڣ�ʹֲ�ﶯ����
void updateGame();
//��ȡ�ӳ�ʱ�䣬������Ϸ����
int getDelay();
//��Ϸ�˵�
void startUI();


//����ʮ���м�����Ϊjackey������ʬ�γɺ�����
struct zm
{
	int x, y;
	int frameIndex;
	bool used;
	int speed;
};
struct zm zms[10];
IMAGE imgZM[22];