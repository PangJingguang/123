#include "game.h"
extern const char* IMG_PLANE[5];
extern const char* IMG_GAME[6];
extern const char* IMG_EXC;
extern const char* IMG_DICE[7] ;
extern const char* FILENAME[4] ;
extern bool SAVE[4];
extern const int END[5] = { 999,1,14,27,40 };//各个玩家的终点
extern const int HOME = -1, READY = 0;
extern int map_x[53], map_y[53];//保存格子的坐标
extern IMAGE exc;//动画
extern IMAGE background;

extern Mouse mouse;
extern Menu menu;

Game::Game() {
	ai_number=-1;
}
void Game::Init(){
	for (int i = 1; i <= 4; i++) {
		bool _ai=(i>4-ai_number?true:false);
		Player play(i,_ai);
		for (int j = 1; j <= 4; j++) {
			Plane plane(i, j);
			play.aircarft[j] = plane;
		}
		player[i] = play;
	}
	loadimage(&status, NULL);
}
void Game::GameShow() {
	putimage(0, 0, &status);
}

void Game::Block() {
}























Player::Player() {

}

Player::Player(int _number, bool _ai):number(_number),ai(ai){
}

int Player::Dice() {
	IMAGE img_dice;
	loadimage(&img_dice, IMG_DICE[0]);
	putimage(0, 0, &exc);
	putimage(300, 300, &img_dice);
	mouse.Dice();
	return DiceShow();
}

int Player::DiceShow() {
	IMAGE img_dice;
	int t;
	for (int i = 0; i < 10; i++) {
		t = rand() % 6 + 1;
		loadimage(&img_dice, IMG_DICE[t]);
		putimage(0, 0, &exc);
		putimage(300, 300, &img_dice);
		Sleep(50);
	}
	return t;
}

void Player::AI(){
}




























Plane::Plane() {
	;
}
Plane::Plane(int _owner,int _number):owner(_owner),number(_number) {
	loadimage(&img, IMG_PLANE[owner]);
	switch (owner) {
	case 1:x = 600; y = 50; break;
	case 2:x = 600; y = 600; break;//       4    1
	case 3:x = 50; y = 600; break;
	case 4:x = 50; y = 50; break;//       3    2
	default:
		break;
	}
	switch (number) {
	case 1:x += 0; y += 0; break;
	case 2:x += 50; y += 0; break;//           1    2
	case 3:x += 0; y += 50; break;
	case 4:x += 50; y += 50; break;//          3    4
	default:
		break;
	}
	position = -1;
	Show();
}
void Plane::Show() {
	putimage(x, y, &img);
}
void Plane::Move(int step,Game game) {
	putimage(0, 0, &background);
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (i != owner && j != number) {
				game.player[i].aircarft[j].Show();
			}
		}
	}
	saveimage(IMG_EXC,NULL);
	loadimage(&exc, IMG_EXC);
	for (int i = 0; i <= step; i++) {
		putimage(0, 0, &exc);//把背景放上去
		x = map_x[position + i];
		y = map_y[position + i];
		Show();//飞机移动
		Sleep(500);
	}
	position += step;
}
void Plane::LoadSet(int pos){
	position = pos;
	x = map_x[position];
	y = map_x[position];
}



















Menu::Menu() {
	S_L.open("save");
}

void Menu::SaveStates(Game S_game,int t) {
	S_L.open(FILENAME[t]);
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			S_L<< S_game.player[i].aircarft[j].number << endl;
		}
	}
}

Game Menu::LoadStates(int t) {
	Game game;
	S_L.open(FILENAME[t]);
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			char s[3];
			int i = 0, res = 0;
			S_L.getline(s, 3);
			while (1) {
				if (s[i] == '\0')
					break;
				res = res * 10 + (s[i] - '0');
			}
			Plane air(i, j);
			air.LoadSet(res);
			game.player[i].aircarft[j] = air;
		}
	}
	return game;
}

void Menu::PlayBack() {
}























bool Mouse::Judge(int x1, int x2, int y1, int y2, bool add){
	if((msg.x / 50 > x1 && msg.x / 50 < x2) && (msg.y / 50 > y1 && msg.y / 50 < y2)&&add)
	return true;
	return false;
}

int Mouse::Start(){//5,7-14,10 新游戏   5 ,11-17,14 继续游戏
	while (1) {
		msg = GetMouseMsg();
		if(Judge(5,14,7,10, msg.mkLButton))
			return 1; 
		else if (Judge(5, 17, 11, 14, msg.mkLButton))
			return 0;
	}

}

int Mouse::PlayNum()
{
	while (1) {
		msg = GetMouseMsg();
		if (Judge(1, 7, 4, 7, msg.mkLButton))
			return 1;
		else if (Judge(10, 15, 4, 7, msg.mkLButton))
			return 2;
		else if (Judge(1, 8, 9, 14, msg.mkLButton))
			return 3;
		else if (Judge(10, 17, 9, 12, msg.mkLButton))
			return 4;
	}
}

int Mouse::Login() {
	while (1) {
		msg = GetMouseMsg();
		if (Judge(1, 7, 4, 7, msg.mkLButton))
			return 1;
		else if (Judge(10, 15, 4, 7, msg.mkLButton))
			return 2;
		else if (Judge(1, 8, 9, 14, msg.mkLButton))
			return 3;
		else if (Judge(10, 17, 9, 12, msg.mkLButton))
			return 4;
	}
}

void Mouse::Dice(){
	while (1) {
		msg = GetMouseMsg(); 
		if (Judge(6,9, 6, 9, msg.mkLButton))
			return ;
	}

}

int Mouse::Running() {
	while (1) {
		msg = GetMouseMsg();
		if (Judge(1, 7, 4, 7, msg.mkLButton))
			return 1;
		else if (Judge(10, 15, 4, 7, msg.mkLButton))
			return 2;
		else if (Judge(1, 8, 9, 14, msg.mkLButton))
			return 3;
		else if (Judge(10, 17, 9, 12, msg.mkLButton))
			return 4;
	}
}

void Mouse::PlayBack() {
}










void Initialization() {
	Game res;
	/*for (int i = 1; i <= 4; i++) {
		fstream fp;
		fp.open(FILENAME[i]);
		SAVE[i] = fp.eof()? false:true;
	}*/
	//初始化每个方框对应的坐标  （左上角坐标）
	int num, _x, _y, sum, spec;
	//-------------四行
	for (int m = 1; m <= 4; m++) {
		switch (m)
		{
		case 1:num = 50; _x = 200; _y = 0; sum = 8; spec = 1; break;
		case 2:num = 43; _x = 0; _y = 200; sum = 7; spec = 8; break;
		case 3:num = 17; _x = 700; _y = 500; sum = 7; spec = 34; break;
		case 4:num = 24; _x = 500; _y = 700; sum = 8; spec = 27; break;
		default:
			break;
		}
		for (int i = 0; i < sum; i++) {
			if (i == sum / 2)
				num = spec;
			map_x[num] = _x + (m < 3 ? i : -i) * 50;
			map_y[num] = _y;
			num++;
		}
	}
	//-------------四列
	for (int m = 1; m <= 4; m++) {
		switch (m)
		{
		case 1:num = 37; _x = 0; _y = 200; sum = 7; spec = 40; break;
		case 2:num = 30; _x = 200; _y = 0; sum = 8; spec = 33; break;
		case 3:num = 4; _x = 500; _y = 0; sum = 8; spec = 21; break;
		case 4:num = 11; _x = 700; _y = 200; sum = 7; spec = 14; break;
		default:
			break;
		}
		for (int i = 0; i < sum; i++) {
			if (i == sum / 2)
				num = spec;
			map_x[num] = _x;
			map_y[num] = _y + (m < 3 ? i : -i) * 50;
			num++;
		}
	}

//打开图片
	srand(time(0));//随机数种子
	
}