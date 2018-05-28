#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*
Config file:  config.cfg
content:
arraySizeX					16 // these two values should be equal
arraySizeY					16 // no bigger than 16
StartingDirection			2  // 0 - random.  1 - nadqsno, 2 - nagore, 3 -nalqvo, 4, nadolu 
snakeSize					5  // no longer than 5;
IncreaseSpeedOnEveryFood	1
The config value is opened only if the user choose '0' for the size of the array.
*/


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
#define MAX 50
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
void init_list(); //item 리스트 재실행시 초기화 
void SetCharacterPosition(int *snakePos, int snakeSize, int direction_snake, int snakeDir); //지렁이 위치 설정 함수
COORD GetCurrentCursorPos();//현재좌표 받아오기

							/////////////전역변수부///////////////////////
int NPCX, NPCY;
int PCX = 2;	//주인공 좌표X
int PCY = 4;	//주인공 좌표Y
int second = 0;	//초받아오는 변수
int limitFoodByStage(int stageNum); //스테이지별 먹이 개수 제한 함수
int itemArray[MAX] = { 6 }; //item 입력 받는 리스트
int front = 3;
int rear = 3;
int stageNum = 1; //스테이지 구별 변수 
int Speed;
int snakeSize = 3;

/////////////////////////////////////////

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
COORD GetCurrentCursorPos()
{

	COORD curPoint;

	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	curPoint.X = curInfo.dwCursorPosition.X;

	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;

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
	system("mode con:cols=100 lines=30");	//콘솔창 크기 조절
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
			switch (key) //방향키로 이동
			{
			case 72:
				if (y > 18) y--;
				break;
			case 80:
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
				StoryScreen();
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
			printf("술 적당히 마시지 그랬어...;; ");
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
			printf("농담이고 싫어도 나가려면 해야해!\n");
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

	if (PrintCount == 5)
	{
		MainStation();
	}
}
/* 아이템 목록 관련 큐 추가 */
void init_list()// init 함수로 재시작 시 초기화
{
	rear = 0;
	front = 0;
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
				// 몇이 들어갔는지 확인용 printf("%d", itemArray[front]);
			}
		}
		else if (3< itemArray[front]<5)
		{
			if (snakeSize < 50)
			{
				gotoxy(46, 21);
				printf("효과 : 나는 무적이다!!");
			}
		}
		else
		{

		}

		front += 1;
	}
	else
	{

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
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(100);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

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
	int arraySizeY = 10;
	int arraySizeX = arraySizeY;
	char *arr = NULL;
	int TalkCheck = 0;
	int DetectHelper = 0;
	int SBCheck = 0;

	PCX = 2;	//주인공 좌표X
	PCY = 4;	//주인공 좌표Y
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
				printf("이제 세번만 더하면\n");
				gotoxy(22, 1);
				printf("탈출 할수있어\n");
				gotoxy(22, 2);
				printf("하지만 녀석을 화나게 했어\n");
				gotoxy(22, 3);
				printf("@ 이녀석을 조심하라구");
				gotoxy(22, 4);
				printf("빨간색으로 변하면");
				gotoxy(22, 5);
				printf("널 따라오는거니");
				gotoxy(22, 6);
				printf("조심하도록해!");
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
				printf("라이프갯수가 줄어들었어\n");
				gotoxy(22, 3);
				printf("보다 신중하길 바래");
				gotoxy(22, 4);
				printf("@ 이녀석 화나서 예민해졌어");
				gotoxy(22, 5);
				printf("가까이 가지 않도록 조심해!");
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
				printf("마지막은 라이프가 없어");
				gotoxy(22, 4);
				printf("한번의 기회뿐이니");
				gotoxy(22, 5);
				printf("죽지말고 신중히해");
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
	int i, j, z, createItem;	//z는 음식이 사라지기 전 움직일 수 있는 최대값
	char *arr = NULL;
	int CheckFoodCoord = 0;
	int CheckItemCoord = 0;
	int arraySizeX;
	int arraySizeY;
	int newFood = 1;
	int NoNewGame = 0;
	int foodPos[2];
	int itemPos[2];
	int izqdeGolemiq = 0;
	int food_testX = 0;
	int food_testY = 0;
	int item_testX = 0;
	int item_testY = 0;
	int snakePos[100];  //스네이크길이 최대 50으로 제한
	int snakeDir = 1; /* 1 - 오른쪽, 2 - 위, 3 -왼쪽, 4, 아래 값에 따라 스네이크가 출발하는 방향 초기설정*/
	int newItem = 1;
	int selectItem = 0; // 아이템 생성시 선택된 아이템
	int shieldItem = 0; // 무적아이템 유무확인 변수
	int GameStartCheck = 0;
	int lifeCount;
	int foodCount;
	int NeedEscape;		//탈출에 필요한 먹이갯수
	int lifeonecheck; //라이프소진후 1초간무적
	COORD curPos;

	int CloseCheck = 0;	//npc와 가까운지 체크
	int StartRandom;	//npc움직임 랜덤
	int MoveLimit = 0;	//npc랜덤 하게 움직임
	int timecheck = 0;	//방향 움직임 시간체크
	int NPCDA = 0;		//NPC 감지거리


	arraySizeY = 20;
	arraySizeX = arraySizeY;

	if (stageNum == 1)
	{
		lifeCount = 4; //목숨 개수(스테이지별 초기화)
		foodCount = 0; //스테이지 별 먹이 수 제한 
		NeedEscape = 5;
		Speed = 3;
		z = 24;
		NPCDA = 0;
	}
	else if (stageNum == 2)
	{
		lifeCount = 4; //목숨 개수(스테이지별 초기화)
		foodCount = 0; //스테이지 별 먹이 수 제한 
		NeedEscape = 7;
		Speed = 5;
		z = 20;
		NPCDA = 8;
	}
	else if (stageNum == 3)
	{
		lifeCount = 3; //목숨 개수(스테이지별 초기화)
		foodCount = 0; //스테이지 별 먹이 수 제한 
		NeedEscape = 9;
		Speed = 7;
		z = 16;
		NPCDA = 10;
	}
	else if (stageNum == 4)
	{
		lifeCount = 1; //목숨 개수(스테이지별 초기화)
		foodCount = 0; //스테이지 별 먹이 수 제한 
		NeedEscape = 12;
		Speed = 9;
		z = 14;
		NPCDA = 12;
	}

	ItemScreen();
	gotoxy(58, 0);
	printf("♤ : 먹이");
	gotoxy(58, 1);
	printf("△,0 : 스피드 업 (Q 입력 시 사용가능)");
	gotoxy(58, 2);
	printf("▽ : 스피드 다운");
	gotoxy(58, 3);
	printf("●,2 : 지렁이 길이 +1 (Q 입력 시 사용가능)");
	gotoxy(58, 4);
	printf("○ : 지렁이 길이 -1");
	gotoxy(58, 5);
	printf("★,4 : 무적 (Q 입력 시 사용가능)");
	gotoxy(58, 6);
	printf("■ : 생명 -1 ");
	gotoxy(58, 7);
	printf("♬ : 생명 3 이하일 경우 생명 추가");
	gotoxy(58, 8);
	printf("@ : 2탄 부터 움직이는 적 등장!");

	arr = (char*)malloc(arraySizeX * arraySizeY * sizeof(char));            //메모리값 오류
	if (arr == NULL)
	{
		printf("cannot allocate memory\n"); _getch();
	}

	for (i = 0; i < arraySizeX * arraySizeY; i++) arr[i] = ' '; //맵 공백 초기화
																// XY벽 생성 
	for (i = 0; i < arraySizeX * arraySizeY; i++)
	{

		if (i < arraySizeX) arr[i] = '-';
		else if (i % arraySizeX == 0) { arr[i] = '|'; }
		else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '-';
		else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|';
	}
	gotoxy(42, 0);
	printf("■■■■■■■");
	gotoxy(42, 1);
	printf("■ L I F E  ■");
	gotoxy(42, 2);
	printf("■■■■■■■");
	gotoxy(42, 4);
	printf("■■■■■■■");

	while (1)	//게임 사이클 시작부분
	{


		lifeonecheck = 0;
		Dead = 0;
		CurrentDir = 0;
		CheckFoodCoord = 0;
		izqdeGolemiq = 0;
		newFood = 1;
		Key = 0;
		createItem = 10;  // 아이템이 사라지기 전 움직일 수 있는 최대값
		foodCount = limitFoodByStage(stageNum);
		snakeSize = 3;
		SetCharacterPosition(snakePos, snakeSize, 2, snakeDir); // 뱀 고정 위치 설정
		for (j = 0; j < 100; j++) snakePos[j] = 1; //스네이크 포지션 1로 초기화



		while (1)
		{
			if (lifeonecheck == 1)
			{
				if (second % 2 == 0)
				{
					lifeonecheck = 0;
				}
			}

			int C_arrX[MAX];
			int C_arrY[MAX];
			int c = 0;
			z--;
			createItem--;

			if (z == 0) newFood = 1;
			if (createItem == 0) newItem = 1;
			// z값의 한계치가 넘어가면 음식 다시생기게하는 부분

			gotoxy(2, 20);
			printf("%d : 탈출까지 길어져야 하는 목표 갯수", NeedEscape - snakeSize + 3);


			izqdeGolemiq = 0;
			CurrentDir = snakeDir;


			for (i = 0; i < arraySizeX * arraySizeY; i++)  //맵 가장자리 생성
			{
				if (i < arraySizeX) arr[i] = '-';             //맨 위쪽 벽
				else if (i % arraySizeX == 0) { arr[i] = '|'; } //왼쪽 벽
				else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '-'; //맨아래 벽
				else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|'; //오른쪽 벽
				else arr[i] = ' ';
			}

			/*음식을 생성하는 부분 좌표중 +부분에 생성, 이동 한계치 초과시 음식 재생성 구간 및 음식 포지션 설정(뱀과의 위치에서 일정하게 떨어져야지 생성됨) */
			if (newFood)

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
				selectItem = rand() % 7; // 아이템 랜덤으로 출력 하기 위해 난수생성
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

			/* 스네이크 벽충돌및 음식충돌 검사(음식충돌시 스네이크 길이+1) dead=1이 될시 사망처리 */
			for (i = 0; i < snakeSize; i++)           //충돌 체크
			{
				/* 음식과 충돌체크*/
				if ((snakePos[2 * i] == foodPos[0]) && (snakePos[2 * i + 1] == foodPos[1]))
				{
					newFood = 1;
					//스네이크 길이 최대치 25이상x
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
					case 5: //■ : 벽
						lifeCount--;
						SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
						break;
					case 6://♬ : 목숨 +1
						if (lifeCount<3)
						{
							lifeCount++;
							gotoxy(58, 9);
							printf("♥이 추가 되었어요!!");
						}
						break;

					}

				}
				/* 벽과충돌체크*/
				if (!izqdeGolemiq)
				{
					if ((arr[snakePos[2 * snakeSize - 1] * arraySizeX + snakePos[2 * snakeSize - 2]] == '-') || (arr[snakePos[2 * snakeSize - 1] * arraySizeX + snakePos[2 * snakeSize - 2]] == '|'))
					{
						if (shieldItem)
						{
							shieldItem = 0;
							snakeDir = 1;
							SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
						}
						else
						{
							if (lifeonecheck == 0)
							{
								lifeCount--;
								snakeDir = 1;
								SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
							}

						}
					}
				}
				/* 지렁이가 자신의 몸에 충돌 하는지 검사하는 부분  */
				if (i != (snakeSize - 1))
				{
					if ((snakePos[2 * (snakeSize - 1)] == snakePos[2 * i]) && (snakePos[2 * (snakeSize - 1) + 1] == snakePos[2 * i + 1]))
					{
						if (lifeonecheck == 0)
						{
							lifeCount--;
							snakeDir = 1;
							SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
						}


					}
				}
			}

			if (lifeCount < 0)
				Dead = 1;
			/* snakedir 값 변경시 초기 지렁이 이동방향 설정가능 */
			/* 스네이크 이동 및 음식 좌표 */
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
			/* snakedir값에 따른 스네이크 이동 */
			for (i = 0; i < snakeSize - 1; i++)
			{
				snakePos[2 * i] = snakePos[2 * i + 2];
				snakePos[2 * i + 1] = snakePos[2 * i + 3];
			}

			if (snakeDir == 1) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4] + 1; snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3]; } // move right
			if (snakeDir == 2) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4];      snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3] - 1; } // move up
			if (snakeDir == 3) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4] - 1; snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3]; } // move left
			if (snakeDir == 4) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4];      snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3] + 1; } // move down

																																								  /* 뱀출력 */
			for (i = 0; i < snakeSize; i++)
			{
				arr[snakePos[2 * i + 1] * arraySizeX + snakePos[2 * i]] = '*';  // 뱀 모양
			}

			/*음식 좌표(배열)값 배정 */
			if (foodPos[0] == 0 && foodPos[1] == 0)
				arr[foodPos[1] * arraySizeX + foodPos[0]] = '-';
			else
				arr[foodPos[1] * arraySizeX + foodPos[0]] = '+';

			/*아이템 좌표(배열)값 배정 */
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
			case 5: //■ : 벽
				arr[itemPos[1] * arraySizeX + itemPos[0]] = '1';
				break;
			case 6: //♬ : 목숨 +1
				arr[itemPos[1] * arraySizeX + itemPos[0]] = '2';
				break;
			}

			gotoxy(0, 0);

			//게임판 그리기
			for (i = 0; i < arraySizeX; i++)
			{
				void hidecursor();

				for (j = 0; j < arraySizeY; j++)
				{
					if (arr[i * arraySizeX + j] == '-')
					{
						if (lifeCount == 0)
						{
							YELLOW;
						}
						printf("■");
						WHITE;
					}
					else if (arr[i * arraySizeX + j] == '|')
					{
						if (lifeCount == 0)
						{
							YELLOW;
						}
						printf("■");
						WHITE;
					}
					else if (arr[i * arraySizeX + j] == ' ')
					{
						printf("  ");
					}
					else if (arr[i * arraySizeX + j] == '*') //지렁이 모양 
					{
						printf("●");
						curPos = GetCurrentCursorPos();

						C_arrX[c] = curPos.X;
						C_arrY[c] = curPos.Y;
						c++;
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
					else if (arr[i * arraySizeX + j] == '1') //■ : 벽돌
					{
						printf("■");
					}
					else if (arr[i * arraySizeX + j] == '2') //♬ : 생명 +1
					{
						printf("♬");
					}
				}
				printf("\n");
			}

			/////////////////적 캐릭터 구현부///////////////////////////////////
			if (stageNum > 1)
			{
				timecheck = second;

				if (second % 2 == 0)
				{
					timecheck++;
				}
				if (GameStartCheck == 0)
				{
					gotoxy(NPCX, NPCY);
					printf("＠");
				}
				if (MoveLimit == 0)
				{
					srand((unsigned int)time(NULL));
					StartRandom = (rand() % 4) + 1;
					MoveLimit = 1;
				}
				else if (timecheck > 5)
				{
					MoveLimit = 0;
					timecheck = 0;
				}

				if (curPos.X == NPCX && NPCY - curPos.Y <= NPCDA && NPCY - curPos.Y >= 0) //up
				{
					CloseCheck = 1;

				}
				else if (curPos.X == NPCX && curPos.Y - NPCY <= NPCDA && curPos.Y - NPCY >= 0) //down
				{
					CloseCheck = 1;
				}
				else if (curPos.Y == NPCY && curPos.X - NPCX <= NPCDA * 2 && curPos.X - NPCX >= 0)//right
				{
					CloseCheck = 1;
				}
				else if (curPos.Y == NPCY && NPCX - curPos.X <= NPCDA * 2 && NPCX - curPos.X >= 0)//left
				{
					CloseCheck = 1;
				}
				else
				{
					gotoxy(NPCX, NPCY);
					WHITE;
					printf("＠");
					CloseCheck = 0;

					if (StartRandom == 1)	//위
					{

						if (NPCY == 1)
						{
							MoveLimit = 0;
						}
						else
							NPCY--;
					}
					else if (StartRandom == 2)	//아래
					{

						if (NPCY == 18)
						{
							MoveLimit = 0;
						}
						else
							NPCY++;
					}
					else if (StartRandom == 3)	//오른쪽
					{
						if (NPCX == 18)
						{
							MoveLimit = 0;
						}
						else
							NPCX += 2;

					}
					else if (StartRandom == 4)	//왼쪽
					{
						if (NPCX == 2)
						{
							MoveLimit = 0;
						}
						else
							NPCX -= 2;

					}
				}
				if (CloseCheck == 1)
				{

					gotoxy(NPCX, NPCY);
					RED;
					printf("＠");
					WHITE;



					if (curPos.X == NPCX && NPCY - curPos.Y <= NPCX && NPCY - curPos.Y >= 0) //up
					{
						NPCY--;
					}
					else if (curPos.X == NPCX && curPos.Y - NPCY <= NPCX && curPos.Y - NPCY >= 0) //down
					{
						NPCY++;
					}
					else if (curPos.Y == NPCY && curPos.X - NPCX <= NPCX && curPos.X - NPCX >= 0)//right
					{
						NPCX += 2;
					}
					else if (curPos.Y == NPCY && NPCX - curPos.X <= NPCX && NPCX - curPos.X >= 0)//left
					{
						NPCX -= 2;
					}

				}
				for (int i = 0; i < snakeSize; i++)
				{
					if (C_arrX[i] == NPCX && C_arrY[i] == NPCY)
					{
						if (lifeonecheck == 0)
						{
							lifeCount--;
							snakeDir = 1;
							NPCX = NPCY = 10;
							SetCharacterPosition(snakePos, snakeSize, 2, snakeDir);
						}
					}
				}
			}

			///////////////////////////////////


			switch (lifeCount)
			{
			case 0: gotoxy(42, 3); printf("■  ■  ■  ■"); break;
			case 1: gotoxy(42, 3); printf("■♡■  ■  ■"); break;
			case 2: gotoxy(42, 3); printf("■♡■♡■  ■"); break;
			case 3: gotoxy(42, 3); printf("■♡■♡■♡■"); break;
			default: break;
			}


			/* 죽음시 break로 탈출,키보드로 뱀 이동*/
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
					_getch();
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
				get();
			}

			if (snakeDir != CurrentDir)
			{
				/*값에따라 반대쪽 이동제한 ex)오른쪽 이동중이면 반대편인 왼쪽으로 이동불가*/
				if (snakeDir == 2 && CurrentDir == 4) snakeDir = 4;
				if (snakeDir == 1 && CurrentDir == 3) snakeDir = 3;
				if (snakeDir == 4 && CurrentDir == 2) snakeDir = 2;
				if (snakeDir == 3 && CurrentDir == 1) snakeDir = 1;
			}
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
