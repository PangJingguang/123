#include "game.h"

Plane::Plane() {
	;
}
Plane::Plane(int _owner,int _number):owner(_owner),number(_number) {
	loadimage(&img, IMG_PLANE[owner]);
	switch (owner) {
	case 1:x = 50; y = 50; break;
	case 2:x = 600; y = 50; break;//       4    1
	case 3:x = 600; y = 600; break;
	case 4:x = 50; y = 600; break;//       3    2
	default:
		break;
	}
	switch (owner) {
	case 1:x += 0; y += 0; break;
	case 2:x += 50; y += 0; break;//           1    2
	case 3:x += 0; y += 50; break;
	case 4:x += 50; y += 50; break;//          3    4
	default:
		break;
	}
}
void Plane::Show() {
	putimage(x, y, &img);
}
void Plane::Move(int step) {
	
}

void initialization(){
//-------------四行
	for (int m = 1; m <= 4 ; m++) {
		int num,_x,_y,sum;
		switch (m)
		{
		case 1:num = 50; _x = 200; _y = 0; sum = 8; break;
		case 2:num = 43; _x = 0; _y = 200; sum = 7; break;
		case 3:num = 37; _x = 0; _y = 500; sum = 7; break;
		case 4:num = 30; _x = 200; _y = 700; sum = 8; break;
		default:
			break;
		}
		for (int i = 0; i < sum; i++) {
			map_x[num] = _x + i * 50;
			map_y[num] = _y;
		}
	}
//-------------四列
	for (int m = 1; m <= 4 ; m++) {
		int num,_x,_y;
		switch (m)
		{
		case 1:num = 43; _x = 0; _y = 200; break;
		case 2:num = 50; _x = 200; _y = 0; break;
		case 3:num = 4; _x = 500; _y = 0; break;
		case 4:num = 11; _x = 700; _y = 200; break;
		default:
			break;
		}

	}
}

int init_helper_H(int i,int a, int b) {//从小到大的情况
	return i > a ? b : i;
}
int init_helper_L(int i, int a, int b) {//从大到小的情况
	return i < a ? b : i;
}