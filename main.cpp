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
//������Դ

void DrawTipText()//��ʾ�������
{
	static TCHAR str[32];
	_stprintf_s(str, _T("mine found:%d"), flage);
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}
//��ʾ�������

void ShowMine(char board[ROWS][COLS])//��Ϸ����ʱչʾ����
{
	int i = 0, j = 0;
	for (i = 1; i <= ROW; i++)
	{
		for (j = 1; j <= COL; j++)
		{
			if (mine[i][j] == 1 && show[i][j]==0)
			{
				putimage((i - 1) * 50, (j - 1) * 50, &Mine);//��Ⱦδ��ǵ��ĵ���ͼƬ
			}
			else if (mine[i][j] == 1 && show[i][j] == 5)
			{
				putimage((i - 1) * 50, (j - 1) * 50, &MineFined);//��Ⱦ��ǵ��ĵ���ͼƬ
			}
			mine_explode = true;//���ĵ��ױ�ըΪ��
		}
	}
}
//��Ϸ����ʱչʾ����

void CheckWin()//���ʤ��
{	
		if (mine_find == Sum_of_mine && mine_num == Sum_of_mine)//�� �ɹ���ǵ������� �� ��ǵ������� �����ڵ�������ʱ
		{
			all_mine_find = true;//�����ҵ����е���Ϊ��
		}
		else if (Num_of_cover==0)
		{
			all_mine_find = true;
		}
}
//���ʤ��

void IntBoard(char board[ROWS][COLS], int rows, int cols)//��ʼ������
{
	int i, j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = 0;//������ÿ���趨Ϊ0	
		}
	}
}
//��ʼ������

void SetMine(char board[ROWS][COLS], int rows, int cols,int index_x,int index_y)//���õ���
{
	int count = Sum_of_mine;//���õ�������
	int first_x = index_x;//�����һ�ε��λ����Ϣ
	int	first_y = index_y;

	while (count)//������õ���
	{
		int x = (rand() % ROW + 1);
		int y = (rand() % COL + 1);
		if (board[x][y] == 0 && (x != first_x || y != first_y))//���������λ������Ϊ���Ҳ��ǵ�һ�ε����λ��ʱ
		{
			board[x][y] = 1;//���õ���Ϊ1
			count--;//���ٵ�������
		}
	}
}
//���õ���

void DrawMineCover(char board[ROWS][COLS], int rows, int cols)//��Ⱦ��Ϸ��ʼ����
{
	int i = 0, j = 0;
	for (i = 1; i <= ROW; i++)
	{
		for (j = 1; j <= COL; j++)
		{
			if (board[i][j] == 0)
			{
				putimage((i - 1) * 50, (j - 1) * 50, &MineCover);//��������������δ����λ�û��Ƴ�ʼͼƬ
			}
		}
	}
}
//��Ⱦ��Ϸ��ʼ����

int GetMineCount(int x, int y)//������Χ��������
{
	return	mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1] - 8 * 0;//������Χ8�������������������
}
//������Χ��������

void CheckAround(int x,int y)//�����������Ƿ�Ϊ�գ���������İ˸�������м�⣬��Ϊ����������
//��ʵ�ֵ���հ״�ʱ����������
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
//��������Ƿ�Ϊ��

void FindMine(char board[ROWS][COLS])//��ǵ���
{
	int x = msg.x;
	int y = msg.y;

	int index_x = (x / 50) + 1;
	int index_y = (y / 50) + 1;//��ȡ�����Ϣת��Ϊ�������λ��

	if(show[index_x][index_y] == 5)//�����λ���ѱ����ʱ
	{
		flage--;
		putimage((index_x - 1) * 50, (index_y - 1) * 50, &MineCover);//ȥ�����
		mine_num--;//���ٱ�ǵ�������
		if (mine[index_x][index_y] == 1)//�����λ���е���ʱ
		{
			//Num_of_cover++;
			mine_find--;//���ٳɹ���ǵĵ���
			CheckWin();//����Ƿ�ʤ��
		}
		CheckWin();//����Ƿ�ʤ��
		show[index_x][index_y] = 0;//��Ŀ��λ������Ϊδ�����
	}
	else if (show[index_x][index_y] == 0 && flage< Sum_of_mine)//�����λ��δ�����ʱ
	{
		putimage((index_x - 1) * 50, (index_y - 1) * 50, &MineMarked);//��ǵ��λ��
		mine_num++;//�����ѱ����
		flage++;
		if (mine[index_x][index_y] == 1)//����ǵ�Ϊ����ʱ
		{	
			//Num_of_cover--;
			mine_find++;//���ӳɹ���ǵĵ�������
			CheckWin();//����Ƿ�ʤ��
		}
		CheckWin();//����Ƿ�ʤ��
		show[index_x][index_y] = 5;//��Ŀ��λ������Ϊ��ǵ���
	}
}
//��ǵ���

void CheckMine(char board[ROWS][COLS],int x,int y)
{
	if (mine[x][y] == 0&& show[x][y] ==0)//�����λ��û�е��ף���δ�����ʱ
	{
		show[x][y] = 9;//���ļ������Ϊ�Ѽ��
		Num_of_cover--;
		int num = (GetMineCount(x,y));//��ȡ��Χ��������
		if (num > 0)//����Χ�е���ʱ
		{
			switch (num)//�����Ӧ������ͼƬ
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
		else if (num == 0)//����Χû����ʱ
		{
			putimage((x - 1) * 50, (y - 1) * 50, &Base);//�����ͼƬ
			CheckAround(x, y);//��������Ƿ�Ϊ��
		}
	}
	if(mine[x][y] == 1 && show[x][y] == 0)//�����λ�ô���δ�����״̬���е���ʱ
	{
		ShowMine(mine);//չʾ���� ��Ϸ����
	}
}
//������

void FirstClick(char board[ROWS][COLS], int rows, int cols)//�״ε������
{
	while(setup)
	{
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)//�����Ϣ��ȡ
			{
				int x = msg.x;
				int y = msg.y;
				int index_x = (x / 50) + 1;
				int index_y = (y / 50) + 1;
				SetMine(mine, ROWS, COLS, index_x, index_y);//���õ���//��ȡ��һ�ε����λ��
				game_start = true;//������Ϸ��ѭ��
				setup = false;//����׼������
				CheckMine(show, index_x, index_y);//����״ε��λ�ø�����������
				show[index_x][index_y] = 9;//���״ε��λ���趨Ϊ�Լ��
			}
		}
	}
}
//�״ε������

void Menu()
{
	int a = 0;
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//�������
}
//�˵�ѡ��

int main()
{

	srand((unsigned int)time(NULL));//��ʼ�������

	Menu();//����˵�
	LoadResource();//������Դ
	IntBoard(mine, ROWS, COLS);//��ʼ������������ݵ�����
	IntBoard(show, ROW, COL);//��ʼ�����������ݵ�����
	DrawMineCover(show, ROW, COL);//��Ⱦ��ʼ����
	FirstClick(mine, ROWS, COLS);//���״ε�����г�ʼ��
	while (game_start)//��ʼ����ɺ������ѭ��
	{
		DWORD start_time = GetTickCount();
		FlushBatchDraw();
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)//�����Ϣ��ȡ
			{
				int x = msg.x;
				int y = msg.y;
				int index_x = (x / 50) + 1;
				int index_y = (y / 50) + 1;
				CheckMine(mine, index_x, index_y);//�����λ���Ƿ��е���

			}
			if (msg.message == WM_RBUTTONDOWN)//�����Ϣ��ȡ
			{
				int x = msg.x;
				int y = msg.y;
				int index_x = (x / 50) + 1;
				int index_y = (y / 50) + 1;
				if (show[index_x][index_y] != 9)//�����λ�ò����Ѽ��λ��
				{
					FindMine(show);//��ǵ���
				}
			}
		}
		CheckWin();
		DrawTipText();
		if (all_mine_find)//�ҵ����е���
		{
			MessageBox(GetHWnd(), _T("Mine find"), _T("game end"), MB_OK);
			game_start = false;
		}
		else if (mine_explode)//���ױ�ը
		{
			MessageBox(GetHWnd(), _T("Mine explode"), _T("game end"), MB_OK);
			game_start = false;
		}

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / ((unsigned int)fps))//����ѭ�����Ż�
		{
			Sleep(1000 / fps - delta_time);
		}
	}

	EndBatchDraw();

	closegraph();

	return 0;
}