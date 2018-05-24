#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <string.h>

#pragma comment(lib,"winmm.lib")

#define Space 32 //스페이스바의 아스키코드
/*--------아래 매크로는 텍스트 색깔들을 정의함. ---------*/
#define COL GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute(COL, 0x000c);
#define YELLOW SetConsoleTextAttribute(COL, 0x000e);
#define GREEN SetConsoleTextAttribute(COL, 0x0002);
#define SKY_BLUE SetConsoleTextAttribute(COL, 0x000b);
#define BLUE SetConsoleTextAttribute(COL, 0x0001);
#define PURPLE SetConsoleTextAttribute(COL, 0x000d);
#define WHITE SetConsoleTextAttribute(COL, 0x000f);
#define Enter 13
#define COMMAND_SIZE 256\

int handlecount = 0;
int startcount = 0;
int Menu(void);
void consolesize();
void TT(void);
//void RankScreen();
//void Story(void);

void gotoxy(int x, int y);

void consolesize() {
	//char command[COMMAND_SIZE] = { '\0', };
	//int lines = 30;
	//int cols = 100;
	//printf(command, "mode con: lines=%d cols=%d", lines, cols);
	//system(command);

	system("mode con:cols=100 lines=30");
	
}

void TT(void)
{
	gotoxy(53, 23);
	printf(" 김덕영 / 김예지 / 이광호 / 김상훈 / 노형섭");
	Sleep(3000);
	gotoxy(53, 23);
	printf("                                   ");
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int Menu(void)
{

	const int x = 41;
	int y = 18;
	int key;
	if (startcount == 0) {
		gotoxy(x, y);
		printf("▶");
		printf("게임시작");
		gotoxy(x, y + 1);
		printf("  개발자");
		gotoxy(x, y + 2);
		printf("  게임종료");
	}

	while (1)
	{
		gotoxy(x, y);
		printf("");
		key = _getch();
		printf(" ");
		switch (key)
		{
		case 72:     //방향키로 바꿔야함
			if (y > 18) y--;
			break;
		case 80:     //얘도
			if (y < 20) y++;
			break;
		case 13:
		{//이것도 엔터
			startcount = 1;
			return y - 18;
		}
		}
		if (handlecount != 1) {
			gotoxy(x, y);
			printf("▶");
		}
	}

}

int main()
{
	consolesize();
	int i;
	int SELECT;

	Sleep(1000);
	RED
	printf("                                                                                              \n");
	printf("                                                                                              \n");
	printf("      ■■■■     ■             ■        ■■■■■■        ■■■■■ ■       ■■■■      \n");
	printf("                   ■           ■  ■                ■        ■         ■                     \n");
	printf("    ■■■■■■   ■         ■      ■              ■        ■■■■   ■■   ■■■■■■    \n");
	printf("                   ■       ■          ■          ■          ■         ■          ■         \n");
	printf("       ■■■      ■■■                                       ■■■■■ ■         ■ ■       \n");
	printf("      ■    ■     ■       ■■■■■■■  ■■■■■■■                                        \n");
	printf("       ■■■      ■             ■              ■                  ■■■■    ■■■■■■■  \n");
	printf("                   ■             ■              ■                        ■          ■        \n");
	printf("                                                                      ■■■■       ■■■■     \n");
	printf("                                                                      ■                   ■     \n");
	printf("                                                                      ■■■■       ■■■■     \n");
	printf("                                                                                     ■           \n");
	printf("                                                                                     ■■■■     \n");
	Sleep(500);
	RED


	PURPLE
	gotoxy(41, 17);
	printf("┏━━━━━━━━━━┓\n");

	gotoxy(41, 21);
	printf("┗━━━━━━━━━━┛\n");

	WHITE

	YELLOW


	WHITE
		while (1)
		{
			SELECT = Menu();
			switch (SELECT)
			{
			case 0:
				system("cls");
				for (i = 3; i > 0; i--)
				{
					gotoxy(65, 24);
					printf("Start in..%d", i);
					Sleep(1000);
				}
				system("cls");
				handlecount = 1;
//				Story();
				////////////////////////////////////////게임 시작되야되는 부분
				break;
			case 1:
				TT();
				break;
			case 2:
				exit(0);

				break;
	
				
				break;


			}

		}
	return 0;
}