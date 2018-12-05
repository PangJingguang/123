#include "game.h"
const char* IMG_PLANE[5] = { "棋盘.jpg", "飞机1.jpg","飞机2.jpg" ,"飞机3.jpg" ,"飞机4.jpg" };
const char* IMG_GAME[6] = { "开始.jpg","读取.jpg","选择.jpg","提示.jpg","棋盘.jpg", "回放.jpg" };
const char* IMG_EXC = "exc.jpg";
const char* IMG_DICE[7] = { "dice0.jpg","dice1.jpg","dice2.jpg","dice3.jpg","dice4.jpg","dice5.jpg","dice6.jpg" };
const char* FILENAME[4] = { "save1.txt","save1.txt","save2.txt","save3.txt" };
bool SAVE[4];
IMAGE exc;//动画
IMAGE background, dice_img;

Mouse mouse;
Menu menu;
Game exgame;
int main()
{
	Game game;
	initgraph(1000, 750);//初始化游戏窗口

	Initialization();
	while (game.ai_number < 0) {//游戏初始化
		loadimage(&background, IMG_GAME[0]);//生成背景图
		putimage(0, 0, &background);
		int _mouse_opera = mouse.Start();//
		if (_mouse_opera) {
			loadimage(&background, IMG_GAME[2]);
			putimage(0, 0, &background);
			_mouse_opera = mouse.PlayNum();
			game.ai_number = _mouse_opera;
			loadimage(&background, IMG_GAME[4]);
			putimage(0, 0, &background);//游戏正式开始
		}
		else {//存档界面
			menu.LoadStates();
			game = exgame;
		}
	}
	game.Init();
	Sleep(2000);
	menu.CB.push(game);
	while (1) {
		for (int i =2; i <= 2; i++) {
			int step = game.player[i].Dice();
			step = 6;
			if (step != 6 && !game.player[i].can_move)
				;
			else if(!game.player[i].AI()) {
				int sel,_move;
				sel = mouse.Running();
				_move = game.player[i].aircarft[sel].Move(step, game);
				if (_move== 1)
					game.player[i].can_move++;
				else if (_move== 2)
					;
				else
					game.player[i].can_move--;
			}
			Sleep(1000);
		}

	}
	//for (int i = 1; i <= 52; i++)
	//	cout << map_x[i] << ' ' << map_y[i]<<"\t"<<i << endl;
	//_getch();1+52+16+4+6*4
	return 0;
}
