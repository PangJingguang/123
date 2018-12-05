#include "game.h"
extern const char* IMG_PLANE[5];
extern const char* IMG_GAME[6];
extern const char* IMG_EXC;
extern const char* IMG_DICE[7];
extern const char* FILENAME[4];
extern bool SAVE[4];
 const int END[5] = { 999,1,14,27,40};//各个玩家的终点
 const int BEGIN[5] = { 999,1+3,14+3,27+3,40+3 };//各个玩家的起点
 const int FLY[5] = { 999,1+20,14+20,27+20,(40+20)%52 };//各个玩家的飞行点
const int _GREEN = 1, _BLUE = 2, _RED = 3, _YELLOW = 4;
extern const int HOME = -10, READY = 0, COM = -100;
 int map_x[1+52+16+4+6*4], map_y[1+52+16+4+6*4],map_color[1 + 52 + 6 * 4 + 20];//保存格子的坐标
extern IMAGE exc;//动画
extern IMAGE background;

extern Mouse mouse;
extern Menu menu;
extern Game exgame;

Game::Game() {
	ai_number = -1;
}
void Game::Init() {
	for (int i = 1; i <= 4; i++) {
		bool _ai = (i >ai_number ? true : false);
		Player play(i, _ai);
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
	can_move = 0;
}

Player::Player(int _number, bool _ai) :number(_number), ai(_ai) {
	can_move = 0;
}

int Player::Dice() {
	IMAGE img_dice;
	saveimage(IMG_EXC);
	loadimage(&exc, IMG_EXC);
	putimage(0, 0, &exc);
	loadimage(&img_dice, IMG_DICE[0]);
	putimage(300, 300, &img_dice);
	if (ai) {
		Sleep(2000);
		
	}
	else {
		if (mouse.Dice() == 1)
			;
		else if (mouse.Dice() == 2)
			menu.PlayBack();
		else if (mouse.Dice() == 3)
			menu.SaveStates();
		else if (mouse.Dice() == 4)
			menu.LoadStates();
	}
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

bool Player::AI() {
	if (!ai)
		return false;
	return true;
}




























void Plane::MoveShow(int target_position,int spec,int delay) {
	int t_x = map_x[target_position] - x;
	int t_y = map_y[target_position] - y;
	for (int i = 1; i <= spec; i++) {
		putimage(0, 0, &exc);//把背景放上去
		x += (t_x / spec);
		y += (t_y / spec);
		Show();//飞机移动
		Sleep(delay);
	}
}

void Plane::XYChangeHelper(int target_position){
	x = map_x[target_position];
	y = map_y[target_position];
}

Plane::Plane() {
	;
}
Plane::Plane(int _owner, int _number) :owner(_owner), number(_number) {
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
	position = -10;
	Show();
}
void Plane::Show() {
	putimage(x, y, &img);
}
int Plane::Move(int step, Game game) {
	if(step == 6 && position == HOME) {
		IMAGE _mov;
		loadimage(&background, IMG_GAME[4]);
		putimage(0, 0, &background);
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (i != owner || j != number) {
					game.player[i].aircarft[j].Show();
				}
			}
		}
		loadimage(&_mov, IMG_DICE[step]);
		putimage(300, 300, &_mov);
		saveimage(IMG_EXC);
		loadimage(&exc, IMG_EXC);
		int jump = 52 + 16 + owner;
		MoveShow(jump, 10, 20);
		position = 0;
		XYChangeHelper(jump);
		return 1;
	}

	else {
		IMAGE _mov;
		loadimage(&background, IMG_GAME[4]);
		putimage(0, 0, &background);
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (i != owner || j != number) {
					game.player[i].aircarft[j].Show();
				}
			}
		}
		
		loadimage(&_mov, IMG_DICE[step]);
		putimage(300, 300, &_mov);
		saveimage(IMG_EXC);
		loadimage(&exc, IMG_EXC);
		if (!position) {//飞机处于准备中
			MoveShow(BEGIN[owner], 10, 10);
			position = BEGIN[owner];
			step--;
		}
		for (int i = 0; i <= step; i++) {
			if (position > 52 + 16 + 4) {
				int t;
				if (position + i > 52 + 16 + 4 + 6 * owner) 
					t = 6 - (position+i-(52 + 16 + 4 + 6 * owner));
				else
					t = i;
				MoveShow(position + t, 50, 2);
				XYChangeHelper(position + t);
				Show();//飞机移动
				Sleep(500);
				continue;
			}
			if (position + i > 52 && position + i < 52 + 16 + 4)
				position = -i + 1;
			if (position + i - 1 == END[owner]&&position<52+16) {
				position = 52 + 16 + 4 + (6 * (owner - 1) + 1);
				step -= i;
				i = 0;
			}
			
			MoveShow(position + i, 50, 2);
			XYChangeHelper(position + i);
			Show();//飞机移动
			Sleep(500);
		}
		position += step;
		if (position == 52 + 16 + 4 + 6 * owner) {
			position = -100;
			MoveShow(0, 500,2);
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
			
			Show();
		}
		if (position != END[owner] && owner == map_color[position]) {
			int jump;
			if (position == FLY[owner])
				jump = position + (3 * 4);
			else
				jump = position + 1 * 4;
			if (jump > 52)
				jump %= 52;
			MoveShow(jump,50,20);
			position = jump;
		}
		Sleep(1000);
		if (position == FLY[owner]) {
			int jump = position + (3 * 4);
			MoveShow(jump,50,20);
			position = jump;
		}
		XYChangeHelper(position);
		return 2;
	}
}
void Plane::LoadSet(int pos) {
	position = pos;
	x = map_x[position];
	y = map_x[position];
}



















Menu::Menu() {
	S_L.open("save");
}

void Menu::SaveStates() {
	Game S_game=CB.top();
	int t=mouse.Save();
	S_L.open(FILENAME[t]);
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			S_L << S_game.player[i].aircarft[j].number << endl;
		}
	}
}

void Menu::LoadStates() {
	loadimage(&background, IMG_GAME[1]);
	putimage(0, 0, &background);
	int t = mouse.Login();

	if (SAVE[t]) {
		loadimage(NULL, "empty.jpg");
		Sleep(2000);
		exgame.ai_number = -1;
		return ;
	}
	if (t == 4) {
		exgame.ai_number = -1;
		return ;
	}
	Sleep(3000);
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
			exgame.player[i].aircarft[j] = air;
		}
	}
	return ;
}

void Menu::PlayBack() {
	stack<Game> PB=CB;
	while (1) {
		int _mouse_opera = mouse.PlayBack();
		if (_mouse_opera == 1) {
			PB.top().GameShow();
			PB.pop();
		}
		else
			break;
	}
}























bool Mouse::Judge(int x1, int x2, int y1, int y2, bool add) {
	if ((msg.x / 50 > x1 && msg.x / 50 < x2) && (msg.y / 50 > y1 && msg.y / 50 < y2) && add)
		return true;
	return false;
}

int Mouse::Start() {//5,7-14,10 新游戏   5 ,11-17,14 继续游戏
	while (1) {
		msg = GetMouseMsg();
		if (Judge(5, 14, 7, 10, msg.mkLButton))
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

int Mouse::Dice() {
	while (1) {
		msg = GetMouseMsg();
		if (Judge(6, 9, 6, 9, msg.mkLButton))
			return 1;
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

int Mouse::PlayBack() {
	return 1;
}

int Mouse::Save(){
	return 0;
}










void Initialization() {
	Game res;
	for (int i = 1; i <= 3; i++) {
		fstream fp;
		fp.open(FILENAME[i]);
		SAVE[i] = fp.eof()? false:true;
	}
	//初始化每个方框对应的坐标  （左上角坐标）
	int num, _x, _y, sum, spec;
	//-------------四行
	for (int m = 1; m <= 4; m++) {
		switch (m)
		{
		case 1:num = 50; _x = 200; _y = 0; sum =7; spec = 1; break;
		case 2:num = 43; _x = 0; _y = 200; sum = 8; spec = 8; break;
		case 3:num = 17; _x = 700; _y = 500; sum = 8; spec = 34; break;
		case 4:num = 24; _x = 500; _y = 700; sum = 7; spec = 27; break;
		default:
			break;
		}
		for (int i = 0; i < sum; i++) {
			if (i == sum / 2) {
				num = spec;
				if (m == 2)
					_x += 350;
				else if (m == 3)
					_x -= 350;
			}
				
			map_x[num] = _x + (m < 3 ? i : -i) * 50;
			map_y[num] = _y;
			num++;
		}
	}
	//-------------四列
	for (int m = 1; m <= 4; m++) {
		switch (m)
		{
		case 1:num = 37; _x = 0; _y = 500; sum = 7; spec = 40; break;
		case 2:num = 30; _x = 200; _y = 700; sum = 8; spec = 47; break;
		case 3:num = 4; _x = 500; _y = 0; sum = 8; spec = 21; break;
		case 4:num = 11; _x = 700; _y = 200; sum = 7; spec = 14; break;
		default:
			break;
		}
		for (int i = 0; i < sum; i++) {
			if (i == sum / 2) {
				if (m == 2)
					_y -= 350;
				else if(m==3)
					_y += 350;
				num = spec;
			}
			map_x[num] = _x;
			map_y[num] = _y + (m < 3 ? -i : i) * 50;
			num++;
		}
	}
	map_x[52 + 16 + 1] = 11*50;
	map_y[52 + 16 + 1] = 0*50;
	map_x[52 + 16 + 2] = 14*50;
	map_y[52 + 16 + 2] = 11*50;
	map_x[52 + 16 + 3] = 3*50;
	map_y[52 + 16 + 3] = 14*50;
	map_x[52 + 16 + 4] = 0*50;
	map_y[52 + 16 + 4] = 3*50;
	for (int i = 1; i <= 4; i++) {
		switch (i)
		{
		case 1:
			for (int j = 1; j <= 6; j++) {
				map_x[52 + 16 + 4 + j + (i - 1) * 6] =7*50 ;
				map_y[52 + 16 + 4 + j + (i - 1) * 6] =0 +50 * j;
			}break;
		case 2:
			for (int j = 1; j <= 6; j++) {
				map_x[52 + 16 + 4 + j + (i - 1) * 6] =14*50 -50 * j;
				map_y[52 + 16 + 4 + j + (i - 1) * 6] =7*50 ;
			}break;
		case 3:
			for (int j = 1; j <= 6; j++) {
				map_x[52 + 16 + 4 + j + (i - 1) * 6] =7*50 ;
				map_y[52 + 16 + 4 + j + (i - 1) * 6] =14*50 -50 * j;
			}break;
		case 4:
			for (int j = 1; j <= 6; j++) {
				map_x[52 + 16 + 4 + j + (i - 1) * 6] =0 +50 * j;
				map_y[52 + 16 + 4 + j + (i - 1) * 6] =7*50 ;
			}break;
		default:
			break;
		}
	}
	for (int i = 1; i <= 52; i++) {
		switch (i%4) {
		case 0:map_color[i] = _YELLOW; break;
		case 1:map_color[i] = _GREEN; break;
		case 2:map_color[i] = _BLUE; break;
		case 3:map_color[i] = _RED; break;
		default:
			break;
		}
	}
	//打开图片
	srand(time(0));//随机数种子

}
