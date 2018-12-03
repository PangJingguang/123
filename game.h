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


const char* IMG_PLANE[5] = { "����.jpg", "�ɻ�1.jpg","�ɻ�2.jpg" ,"�ɻ�3.jpg" ,"�ɻ�4.jpg"};
const char* IMG_GAME[6] = { "��ʼ.jpg","��ȡ.jpg","ѡ��.jpg","��ʾ.jpg","����.jpg", "�ط�.jpg" };
int map_x[53], map_y[53];

class Game {
	int ai_number;//����������  
public:
	Game();//��Ϸ��ʼ��
	Player player[5];//�ĸ���� Ϊ�˷������ ����5���� ����player[0]����
};

class Player {
	int number;//��ұ��
	int step;//���ҡɫ�ӻ�õĵ���
public:
	Plane aircarft[5];//һ����ӵ��4�ܷɻ� Ϊ�˷������ ����5�� ����aircarft[0]����
	int Dice();//ҡɫ��
	void AI();//�˻�����
};

class Plane {
	IMAGE img;//�ɻ���ͼ
	int owner;//ӵ����ܷɻ�������˭
	int number;//��ܷɻ��ı��
	int x, y;//��������
public:
	Plane();
	Plane(int _owner, int _number);//һ��ʼҪ�ѷɻ��ŵ�����ȥ
	void Show();//�ѷɻ���ʾ����
	void Move(int step);//���ѡ��ɻ�֮�� �ƶ�
};

class Menu { //�˵�
	std::stack<Game> CB;
	std::fstream S_L;//�ļ��Ķ�ȡ
public:
	Menu();//һ��ʼҪ��ȡ�ļ�����ʼ��ջ
	void SaveStates();//��ȡ��Ϸ
	void LoadStates();//������Ϸ
	void PlayBack();//�ط�
};

void initialization();
int init_helper_H(int a, int b);
int init_helper_L(int a, int b);