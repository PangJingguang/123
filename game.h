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
	IMAGE img;//�ɻ���ͼ
	int owner;//ӵ����ܷɻ�������˭
	int number;//��ܷɻ��ı��
	int x, y;//��������
	int position;//��������
public:
	Plane();
	Plane(int _owner, int _number);//һ��ʼҪ�ѷɻ��ŵ�����ȥ
	void Show();//�ѷɻ���ʾ����
	void Move(int step,Game game);//���ѡ��ɻ�֮�� �ƶ�
	void LoadSet(int pos);//��ȡ��Ϸ  ���ú���
	friend
		class Menu;//������ԪMenu��������Ϸ����ȡ��Ϸ�������ȡowner_number_x_y�ĸ�ֵ,һ��16��
};

class Player {
	int number;//��ұ��
	int step;//���ҡɫ�ӻ�õĵ���
	bool ai;//1 �ǵ��� 0 �����
	int DiceShow();//ҡɫ�ӵĶ���-----------------------------
public:	
	
	Player();
	Player(int _number,bool _ai);
	Plane aircarft[5];//һ����ӵ��4�ܷɻ� Ϊ�˷������ ����5�� ����aircarft[0]����
	int Dice();//ҡɫ��---------------------------

	void AI();//�˻�����
};

class Game {
	  
	IMAGE status;//����طŵ�ͼƬ
public:
	int ai_number;//����������
	Game();
	void Init();//��Ϸ��ʼ��
	Player player[5];//�ĸ���� Ϊ�˷������ ����5���� ����player[0]����
	void GameShow();//ר��Ϊ�ط����Ľӿ�----------
	void Block();//����·��
};

class Menu { //�˵�
	
	fstream S_L;//�ļ��Ķ�ȡ
public:
	stack<Game> CB;//���ڻط�
	void PlayBack();//�ط�
	Menu();//һ��ʼҪ��ȡ�ļ�����ʼ��ջ
	void SaveStates(Game S_game,int t);//������Ϸ
	Game LoadStates(int t);//��ȡ��Ϸ
};


class Mouse {//����������¼��Ĵ���
	MOUSEMSG msg;
	bool Judge(int x1, int x2, int y1, int y2, bool add);//�ж��Ƿ���������
public:
	int Start();//��ʼ����ĵ���¼�-----------------------
	int PlayNum();
	int Login();//��ȡ��Ϸ�ĵ���¼�
	void Dice();//�������ɫ��----------------
	int Running();//��Ϸ��ʼ֮��ĵ���¼�
	void PlayBack();//�ط�ʱ�Ľ���

	/*����ϵ������(�������ݾ�X50)
		6,6-9,9			ɫ�� 
		1,1-3,3			���4
		12,1-14,3		���1
		1,12-3,14		���2
		12,12-14,14		���3
		16,3-19,4		�ط� 
		16,6-19,7		����
		16,9-19,10		��ȡ
		16,12-19,14		�˳�
		-------�ط�״̬
		16,0-20,6       ��һ��
		16,8-20,14		�ص���Ϸ
		-------����
		��Ч
	*/
};




void Initialization();//��ʼ�� �������ӡ�����֮��� 
#endif