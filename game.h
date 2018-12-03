#pragma once
#undef UNICODE
#undef _UNICODE
#include <fstream>
#include <stack>
#include <algorithm>
#include <conio.h>
#include <iostream>

#include <graphics.h>

using namespace std;


const char* IMG_PLANE[5] = { "棋盘.jpg", "飞机1.jpg","飞机2.jpg" ,"飞机3.jpg" ,"飞机4.jpg"};
const char* IMG_GAME[6] = { "开始.jpg","读取.jpg","选择.jpg","提示.jpg","棋盘.jpg", "回放.jpg" };
int map_x[53], map_y[53];

class Game {
	int ai_number;//机器人数量  
public:
	Game();//游戏初始化
	Player player[5];//四个玩家 为了方便计算 声明5个人 其中player[0]作废
};

class Player {
	int number;//玩家编号
	int step;//玩家摇色子获得的点数
public:
	Plane aircarft[5];//一个人拥有4架飞机 为了方便计算 声明5架 其中aircarft[0]作废
	int Dice();//摇色子
	void AI();//人机共玩
};

class Plane {
	IMAGE img;//飞机贴图
	int owner;//拥有这架飞机的人是谁
	int number;//这架飞机的编号
	int x, y;//像素坐标
public:
	Plane();
	Plane(int _owner, int _number);//一开始要把飞机放到基地去
	void Show();//把飞机显示出来
	void Move(int step);//玩家选择飞机之后 移动
};

class Menu { //菜单
	std::stack<Game> CB;
	std::fstream S_L;//文件的读取
public:
	Menu();//一开始要读取文件，初始化栈
	void SaveStates();//读取游戏
	void LoadStates();//保存游戏
	void PlayBack();//回放
};

void initialization();
int init_helper_H(int a, int b);
int init_helper_L(int a, int b);