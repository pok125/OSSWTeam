#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/////////아래 매크로는 텍스트 색깔들을 정의함/////////////////
#define COL GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute(COL, 0x000c);
#define YELLOW SetConsoleTextAttribute(COL, 0x000e);
#define GREEN SetConsoleTextAttribute(COL, 0x0002);
#define SKY_BLUE SetConsoleTextAttribute(COL, 0x000b);
#define BLUE SetConsoleTextAttribute(COL, 0x0001);
#define PURPLE SetConsoleTextAttribute(COL, 0x000d);
#define WHITE SetConsoleTextAttribute(COL, 0x000f);
///////키보드 아스키코드/////////
#define Space 32 
#define Enter 13
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
/////////////////////////////////
#define MAX 100
/////////////////////////////////

///////////////////////함수선언부///////////////////////////
void consolesize();	//콘솔창 크기 조절 함수
void ItemScreen();	//아이템 출력부
void GameMainLoop();	//지렁이 게임 메인 진행 함수
void StoryScreen();	//스토리 진행 함수
void Game();	//게임 대화창
void gotoxy(int x, int y);	//xy커서 좌표이동
void Gameover();	//게임오버시 화면
void MainStation(); //게임 대기 장소
void CursorHide();	//커서 숨기는 함수
void PCKeyInput();	//캐릭터 키보드 함수
void Clock();	//시스템 시간받아오는 함수
void Gamesetting();	//게임 기본세팅함수
void lifeScreen(int lifeCount); //목숨 출력부
void printState(int state); //상태 출력 함수
void init_list(); //item 리스트 재실행시 초기화 
void SetCharacterPosition(int *snakePos, int snakeSize, int direction_snake, int snakeDir); //지렁이 위치 설정 함수
																							////////////////////////////////////////////////////////////


																							///////////////전역변수부///////////////
int PCX = 2;	//주인공 좌표X
int PCY = 4;	//주인공 좌표Y
int second = 0;	//초받아오는 변수
int limitFoodByStage(int stageNum); //스테이지별 먹이 개수 제한 함수
int itemArray[MAX] = { 4 }; //item 입력 받는 리스트
int front = 3;
int rear = 3;
int stageNum = 1; //스테이지 구별 변수 //추후 스테이지 개발자가 생성 및 구현 
				  /////////////////////////////////////////
int Speed;
int snakeSize = 3;


void Clock()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	second = st.wSecond;
}
void Gamesetting()
{

	Clock();
	CursorHide();
}
void PCKeyInput() {
	int key;

	for (int i = 0; i<20; i++)
	{
		if (_kbhit() != 0) {
			gotoxy(PCX, PCY);
			printf("  ");
			key = _getch();
			switch (key) {
			case LEFT:
				if (PCX != 2)
				{
					PCX -= 2;
				}
				break;
			case RIGHT:
				if (PCX != 8 * 2)
				{
					PCX += 2;
				}

				break;
			case UP:
				if (PCY != 1)
				{
					PCY--;
				}
				break;
			case DOWN:
				if (PCY != 8)
				{
					PCY++;
				}

				break;
			}
		}

	}

}
void consolesize()
{
	system("title SewerEscape");   //실행창 이름 바꾸기
	system("mode con:cols=100 lines=30");
}


void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void CursorHide()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Game()
{

	system("cls");


	gotoxy(0, 13);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(0, 14);
	printf("┃                                                                            ┃");
	gotoxy(0, 15);
	printf("┃                                                                            ┃");
	gotoxy(0, 16);
	printf("┃                                                                            ┃");
	gotoxy(0, 17);
	printf("┃                                                                            ┃");
	gotoxy(0, 18);
	printf("┃                                                                            ┃");
	gotoxy(0, 19);
	printf("┃                                                                            ┃");
	gotoxy(0, 20);
	printf("┃                                                                            ┃");
	gotoxy(0, 21);
	printf("┃                                                                            ┃");
	gotoxy(0, 22);
	printf("┃                                                                    enter▼ ┃");
	gotoxy(0, 23);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");


}
void StartMenu()
{
	consolesize();
	Gamesetting();
	system("cls");

	const int x = 41;
	int y = 18;
	int key;
	int i;
	int Select = 3;

	Sleep(1000);
	RED
		//	gotoxy(0, 0);
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

	PURPLE
		gotoxy(41, 17);
	printf("┏━━━━━━━━━━┓\n");

	gotoxy(41, 21);
	printf("┗━━━━━━━━━━┛\n");

	WHITE


		gotoxy(x, y);
	printf("▶");
	printf("게임시작");
	gotoxy(x, y + 1);
	printf("  개발자");
	gotoxy(x, y + 2);
	printf("  게임종료");

	WHITE
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
				Select = y - 18;
				break;
			}
			gotoxy(x, y);
			printf("▶");


			switch (Select)
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
				//handlecount = 1;
				StoryScreen();
				////////////////////////////////////////게임 시작되야되는 부분
				break;
			case 1:
				gotoxy(53, 23);
				printf(" 김덕영 / 김예지 / 이광호 / 김상훈 / 노형섭");
				break;
			case 2:
				exit(0);
				break;

			}
		}


}
void StoryScreen()
{
	int key;
	int PrintCount = 0;
	int roof = 1;


	while (roof)
	{
		if (PrintCount == 0)
		{
			Game();
			gotoxy(4, 15);
			printf("일어나!\n");;
			gotoxy(4, 16);
			printf("일어나 정신이 들어?\n");
			key = _getch();
			if (key == 13)
			{
				PrintCount++;
			}
		}
		if (PrintCount == 1)
		{
			Game();
			gotoxy(4, 15);
			printf("너 길가다가 하수구에 빠진거 기억 안나?\n");
			gotoxy(4, 16);
			printf("그러길래 술 적당히 마시지 그랬어...;; ");
			gotoxy(4, 17);
			printf("하수구를 나가려면 게임을 클리어 해야해! ");


			key = _getch();
			if (key == 13)
			{
				PrintCount++;
			}
		}
		if (PrintCount == 2)
		{
			Game();
			gotoxy(4, 15);
			printf("여기 하수구를 탐험하여 탈출을 해야 살아남을수가 있어!\n");
			gotoxy(4, 16);
			printf("할 수 있겠어?\n");

			gotoxy(4, 19);
			printf("  응  : press Y");
			gotoxy(4, 20);
			printf("아니 : press N");

			key = _getch();
			if (key == 'y' || key == 'Y')
			{
				PrintCount = 3;
			}
			if (key == 'n' || key == 'N')
			{
				PrintCount = 4;
			}
		}
		if (PrintCount == 3)
		{
			Game();
			gotoxy(4, 15);
			printf("좋았어 의지가 충만하군\n");
			gotoxy(4, 16);
			printf("게임에 대해서 궁금하면 나를 찾아오면 알려주도록 할게\n");
			gotoxy(4, 17);
			printf("그럼 몸 조심해!");

			key = _getch();
			if (key == 13)
			{
				roof = 0;
				PrintCount = 5;
			}
		}
		if (PrintCount == 4)
		{
			Game();
			gotoxy(4, 15);
			printf("싫다고? 그럼 죽어!\n");
			gotoxy(4, 16);
			printf("농담이고 싫어도 해야해!\n");
			gotoxy(4, 17);
			printf("게임에 대해서 궁금하면 나를 찾아오면 알려주도록 할게\n");
			gotoxy(4, 18);
			printf("그럼 몸 조심해!");

			key = _getch();
			if (key == 13)
			{
				roof = 0;
				PrintCount = 5;
			}

		}
	}

	if (PrintCount == 5) {

		//	system("cls");
		MainStation();
	}
}
/* 아이템 목록 관련 큐 추가 */
void init_list()// init 함수로 재시작 시 초기화
{
	rear = 3;
	front = 3;
}
void put(int k) // itemArray 큐에 넣음
{


	if (rear - front < 4)
	{
		if (rear - front == 3)
		{
			//아무것도 하지 않음 3이상 차이나지 않게함
		}
		else if (rear - front == 2)
		{
			itemArray[rear] = k;
			gotoxy(48, 18);
			printf("%d", itemArray[rear]);
			gotoxy(48, 16);
			printf("%d", itemArray[rear - 1]);
			gotoxy(48, 14);
			printf("%d", itemArray[rear - 2]);
			rear += 1; // 안해주면 계속 3번 아이템이 바뀜

		}
		else if (rear - front == 1)
		{
			itemArray[rear] = k;
			gotoxy(48, 18);
			printf(" ");
			gotoxy(48, 16);
			printf("%d", itemArray[rear]);
			gotoxy(48, 14);
			printf("%d", itemArray[rear - 1]);
			rear += 1;
		}
		else if (rear - front == 0)
		{
			itemArray[rear] = k;
			gotoxy(48, 18);
			printf(" ");
			gotoxy(48, 16);
			printf(" ");
			gotoxy(48, 14);
			printf("%d", itemArray[rear]);
			rear += 1;
		}
	}
	else //error 확인
	{
		gotoxy(48, 2);
		printf("errer");

	}
}
void get() // itemArray 큐에서 빼냄, 사용하게 하고, 리스트에서 아이템 지움
{
	if (rear - front < 4) // 아이템이 없는데도 계속적으로 쓰지 못하도록 3 이내
	{
		gotoxy(48, 22);
		printf("get : %d", itemArray[front]); //현재 사용되는 아이템

		if (itemArray[front] <1)
		{
			if (Speed < 40)
			{
				Speed += 2;
				gotoxy(46, 21);
				printf("효과 : 스피드 업!!");

			}
		}
		else if (1< itemArray[front] < 3)
		{
			if (snakeSize < 50)
			{
				snakeSize += 1;
				gotoxy(46, 21);
				printf("효과 : 지렁이 길이 +1!!");
			}
		}
		else if (3< itemArray[front] <5)
		{
			gotoxy(46, 21);
			printf("효과 : 나는 무적이다!!");
		}

		front += 1;
	}
	//다시 바뀐 배열을 프린트함

	if (rear - front == 2)
	{
		gotoxy(48, 18);
		printf(" ");
		gotoxy(48, 16);
		printf("%d", itemArray[front + 1]);
		gotoxy(48, 14);
		printf("%d", itemArray[front]);
	}
	else if (rear - front == 1)
	{
		gotoxy(48, 18);
		printf(" ");
		gotoxy(48, 16);
		printf(" ");
		gotoxy(48, 14);
		printf("%d", itemArray[front]);
	}
	else if (rear - front == 1)
	{
		gotoxy(48, 18);
		printf(" ");
		gotoxy(48, 16);
		printf(" ");
		gotoxy(48, 14);
		printf(" ");
	}
	/*
	gotoxy(48, 14);
	printf("%d", itemArray[front+1]); //1번 템
	gotoxy(48, 16);
	printf("%d", itemArray[front]);
	gotoxy(48, 18);
	printf("%d", itemArray[front-1]);
	*/


}
void Gameover()
{
	RED
		gotoxy(0, 0);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(1000);
	WHITE
		char key;
	gotoxy(34, 13);
	printf("당신은 죽었습니다.");
	Sleep(1000);
	gotoxy(30, 14);
	printf("다시하시겠습니까?   Y/N");
	while (1)
	{

		printf("");
		key = _getch();
		printf(" ");
		switch (key)
		{
		case 'n':
			StartMenu();
			break;
		case 'N':
			StartMenu();
			break;
		case 'y':

			StartMenu();
			break;
		case 'Y':
			StartMenu();
			break;
		}
	}

}
void MainStation()
{
	system("cls");
	int NPCX, NPCY;
	int arraySizeY = 10;
	int arraySizeX = arraySizeY;
	char *arr = NULL;
	int TalkCheck = 0;
	int DetectHelper = 0;
	int SBCheck = 0;


	NPCX = NPCY = 10;


	arr = malloc(arraySizeX * arraySizeY * sizeof(char));            //메모리값 오류 확인
	if (arr == NULL)
	{
		printf("cannot allocate memory\n"); _getch();
	}

	for (int i = 0; i < arraySizeX * arraySizeY; i++) arr[i] = '0'; //맵 공백 초기화
																	/* 맵의 프레임 생성은 (arraySizeX * arraySizeY) */
	for (int i = 0; i < arraySizeX * arraySizeY; i++)
	{

		if (i < arraySizeX) arr[i] = '1';
		else if (i % arraySizeX == 0) { arr[i] = '1'; }
		else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '1';
		else if (i % arraySizeX == arraySizeX - 1) arr[i] = '1';
		//else arr[i] = ' '; 

	}


	for (int i = 0; i < arraySizeX; i++)
	{
		void hidecursor();

		if (i == 4)	//x좌표 수집
		{
			NPCX = i * 2;
		}
		for (int j = 0; j < arraySizeY; j++)
		{
			if (j == 2)	//Y좌표 수집
			{
				NPCY = j;
			}
			if (arr[i * arraySizeX + j] == '1')
			{
				printf("■");
				//j++;
			}
			else if (arr[i * arraySizeX + j] == '0')
			{
				printf("  ");
			}
			else if (arr[i * arraySizeX + j] == '*')
			{
				printf("●");
			}
			else if (arr[i * arraySizeX + j] == '+')
			{
				printf("♡");
			}
			//   printf("%c", arr[i * arraySizeX + j]);
		}
		printf("\n");
	}


	int timer = 0;
	while (1)
	{
		Gamesetting();
		gotoxy(NPCX, NPCY);
		printf("§");
		if (SBCheck == 0)
		{
			if (second % 2 == 0)
			{
				gotoxy(NPCX - 2, NPCY - 1);
				printf("이리와");
			}
			else if (second % 2 != 0)
			{
				gotoxy(NPCX - 2, NPCY - 1);
				printf("대화해");
				timer = 0;
			}
		}
		else
		{
			gotoxy(NPCX - 2, NPCY - 1);
			printf("      ");
			gotoxy(NPCX, NPCY + 6);
			printf("★");
		}
		timer++;
		gotoxy(PCX, PCY);
		printf("⊙");
		PCKeyInput();

		if (PCX == NPCX && PCY - NPCY <= 1 && PCY - NPCY >= 0) //down
		{
			DetectHelper = 1;
		}
		else if (PCY == NPCY && PCX - NPCX <= 2 && PCX - NPCX >= 0)//right
		{
			DetectHelper = 1;
		}
		else if (PCY == NPCY && NPCX - PCX <= 2 && NPCX - PCX >= 0)//left
		{
			DetectHelper = 1;
		}
		else
		{
			DetectHelper = 0;
			TalkCheck = 0;

		}

		if (DetectHelper == 1 && TalkCheck == 0)
		{
			gotoxy(20, 0);
			printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
			gotoxy(20, 1);
			printf("┃                           ┃");
			gotoxy(20, 2);
			printf("┃                           ┃");
			gotoxy(20, 3);
			printf("┃                           ┃");
			gotoxy(20, 4);
			printf("┃                           ┃");
			gotoxy(20, 5);
			printf("┃                           ┃");
			gotoxy(20, 6);
			printf("┃                           ┃");
			gotoxy(20, 7);
			printf("┃                           ┃");
			gotoxy(20, 8);
			printf("┃                           ┃");
			gotoxy(20, 9);
			printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

			if (stageNum == 1)
			{
				gotoxy(22, 1);
				printf("탈출하기 위해\n");
				gotoxy(22, 1);
				printf("너가 해야할 게임은\n");
				gotoxy(22, 2);
				printf("지렁이 게임이야\n");
				gotoxy(22, 3);
				printf("아래에있는 ★에 가면");
				gotoxy(22, 4);
				printf("탈출을 위한 게임할수있어");
				gotoxy(22, 5);
				printf("죽지 않게 조심해!");
				TalkCheck = 1;
				SBCheck = 1;
			}
			else if (stageNum == 2)
			{
				gotoxy(22, 1);
				printf("첫번째는 쉽지?\n");
				gotoxy(22, 1);
				printf("이제 세번만 더하면\n");
				gotoxy(22, 2);
				printf("탈출 할수있어\n");
				gotoxy(22, 3);
				printf("갈수록 어려워지니 조심해");
				gotoxy(22, 4);
				printf("아래에있는 ★에 가면");
				gotoxy(22, 5);
				printf("다음 게임을 할수있어!");
				TalkCheck = 1;
				SBCheck = 1;
			}
			else if (stageNum == 3)
			{
				gotoxy(22, 1);
				printf("두번째도 꽤나 \n");
				gotoxy(22, 1);
				printf("잘 해내었구나!\n");
				gotoxy(22, 2);
				printf("지금 처럼 계속\n");
				gotoxy(22, 3);
				printf("하면 탈출 할수 있을거야");
				gotoxy(22, 4);
				printf("★에 가면 다음게임을 할수있어");
				gotoxy(22, 5);
				printf("죽지 않게 조심해!");
				TalkCheck = 1;
				SBCheck = 1;
			}
			else if (stageNum == 4)
			{
				gotoxy(22, 1);
				printf("마지막이구나 \n");
				gotoxy(22, 1);
				printf("나름 정들었는데\n");
				gotoxy(22, 2);
				printf("그래도 나가야겠지?\n");
				gotoxy(22, 3);
				printf("아래에있는 ★에 가면");
				gotoxy(22, 4);
				printf("탈출을 위한 게임할수있어");
				gotoxy(22, 5);
				printf("마지막이니 죽지마!");
				TalkCheck = 1;
				SBCheck = 1;
			}
			else if (stageNum == 5)
			{
				gotoxy(22, 1);
				printf("해냈구나!\n");
				gotoxy(22, 1);
				printf("이제 탈출 할수있어!\n");
				gotoxy(22, 2);
				printf("아래에있는 ★에가면 \n");
				gotoxy(22, 3);
				printf("바깥 세상으로 나갈수 있어!");
				gotoxy(22, 4);
				printf("지금 까지 고생했고");
				gotoxy(22, 5);
				printf("잘가!");
				TalkCheck = 1;
				SBCheck = 1;
			}

		}
		else if (DetectHelper == 0)
		{
			gotoxy(20, 0);
			printf("                                                ");
			gotoxy(20, 1);
			printf("                                                ");
			gotoxy(20, 2);
			printf("                                                ");
			gotoxy(20, 3);
			printf("                                                ");
			gotoxy(20, 4);
			printf("                                                ");
			gotoxy(20, 5);
			printf("                                                ");
			gotoxy(20, 6);
			printf("                                                ");
			gotoxy(20, 7);
			printf("                                                ");
			gotoxy(20, 8);
			printf("                                                ");
			gotoxy(20, 9);
			printf("                                                ");
			gotoxy(22, 1);

		}
		if (SBCheck == 1 && PCX == NPCX && PCY == NPCY + 6)
		{
			GameMainLoop();
		}
		else if (SBCheck == 1 && PCX == NPCX && PCY == NPCY + 6 && stageNum == 5)
		{
			StartMenu();
		}
	}
}
void GameMainLoop()
{

	int NUMBER_OF_CONFIG_ELEMENTS = 5;
	int STARTING_DIRECTION = 0;
	int INITIAL_SNAKE_SIZE = 3;
	int INCREASE_SPEED_ON_EVERY_FOOD = 0;
	char Key;
	int CurrentDir = 0;
	int direction_snake = 0;
	int Dead = 0;
	int i, j, z, createItem;
	char *arr = NULL;
	int CheckFoodCoord = 0;
	int CheckItemCoord = 0;
	char unused[30];
	int arraySizeX = 16;
	int arraySizeY = 16;
	int newFood = 1;
	int NoNewGame = 0;
	int foodPos[2];
	int itemPos[2];
	int izqdeGolemiq = 0;
	int food_testX = 0;
	int food_testY = 0;
	int item_testX = 0;
	int item_testY = 0;
	int snakePos[100];  //x,y pos for 50 snake elements. If the snake is getting bigger -> malloc for new 10 elements

	int snakeDir = 1; /* 1 - nadqsno, 2 - nagore, 3 -nalqvo, 4, nadolu */
	int newItem = 1;
	int selectItem = 0; // 아이템 생성시 선택된 아이템
	int shieldItem = 0; // 무적아이템 유무확인 변수
	int lifeCount;
	int foodCount;
	int NeedEscape;

	arraySizeY = 20;
	arraySizeX = arraySizeY;

	if (stageNum == 1)
	{
		lifeCount = 0; //목숨 개수(스테이지별 초기화)
		foodCount = 0; //스테이지 별 먹이 수 제한 
		NeedEscape = 5;
		Speed = 3;
	}
	else if (stageNum == 2)
	{
		lifeCount = 0; //목숨 개수(스테이지별 초기화)
		foodCount = 0; //스테이지 별 먹이 수 제한 
		NeedEscape = 7;
		Speed = 5;
	}
	else if (stageNum == 3)
	{
		lifeCount = 0; //목숨 개수(스테이지별 초기화)
		foodCount = 0; //스테이지 별 먹이 수 제한 
		NeedEscape = 9;
		Speed = 7;
	}
	else if (stageNum == 4)
	{
		lifeCount = 0; //목숨 개수(스테이지별 초기화)
		foodCount = 0; //스테이지 별 먹이 수 제한 
		NeedEscape = 12;
		Speed = 9;
	}

	ItemScreen();
	gotoxy(58, 0);
	printf("♤ : 먹이");
	gotoxy(58, 1);
	printf("△ : 스피드 업 (Q 입력 시 사용가능)");
	gotoxy(58, 2);
	printf("▽ : 스피드 다운");
	gotoxy(58, 3);
	printf("● : 지렁이 길이 +1 (Q 입력 시 사용가능)");
	gotoxy(58, 4);
	printf("○ : 지렁이 길이 -1");
	gotoxy(58, 5);
	printf("★ : 무적 (Q 입력 시 사용가능)");

	arr = (char*)malloc(arraySizeX * arraySizeY * sizeof(char));            //메모리값 오류
	if (arr == NULL)
	{
		printf("cannot allocate memory\n"); _getch();
	}

	for (i = 0; i < arraySizeX * arraySizeY; i++) arr[i] = ' '; //맵 공백 초기화
																/* Create the frame arraySizeX * arraySizeY */
	for (i = 0; i < arraySizeX * arraySizeY; i++)
	{

		if (i < arraySizeX) arr[i] = '-';
		else if (i % arraySizeX == 0) { arr[i] = '|'; }
		else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '-';
		else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|';
	}

	while (1)
	{ // new game cycle
		srand(time(NULL));
		for (j = 0; j < 100; j++) snakePos[j] = 1; //스네이크 포지션 1로 초기화
		Dead = 0;
		NoNewGame = 0;
		CurrentDir = 0;
		CheckFoodCoord = 0;
		izqdeGolemiq = 0;
		newFood = 1;
		snakeDir = 1;
		Key = 0;
		createItem = 10;  // 아이템이 사라지기 전 움직일 수 있는 최대값
		stageNum = 1; //임의로 초기화 1탄
		foodCount = limitFoodByStage(stageNum);
		lifeCount = 3;
		lifeScreen(lifeCount);
		snakeSize = 3;

		z = 24; //z는 음식이 사라지기 전 움직일 수 있는 최대값

		SetCharacterPosition(snakePos, snakeSize, 2, snakeDir); // 뱀 고정 위치 설정
		fflush(stdin);

		while (1)
		{


			z--;
			createItem--;
			if (z == 0) newFood = 1;
			if (createItem == 0) newItem = 1;
			// z가 25번 넘어가면 음식 다시생기게하는 부분

			gotoxy(2, 20);
			printf("%d : 탈출까지 길어져야 하는 목표 갯수", NeedEscape - snakeSize + 3);


			izqdeGolemiq = 0;
			CurrentDir = snakeDir;

			/* Create the frame arraySizeX * arraySizeY */
			for (i = 0; i < arraySizeX * arraySizeY; i++)  //맵 가장자리 생성
			{
				if (i < arraySizeX) arr[i] = '-';             //맨 위쪽 벽
				else if (i % arraySizeX == 0) { arr[i] = '|'; } //왼쪽 벽
				else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '-'; //맨아래 벽
				else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|'; //오른쪽 벽
				else arr[i] = ' ';
			}

			/* Create the food - place '+' on a random coordinates different than the snake coordinates */
			if (newFood)        //이동 한계치 초과시 음식 재생성 구간 및 음식 포지션 설정(뱀과의 위치에서 일정하게 떨어져야지 생성됨)

			{
				CheckFoodCoord = 0;
				for (;;)
				{
					food_testX = 1 + rand() % (arraySizeX - 2);
					food_testY = 1 + rand() % (arraySizeY - 2);
					for (i = 0; i < snakeSize; i++)
					{
						if ((snakePos[2 * i] != food_testX) && (snakePos[2 * i + 1] != food_testY))
							CheckFoodCoord = 1;
					}
					if (CheckFoodCoord) break;
				}

				if (foodCount <= 0) {
					foodPos[0] = 0;
					foodPos[1] = 0;
				}
				else {
					foodPos[0] = food_testX;
					foodPos[1] = food_testY;
				}

				z = arraySizeX * 2;
				newFood = 0;
				foodCount--;

			}

			if (newItem)        //아이템 재생성 구간 및 아이템 포지션 설정(뱀과의 위치에서 일정하게 떨어져야지 생성됨)

			{
				CheckItemCoord = 0;
				selectItem = rand() % 5; // 아이템 랜덤으로 선택
				for (;;)
				{
					item_testX = 1 + rand() % (arraySizeX - 2);
					item_testY = 1 + rand() % (arraySizeY - 2);
					for (i = 0; i < snakeSize; i++)
					{
						if ((snakePos[2 * i] != item_testX) && (snakePos[2 * i + 1] != item_testY))
							CheckItemCoord = 1;
					}
					if (CheckItemCoord) break;
				}
				itemPos[0] = item_testX;
				itemPos[1] = item_testY;
				createItem = 15;
				newItem = 0;
			}

			/* Check snake coordinates for food for impact or walls - for food -> increase snake_size +1; - for impact and walls -> Dead = 1 */
			for (i = 0; i < snakeSize; i++)           //충돌 체크
			{
				/* food check 음식과 충돌시*/
				if ((snakePos[2 * i] == foodPos[0]) && (snakePos[2 * i + 1] == foodPos[1]))
				{
					newFood = 1;
					/* the snake cannot be longer than 25 elements. */
					if (snakeSize < 50) snakeSize++;                         // 스네이크 길이 증가
					izqdeGolemiq = 1;
					if (INCREASE_SPEED_ON_EVERY_FOOD && (Speed < 40))Speed++;
				}
				/* 아이템과 충돌시 */
				if ((snakePos[2 * i] == itemPos[0]) && (snakePos[2 * i + 1] == itemPos[1]))
				{
					newItem = 1;
					izqdeGolemiq = 1;
					//충돌된 아이템에 따라 부여되는 효과 설정
					switch (selectItem)
					{
					case 0: //△ : 스피드 업

						put(0); //itemArray[]에 번호로 추가
						break;
					case 1: //▽ : 스피드 다운
						if (Speed < 40 && Speed >0) Speed -= 2;
						break;
					case 2: //● : 지렁이 길이 +1

						put(2); //itemArray[]에 번호로 추가
						break;
					case 3: //○ : 지렁이 길이 -1
						if (snakeSize < 50 && snakeSize>0)
							snakeSize--;
						break;
					case 4: //★ : 무적
						shieldItem = 1;
						put(4); //itemArray[]에 번호로 추가
						break;
					}

				}
				/* wall check 벽돌과 충돌시*/
				if (!izqdeGolemiq)
				{
					if ((arr[snakePos[2 * snakeSize - 1] * arraySizeX + snakePos[2 * snakeSize - 2]] == '-') || (arr[snakePos[2 * snakeSize - 1] * arraySizeX + snakePos[2 * snakeSize - 2]] == '|'))
					{
						if (shieldItem)
						{
							shieldItem = 0;
							SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
						}
						else
						{
							lifeCount--;
							if (lifeCount < 0)
								Dead = 1;
							else {
								lifeScreen(lifeCount);
								//뱀 위치 랜덤설정하는 코드 복붙
								//추후 함수로 빼서 호출하기 
								SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
								fflush(stdin);
							}
						}
					}
				}
				else
				{
					if ((arr[snakePos[2 * snakeSize - 3] * arraySizeX + snakePos[2 * snakeSize - 4]] == '-') || (arr[snakePos[2 * snakeSize - 3] * arraySizeX + snakePos[2 * snakeSize - 4]] == '|'))
					{

						if (shieldItem)
						{
							shieldItem = 0;
							SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
						}
						else
						{
							lifeCount--;
							if (lifeCount < 0)
								Dead = 1;
							else {
								lifeScreen(lifeCount);
								//뱀 위치 랜덤설정하는 코드 복붙
								//추후 함수로 빼서 호출하기 
								SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
								fflush(stdin);
							}
						}
					}
				}
				/* snake self-impact check 지렁이가 자신의 몸에 충돌 하는지 검사하는 부분  */
				if (i != (snakeSize - 1))
				{
					if ((snakePos[2 * (snakeSize - 1)] == snakePos[2 * i]) && (snakePos[2 * (snakeSize - 1) + 1] == snakePos[2 * i + 1]))
					{
						lifeCount--;
						if (lifeCount < 0)
							Dead = 1;
						else {
							lifeScreen(lifeCount);
							SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
							fflush(stdin);
						}
					}
				}
			}

			/* Calculate new snake depending on the Dir choosed by user. move the array */
			/* move array - food condition */
			if (izqdeGolemiq)
			{
				for (i = snakeSize; i > 1; i--)
				{
					snakePos[2 * i - 1] = snakePos[2 * i - 3];
					snakePos[2 * i - 2] = snakePos[2 * i - 4];
				}
				if (snakeDir == 1) { snakePos[0] = snakePos[2] - 1; snakePos[1] = snakePos[3]; } // move right
				if (snakeDir == 2) { snakePos[0] = snakePos[2];      snakePos[1] = snakePos[3] + 1; } // move up
				if (snakeDir == 3) { snakePos[0] = snakePos[2] + 1; snakePos[1] = snakePos[3]; } // move left
				if (snakeDir == 4) { snakePos[0] = snakePos[2];      snakePos[1] = snakePos[3] - 1; } // move down
			}
			/* move array - dir condition */
			for (i = 0; i < snakeSize - 1; i++)
			{
				snakePos[2 * i] = snakePos[2 * i + 2];
				snakePos[2 * i + 1] = snakePos[2 * i + 3];
			}

			if (snakeDir == 1) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4] + 1; snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3]; } // move right
			if (snakeDir == 2) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4];      snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3] - 1; } // move up
			if (snakeDir == 3) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4] - 1; snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3]; } // move left
			if (snakeDir == 4) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4];      snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3] + 1; } // move down

																																								  /* Create the snake */
			for (i = 0; i < snakeSize; i++)
			{
				arr[snakePos[2 * i + 1] * arraySizeX + snakePos[2 * i]] = '*';  // 뱀 모양
			}

			/* Put the food on the matrix */
			if (foodPos[0] == 0 && foodPos[1] == 0)
				arr[foodPos[1] * arraySizeX + foodPos[0]] = '-';
			else
				arr[foodPos[1] * arraySizeX + foodPos[0]] = '+';

			switch (selectItem)
			{
			case 0: //△ : 스피드 업
				arr[itemPos[1] * arraySizeX + itemPos[0]] = '&';
				break;
			case 1: //▽ : 스피드 다운
				arr[itemPos[1] * arraySizeX + itemPos[0]] = '^';
				break;
			case 2: //● : 지렁이 길이 +1
				arr[itemPos[1] * arraySizeX + itemPos[0]] = '$';
				break;
			case 3: //○ : 지렁이 길이 -1
				arr[itemPos[1] * arraySizeX + itemPos[0]] = '(';
				break;
			case 4: //★ : 무적
				arr[itemPos[1] * arraySizeX + itemPos[0]] = '!';
				break;
			}

			//system("cls");
			gotoxy(0, 0);
			/* print the matrix with the snake and the food*/
			for (i = 0; i < arraySizeX; i++)
			{
				void hidecursor();

				for (j = 0; j < arraySizeY; j++)
				{
					if (arr[i * arraySizeX + j] == '-')
					{
						printf("■");
						//j++;
					}
					else if (arr[i * arraySizeX + j] == '|')
					{
						printf("■");
					}
					else if (arr[i * arraySizeX + j] == ' ')
					{
						printf("  ");
					}
					else if (arr[i * arraySizeX + j] == '*') //지렁이 모양 
					{
						printf("●");
					}
					else if (arr[i * arraySizeX + j] == '+') //♤ : 먹이 
					{
						printf("♤");
					}
					else if (arr[i * arraySizeX + j] == '&') //△ : 스피드 업
					{
						printf("△");
					}
					else if (arr[i * arraySizeX + j] == '^') //▽ : 스피드 다운
					{
						printf("▽");
					}
					else if (arr[i * arraySizeX + j] == '$') //● : 지렁이 길이 +1
					{
						printf("●");
					}
					else if (arr[i * arraySizeX + j] == '(') //○ : 지렁이 길이 -1
					{
						printf("○");
					}
					else if (arr[i * arraySizeX + j] == '!') //★ : 무적
					{
						printf("★");
					}
					//   printf("%c", arr[i * arraySizeX + j]);
				}
				printf("\n");
			}


			/* if condition Dead is satisfied -> break  키보드로 뱀 이동*/
			Key = 0;
			if (Dead) break;
			if (NeedEscape - snakeSize + 3 == 0)
			{

				break;
			}
			Sleep(1000 / Speed);
			if (_kbhit())
			{
				Key = _getch();
			}
			if (Key == -32)
			{
				switch (_getch())
				{
				case 72:
					snakeDir = 2; //up
					break;
				case 80:
					snakeDir = 4; //down
					break;
				case 75:
					snakeDir = 3; //left
					break;
				case 77:
					snakeDir = 1; // right
					break;
				}
			}
			else if (Key == 27)
			{
				Key = 0;
				while (1)
				{
					fflush(stdin);
					if (_kbhit())
					{
						Key = _getch();
					}
					if (Key == 27) break;
				}
			}
			/* 아이템 사용 */
			if (Key == 'q' || Key == 'Q')
			{
				get(Speed, snakeSize);
			}

			if (snakeDir != CurrentDir)
			{
				/* if the current direction is left -> we cannot choose right ...*/
				if (snakeDir == 2 && CurrentDir == 4) snakeDir = 4;
				if (snakeDir == 1 && CurrentDir == 3) snakeDir = 3;
				if (snakeDir == 4 && CurrentDir == 2) snakeDir = 2;
				if (snakeDir == 3 && CurrentDir == 1) snakeDir = 1;
			}
			fflush(stdin);
			CurrentDir = snakeDir;
			i++;
		}

		if (Dead)             // 뱀이 죽었을 경우
		{
			Gameover();
		}
		if (NeedEscape - snakeSize + 3 == 0)
		{
			stageNum++;
			MainStation();
		}

	}
}
int limitFoodByStage(int stageNum) {
	int foodCount;
	switch (stageNum) {
	case 1: foodCount = 10; break;
	case 2: foodCount = 9; break;
	case 3: foodCount = 8; break;
	case 4: foodCount = 7; break;
	case 5: foodCount = 6; break;
	}
	return foodCount;
}
void lifeScreen(int lifeCount) {
	switch (lifeCount)
	{
	case 0: YELLOW gotoxy(42, 3); printf("■  ■  ■  ■"); break;
	case 1: gotoxy(42, 3); printf("■♡■  ■  ■"); break;
	case 2: gotoxy(42, 3); printf("■♡■♡■  ■"); break;
	case 3: gotoxy(42, 3); printf("■♡■♡■♡■"); break;
	default: break;
	}
	gotoxy(42, 0);
	printf("■■■■■■■");
	gotoxy(42, 1);
	printf("■ L I F E  ■");
	gotoxy(42, 2);
	printf("■■■■■■■");
	gotoxy(42, 4);
	printf("■■■■■■■");

}
void printState(int state) {
	switch (state)
	{
		//case 0: gotoxy(42, 9); printf("목숨 -1 되었습니다.");  break;
		//case 0: gotoxy(42, 9); printf("△ : 스피드 업");  break;
		//case 1: gotoxy(42, 9); printf("▽ : 스피드 다운");  break;
		//case 2: gotoxy(42, 9); printf("● : 지렁이 길이 +1");  break;
		//case 3: gotoxy(42, 9); printf("○ : 지렁이 길이 -1");  break;
		//case 4: gotoxy(42, 9); printf("◑ : 먹이 먹을 시 +2");  break;
		//case 5: gotoxy(42, 9); printf("★ : 무적");  break;
		//default: break;
	}
}
void ItemScreen()
{
	gotoxy(42, 11);
	printf("■■■■■■■");
	gotoxy(42, 12);
	printf("■ I T E M  ■");
	gotoxy(42, 13);
	printf("■■■■■■■");
	gotoxy(42, 14);
	printf("■ 1:       ■");
	gotoxy(42, 15);
	printf("■■■■■■■");
	gotoxy(42, 16);
	printf("■ 2:       ■");
	gotoxy(42, 17);
	printf("■■■■■■■");
	gotoxy(42, 18);
	printf("■ 3:       ■");
	gotoxy(42, 19);
	printf("■■■■■■■");
	gotoxy(42, 20);
	printf("if press q you can use Item");
}
void SetCharacterPosition(int *snakePos, int snakeSize, int direction_snake, int snakeDir)
{
	int i, j;
	for (i = 0; i < snakeSize; i++)   //뱀 위치 랜덤 설정
	{
		if (i == 0)
		{
			snakePos[i] = 10;
			snakePos[2 * i + 1] = 13;

		}
		else
		{
			if (i == 1)
			{
				switch (direction_snake)
				{
				case 1: /*Right*/
					for (j = 2; j < 2 * snakeSize + 1;)
					{
						snakePos[j] = snakePos[j - 2] + 1;
						snakePos[j + 1] = snakePos[j - 1];
						j += 2;
					}
					snakeDir = 1;
					break;
				case 2:  /*up*/
					for (j = 2; j < 2 * snakeSize + 1;)
					{
						snakePos[j] = snakePos[j - 2];
						snakePos[j + 1] = snakePos[j - 1] - 1;
						j += 2;
					}
					snakeDir = 2;
					break;
				case 3: /* Left*/
					for (j = 2; j < 2 * snakeSize + 1;)
					{
						snakePos[j] = snakePos[j - 2] - 1;
						snakePos[j + 1] = snakePos[j - 1];
						j += 2;
					}
					snakeDir = 3;
					break;
				case 4: /*Down */
					for (j = 2; j < 2 * snakeSize + 1;)
					{
						snakePos[j] = snakePos[j - 2];
						snakePos[j + 1] = snakePos[j - 1] + 1;
						j += 2;
					}
					snakeDir = 4;
					break;

				}
			}
		}
	}
}
int main()
{
	StartMenu();
	_getch();
	return 0;
}