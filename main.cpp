#include"game.h"

void LoadResource()
{
	loadimage(&Mine, _T("res/Mine.png"));
	loadimage(&MineCover, _T("res/MineCover.png") );
	loadimage(&Num1, _T("res/Num1.png") );
	loadimage(&Num2, _T("res/Num2.png"));
	loadimage(&Num3, _T("res/Num3.png"));
	loadimage(&Num4, _T("res/Num4.png") );
	loadimage(&Num5, _T("res/Num5.png") );
	loadimage(&Num6, _T("res/Num6.png") );
	loadimage(&Num7, _T("res/Num7.png"));
	loadimage(&Num8, _T("res/Num8.png"));
	loadimage(&Base, _T("res/Base.png") );
	loadimage(&MineMarked, _T("res/MineMarked.png") );
	loadimage(&MineFined, _T("res/MineFined.png") );
	loadimage(&MineBace, _T("res/MineBace.png"));//test
}
//载入资源

void DrawTipText()//提示语句的输出
{
	static TCHAR str[32];
	_stprintf_s(str, _T("mine found:%d"), flage);
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}
//提示语句的输出

void ShowMine(char board[ROWS][COLS])//游戏结束时展示地雷
{
	int i = 0, j = 0;
	for (i = 1; i <= ROW; i++)
	{
		for (j = 1; j <= COL; j++)
		{
			if (mine[i][j] == 1 && show[i][j]==0)
			{
				putimage((i - 1) * 50, (j - 1) * 50, &Mine);//渲染未标记到的地雷图片
			}
			else if (mine[i][j] == 1 && show[i][j] == 5)
			{
				putimage((i - 1) * 50, (j - 1) * 50, &MineFined);//渲染标记到的地雷图片
			}
			mine_explode = true;//更改地雷爆炸为真
		}
	}
}
//游戏结束时展示地雷

void CheckWin()//检测胜利
{	
		if (mine_find == Sum_of_mine && mine_num == Sum_of_mine)//当 成功标记地雷数量 和 标记地雷数量 都等于地雷总数时
		{
			all_mine_find = true;//更改找到所有地雷为真
		}
		else if (Num_of_cover==0)
		{
			all_mine_find = true;
		}
}
//检测胜利

void IntBoard(char board[ROWS][COLS], int rows, int cols)//初始化棋盘
{
	int i, j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = 0;//将棋盘每处设定为0	
		}
	}
}
//初始化棋盘

void SetMine(char board[ROWS][COLS], int rows, int cols,int index_x,int index_y)//放置地雷
{
	int count = Sum_of_mine;//设置地雷数量
	int first_x = index_x;//引入第一次点击位置信息
	int	first_y = index_y;

	while (count)//随机设置地雷
	{
		int x = (rand() % ROW + 1);
		int y = (rand() % COL + 1);
		if (board[x][y] == 0 && (x != first_x || y != first_y))//当随机到的位置棋盘为空且不是第一次点击的位置时
		{
			board[x][y] = 1;//设置地雷为1
			count--;//减少地雷数量
		}
	}
}
//放置地雷

void DrawMineCover(char board[ROWS][COLS], int rows, int cols)//渲染游戏初始界面
{
	int i = 0, j = 0;
	for (i = 1; i <= ROW; i++)
	{
		for (j = 1; j <= COL; j++)
		{
			if (board[i][j] == 0)
			{
				putimage((i - 1) * 50, (j - 1) * 50, &MineCover);//遍历数组在所有未检测的位置绘制初始图片
			}
		}
	}
}
//渲染游戏初始界面

int GetMineCount(int x, int y)//计算周围地雷数量
{
	return	mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1] - 8 * 0;//计算周围8格地雷数量，返回数量
}
//计算周围地雷数量

void CheckAround(int x,int y)//检测检测点四周是否为空，对于数组的八个方向进行检测，若为空则继续检测
//以实现点击空白处时向四周衍生
{	
		x = x - 1;
		if (x <= ROW && y <= COL && x > 0 && y > 0) CheckMine(show, x, y);

		y = y - 1;
		if (x <= ROW && y <= COL && x > 0 && y > 0)	CheckMine(show, x, y);
		
		y = y + 2;
		if (x <= ROW && y <= COL && x > 0 && y > 0) CheckMine(show, x, y);
		
		x = x + 1;
		if (x <= ROW && y <= COL && x > 0 && y > 0) CheckMine(show, x, y);
		
		x = x + 1;
		if (x <= ROW && y <= COL && x > 0 && y > 0) CheckMine(show, x, y);
		
		y = y - 1;
		if (x <= ROW && y <= COL && x > 0 && y > 0)	CheckMine(show, x, y);
		
		y = y - 1;
		if (x <= ROW && y <= COL && x > 0 && y > 0) CheckMine(show, x, y);
		
		x = x - 1;
		if (x <= ROW && y <= COL && x > 0 && y > 0) CheckMine(show, x, y);
}
//检测四周是否为空

void FindMine(char board[ROWS][COLS])//标记地雷
{
	int x = msg.x;
	int y = msg.y;

	int index_x = (x / 50) + 1;
	int index_y = (y / 50) + 1;//调取鼠标信息转化为数组对于位置

	if(show[index_x][index_y] == 5)//当点击位置已被标记时
	{
		flage--;
		putimage((index_x - 1) * 50, (index_y - 1) * 50, &MineCover);//去除标记
		mine_num--;//减少标记地雷数量
		if (mine[index_x][index_y] == 1)//当点击位置有地雷时
		{
			//Num_of_cover++;
			mine_find--;//减少成功标记的地雷
			CheckWin();//检测是否胜利
		}
		CheckWin();//检测是否胜利
		show[index_x][index_y] = 0;//将目标位置设置为未被检测
	}
	else if (show[index_x][index_y] == 0 && flage< Sum_of_mine)//当点击位置未被标记时
	{
		putimage((index_x - 1) * 50, (index_y - 1) * 50, &MineMarked);//标记点击位置
		mine_num++;//增加已标记数
		flage++;
		if (mine[index_x][index_y] == 1)//当标记点为地雷时
		{	
			//Num_of_cover--;
			mine_find++;//增加成功标记的地雷数量
			CheckWin();//检测是否胜利
		}
		CheckWin();//检测是否胜利
		show[index_x][index_y] = 5;//将目标位置设置为标记地雷
	}
}
//标记地雷

void CheckMine(char board[ROWS][COLS],int x,int y)
{
	if (mine[x][y] == 0&& show[x][y] ==0)//当点击位置没有地雷，且未被检测时
	{
		show[x][y] = 9;//更改检测数据为已检测
		Num_of_cover--;
		int num = (GetMineCount(x,y));//调取周围地雷数量
		if (num > 0)//当周围有地雷时
		{
			switch (num)//输出对应数量的图片
			{
			case 1:
				putimage((x - 1) * 50, (y - 1) * 50, &Num1);
				break;
			case 2:
				putimage((x - 1) * 50, (y - 1) * 50, &Num2);
				break;
			case 3:
				putimage((x - 1) * 50, (y - 1) * 50, &Num3);
				break;
			case 4:
				putimage((x - 1) * 50, (y - 1) * 50, &Num4);
				break;
			case 5:
				putimage((x - 1) * 50, (y - 1) * 50, &Num5);
				break;
			case 6:
				putimage((x - 1) * 50, (y - 1) * 50, &Num6);
				break;
			case 7:
				putimage((x - 1) * 50, (y - 1) * 50, &Num7);
				break;
			case 8:
				putimage((x - 1) * 50, (y - 1) * 50, &Num8);
				break;
			default:
				break;
			}	
		}
		else if (num == 0)//当周围没有雷时
		{
			putimage((x - 1) * 50, (y - 1) * 50, &Base);//输出空图片
			CheckAround(x, y);//检测四周是否为空
		}
	}
	if(mine[x][y] == 1 && show[x][y] == 0)//当点击位置处于未被检测状态且有地雷时
	{
		ShowMine(mine);//展示地雷 游戏结束
	}
}
//检测地雷

void FirstClick(char board[ROWS][COLS], int rows, int cols)//首次点击排雷
{
	while(setup)
	{
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)//鼠标信息调取
			{
				int x = msg.x;
				int y = msg.y;
				int index_x = (x / 50) + 1;
				int index_y = (y / 50) + 1;
				SetMine(mine, ROWS, COLS, index_x, index_y);//设置地雷//调取第一次点击的位置
				game_start = true;//进入游戏主循环
				setup = false;//结束准备工作
				CheckMine(show, index_x, index_y);//检测首次点击位置附近地雷数量
				show[index_x][index_y] = 9;//将首次点击位置设定为以检测
			}
		}
	}
}
//首次点击排雷

void Menu()
{
	int a = 0;
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//输出窗口
}
//菜单选项

int main()
{

	srand((unsigned int)time(NULL));//初始化随机数

	Menu();//进入菜单
	LoadResource();//载入资源
	IntBoard(mine, ROWS, COLS);//初始化保存地雷数据的棋盘
	IntBoard(show, ROW, COL);//初始化保存检测数据的棋盘
	DrawMineCover(show, ROW, COL);//渲染初始界面
	FirstClick(mine, ROWS, COLS);//对首次点击进行初始化
	while (game_start)//初始化完成后进入主循环
	{
		DWORD start_time = GetTickCount();
		FlushBatchDraw();
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)//鼠标信息调取
			{
				int x = msg.x;
				int y = msg.y;
				int index_x = (x / 50) + 1;
				int index_y = (y / 50) + 1;
				CheckMine(mine, index_x, index_y);//检测点击位置是否有地雷

			}
			if (msg.message == WM_RBUTTONDOWN)//鼠标信息调取
			{
				int x = msg.x;
				int y = msg.y;
				int index_x = (x / 50) + 1;
				int index_y = (y / 50) + 1;
				if (show[index_x][index_y] != 9)//若点击位置不是已检测位置
				{
					FindMine(show);//标记地雷
				}
			}
		}
		CheckWin();
		DrawTipText();
		if (all_mine_find)//找到所有地雷
		{
			MessageBox(GetHWnd(), _T("Mine find"), _T("game end"), MB_OK);
			game_start = false;
		}
		else if (mine_explode)//地雷爆炸
		{
			MessageBox(GetHWnd(), _T("Mine explode"), _T("game end"), MB_OK);
			game_start = false;
		}

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / ((unsigned int)fps))//程序循环的优化
		{
			Sleep(1000 / fps - delta_time);
		}
	}

	EndBatchDraw();

	closegraph();

	return 0;
}