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

int static curX, curY;//当前选中的植物，在移动过程中的位置
int static curPlant;//0:没有选中，1：选中了第一种植物

static struct plant
{
	int type;       //0：没有植物    1：选择了第一种植物
	int frameIndex;//序列帧序号
};

static struct plant map[5][9];

static struct sunshineBall//定义阳光
{
	int x, y;//阳光球在飘落过程中的坐标位置（x不变）
	int frameIndex;//当前显示的图片帧的序号
	int destY;//飘落的目标位置的y坐标
};

//池 10个阳光球，用一个拿一个，用完还回去
//struct sunshineBall balls


//游戏设置
void gameInit();
//更新窗口
void updateWindow();
//背景透明
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);
int getDelay();
//用户点击
void userClick();
//判断文件是否存在
bool fileExist(const char* name);
//更新游戏窗口，使植物动起来
void updateGame();
//获取延迟时间，更新游戏窗口
int getDelay();
//游戏菜单
void startUI();


//从五十八行及以下为jackey制作僵尸形成和行走
struct zm
{
	int x, y;
	int frameIndex;
	bool used;
	int speed;
};
struct zm zms[10];
IMAGE imgZM[22];