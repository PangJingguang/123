
#include "game.h"
const int 棋盘 = 5;
const char* IMG_PLANE[5] = { "棋盘.jpg", "飞机1.jpg","飞机2.jpg" ,"飞机3.jpg" ,"飞机4.jpg" };
const char* IMG_GAME[6] = { "开始.jpg","读取.jpg","选择.jpg","提示.jpg","棋盘.jpg", "回放.jpg" };
const char* IMG_EXC = "exc.jpg";
const char* IMG_DICE[7] = { "dice0.png","dice1.png","dice2.png","dice3.png","dice4.png","dice5.png","dice6.png" };
const char* FILENAME[4] = { "save1","save1","save2","save3" };
bool SAVE[4];
const int END[5] = { 999,1,14,27,40 };//各个玩家的终点
const int HOME = -1, READY = 0;
int map_x[53], map_y[53];//保存格子的坐标
IMAGE exc;//动画
IMAGE background,dice_img;

Mouse mouse;
Menu menu;
int main()
{
	Game game;
	initgraph(1000, 750);//初始化游戏窗口
	Initialization();
	while (game.ai_number<0) {//游戏初始化
		loadimage(&background, IMG_GAME[0]);//生成背景图
		putimage(0, 0, &background);
		int _mouse_opera = mouse.Start();
		if (_mouse_opera) {
			loadimage(&background, IMG_GAME[2]);
			putimage(0, 0, &background);
			_mouse_opera = mouse.PlayNum();
			game.ai_number = _mouse_opera;
			loadimage(&background, IMG_GAME[4]);
			putimage(0, 0, &background);//游戏正式开始
		}
		else {//存档界面
			loadimage(&background, IMG_GAME[1]);
			putimage(0, 0, &background);
			_mouse_opera = mouse.Login();
			if (_mouse_opera == 4)
				;
			else if (SAVE[_mouse_opera])
				game = menu.LoadStates(_mouse_opera);
			else {
				loadimage(NULL, "empty.jpg");
				Sleep(2000);
			}
		}
	}
	game.Init();
	menu.CB.push(game);
	while (1) {
		for (int i = 1; i <= 4; i++) {
			int step=game.player[i].Dice();
			int sel=mouse.Running();
			game.player[i].aircarft[sel].Move(step,game);
			Sleep(1000);
		}
	}
	getch();
}