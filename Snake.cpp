#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>//��ֹ����
#include<graphics.h>
#include<conio.h>//getch
#include<time.h>//�����������
#include<mmsystem.h>//ý�����
#pragma comment(lib,"winmm.lib")
using namespace std;
typedef struct PointXY {
	int x;
	int y;
}Mypoint;
struct Snake {
	int num; //����
	Mypoint xy[100]; //����
	char position;  //����
}snake;
struct Food {
	Mypoint fdxy; //ʳ������
	int eatgrade=0; //����
	int flag=1; //�Ƿ����
}food;
//ö�ٷ���
int a = 100;//����ֵ
enum moxPos{right=77,left=75,down=80,up=72};//С����ֵ
HWND hwnd = NULL;//ͼ��
void initSnake();
void drawSnake();
void moveSnake();
void keyDown();
void initFood();
void drawFood();
void eatFood();
int snakeDie();
void showGrade();
void pauseMoment();

int main() {
	srand((unsigned int)time(NULL));//�����������
	hwnd = initgraph(640, 480);
	setbkcolor(WHITE);
	mciSendString("close maomi.mp3", 0, 0, 0);
	mciSendString("open maomi.mp3", 0, 0, 0);
	mciSendString("play maomi.mp3", 0, 0, 0);
	while (1) {
		initSnake();
		initFood();
		while (1) {
			for (int i = 0; i < 2; i++) system("cls");
			cleardevice();
			if (food.flag == 0) {
				initFood();
			}
			drawFood();
			drawSnake();
			showGrade();
			eatFood();
			moveSnake();
			while (_kbhit()) {
				pauseMoment();
				keyDown();
			}
			if (snakeDie()) {
				break;
			}
			Sleep(a);
		}
		while (_getch() != 32);
		a = 100;
		food.eatgrade = 0;
	}
	getchar();//��ֹ����
	closegraph();
	return 0;
}

void initSnake(){
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 20;
	snake.xy[1].y = 0;

	snake.xy[0].x = 40;
	snake.xy[0].y = 0;

	snake.num = 3;
	snake.position = right;
}
void drawSnake() {
	IMAGE Right,Left,Down,Up;
	loadimage(&Right, "right.jpg");
	loadimage(&Left, "left.jpg");
	loadimage(&Down, "down.jpg");
	loadimage(&Up, "up.jpg");
	switch (snake.position) {
	case right:putimage(snake.xy[0].x, snake.xy[0].y, &Right);
		break;
	case left:putimage(snake.xy[0].x, snake.xy[0].y, &Left);
		break;
	case down:putimage(snake.xy[0].x, snake.xy[0].y, &Down);
		break;
	case up:putimage(snake.xy[0].x, snake.xy[0].y, &Up);
		break;
	default:
		break;
	}
	for (int i = 1; i < snake.num; i++) {
		setlinecolor(BLACK);//�߿���ɫ
		setfillcolor(GREEN); //(RGB(rand() % 255, rand() % 255, rand() % 255));//���ɫ
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x+20, snake.xy[i].y+20);
	}
}
void moveSnake() {
	for (int i = snake.num-1; i > 0; i--) {
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	switch (snake.position) {
	case right:snake.xy[0].x += 20;
		break;
	case left:snake.xy[0].x -= 20;
		break;
	case down:snake.xy[0].y += 20;
		break;
	case up:snake.xy[0].y -= 20;
		break;
	default:
		break;
	}
}
void keyDown() {
	char userKey = 0;
	userKey = _getch();
	switch (userKey) {
	case right:
		if (snake.position != right && snake.position != left) snake.position = right;
		break;
	case left:
		if(snake.position != right && snake.position != left) snake.position = left;
		break;
	case down:
		if (snake.position != up && snake.position != down) snake.position = down;
		break;
	case up:
		if (snake.position != up && snake.position != down) snake.position = up;
		break;
	default:
		break;
	}
}
void initFood() {
	food.fdxy.x = rand()%32*20;
	food.fdxy.y = rand()%24*20;
	food.flag = 1;
}
void drawFood() {
	IMAGE shit;
	loadimage(&shit, "shit.jpg");
	putimage(food.fdxy.x, food.fdxy.y, &shit);
}
void eatFood() {
	if (snake.xy[0].x == food.fdxy.x && snake.xy[0].y == food.fdxy.y) {
		snake.num++;
		food.flag = 0;
		food.eatgrade += 10;
		mciSendString("close eatshit.mp3", 0, 0, 0);
		mciSendString("open eatshit.mp3", 0, 0, 0);
		mciSendString("play eatshit.mp3", 0, 0, 0);
		if(a>=10)a -= 10;
	}
}
void showGrade() {
	char grade[100] = "";
	sprintf(grade, "%d", food.eatgrade);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	outtextxy(570, 20,"����");
	outtextxy(610, 20, grade);
	outtextxy(400, 450, "100��=���֣�150��=����");
}
int snakeDie() {
	if (snake.xy[0].x > 639 || snake.xy[0].x < 0 || snake.xy[0].y >479 || snake.xy[0].y < 0) {
		outtextxy(250, 200, "���ո����¿�ʼ");
		MessageBox(hwnd, "Gameover","ײǽ�ˣ�",MB_OK);
		return 1;
	}
	for (int i = 1; i < snake.num; i++) {
		if (snake.xy[0].x == snake.xy[i].x&& snake.xy[0].y == snake.xy[i].y) {
			outtextxy(250, 200, "���ո����¿�ʼ");
			MessageBox(hwnd, "Gameover", "ҧ���Լ�β���ˣ�", MB_OK);
			return 1;
		}
	}
	return 0;
}
void pauseMoment() {
	if (_getch() == 32) {
		while (_getch() != 32);
	}
}