#ifndef GAME_H_FILE
#define GAME_H_FILE
#undef UNICODE
#undef _UNICODE
#include <graphics.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <conio.h>
#include <iostream>
#include <time.h>


using namespace std;
class Game;




class Plane {
	IMAGE img;//飞机贴图
	int owner;//拥有这架飞机的人是谁
	int number;//这架飞机的编号
	int x, y;//像素坐标
	int position;//格子坐标
public:
	Plane();
	Plane(int _owner, int _number);//一开始要把飞机放到基地去
	void Show();//把飞机显示出来
	void Move(int step,Game game);//玩家选择飞机之后 移动
	void LoadSet(int pos);//读取游戏  设置函数
	friend
		class Menu;//设置友元Menu，保存游戏、读取游戏即保存读取owner_number_x_y四个值,一共16行
};

class Player {
	int number;//玩家编号
	int step;//玩家摇色子获得的点数
	bool ai;//1 是电脑 0 是玩家
	int DiceShow();//摇色子的动画-----------------------------
public:	
	
	Player();
	Player(int _number,bool _ai);
	Plane aircarft[5];//一个人拥有4架飞机 为了方便计算 声明5架 其中aircarft[0]作废
	int Dice();//摇色子---------------------------

	void AI();//人机共玩
};

class Game {
	  
	IMAGE status;//保存回放的图片
public:
	int ai_number;//机器人数量
	Game();
	void Init();//游戏初始化
	Player player[5];//四个玩家 为了方便计算 声明5个人 其中player[0]作废
	void GameShow();//专门为回放做的接口----------
	void Block();//生成路障
};

class Menu { //菜单
	
	fstream S_L;//文件的读取
public:
	stack<Game> CB;//用于回放
	void PlayBack();//回放
	Menu();//一开始要读取文件，初始化栈
	void SaveStates(Game S_game,int t);//保存游戏
	Game LoadStates(int t);//读取游戏
};


class Mouse {//对于鼠标点击事件的处理
	MOUSEMSG msg;
	bool Judge(int x1, int x2, int y1, int y2, bool add);//判断是否在区域内
public:
	int Start();//开始界面的点击事件-----------------------
	int PlayNum();
	int Login();//读取游戏的点击事件
	void Dice();//鼠标点击掷色子----------------
	int Running();//游戏开始之后的点击事件
	void PlayBack();//回放时的界面

	/*坐标系标明：(以下数据均X50)
		6,6-9,9			色子 
		1,1-3,3			玩家4
		12,1-14,3		玩家1
		1,12-3,14		玩家2
		12,12-14,14		玩家3
		16,3-19,4		回放 
		16,6-19,7		保存
		16,9-19,10		读取
		16,12-19,14		退出
		-------回放状态
		16,0-20,6       上一步
		16,8-20,14		回到游戏
		-------其他
		无效
	*/
};




void Initialization();//初始化 包括格子、窗口之类的 
#endif