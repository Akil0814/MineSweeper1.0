#pragma once
#include<stdio.h>
#include<graphics.h>
#include<stdio.h>
#include <time.h>
#include <windows.h>

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2

int Sum_of_mine = 15;
int Num_of_cover = (ROW * COL)-Sum_of_mine;
char mine[ROWS][COLS] = { 0 };//����׵���Ϣ
char show[ROWS][COLS] = { 0 };//ǰ̨��Ⱦ��Ϣ  0δ��� 5��ǵ��� 9�Լ��
int mine_find = 0;//�ɹ���ǵĵ���
int mine_num = 0;//��ǵ�����
int flage = 0;

int WINDOW_WIDTH = ROW * 50;
int WINDOW_HEIGHT = COL * 50;
int fps = 30;

bool setup = true;
bool game_start = false;
bool all_mine_find = false;
bool mine_explode = false;

ExMessage msg;
IMAGE Mine;
IMAGE MineCover;
IMAGE Num1;
IMAGE Num2;
IMAGE Num3;
IMAGE Num4;
IMAGE Num5;
IMAGE Num6;
IMAGE Num7;
IMAGE Num8;
IMAGE Base;
IMAGE MineMarked;
IMAGE MineFined;
IMAGE MineBace;//test

void CheckMine(char board[ROWS][COLS], int x, int y);