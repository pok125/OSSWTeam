#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
/*
Config file:  config.cfg
content:
arraySizeX               16 // these two values should be equal
arraySizeY               16 // no bigger than 16
StartingDirection         2  // 0 - random.  1 - nadqsno, 2 - nagore, 3 -nalqvo, 4, nadolu
snakeSize               5  // no longer than 5;
IncreaseSpeedOnEveryFood   1
The config value is opened only if the user choose '0' for the size of the array.
*/


void gotoxy(int x, int y)
{

	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);

}

void hidecursor()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	ConCurInf.dwSize = 1;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(hOut, &ConCurInf);
}

int main()
{
	FILE *fp;
	int NUMBER_OF_CONFIG_ELEMENTS = 5;
	int STARTING_DIRECTION = 0;
	int INITIAL_SNAKE_SIZE = 3;
	int INCREASE_SPEED_ON_EVERY_FOOD = 0;
	char newGameChoice = 0;
	char Key;
	int CurrentDir = 0;
	int direction_snake = 0;
	int Dead = 0;
	int i, j, z;
	int Speed;
	char *arr = NULL;
	int CheckFoodCoord = 0;
	char unused[30];
	int arraySizeX = 16;
	int arraySizeY = 16;
	int newFood = 1;
	int NoNewGame = 0;
	int foodPos[2];
	int izqdeGolemiq = 0;
	int food_testX = 0;
	int food_testY = 0;
	int ChetemConfig = 0;
	int snakePos[100];  //x,y pos for 50 snake elements. If the snake is getting bigger -> malloc for new 10 elements
	int snakeSize = 3;
	int snakeDir = 1; /* 1 - nadqsno, 2 - nagore, 3 -nalqvo, 4, nadolu */
	COORD pos = { 0, 0 };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	//while (1)                 //초기 스테이지 크기 설정
	//{
	//   fflush(stdin);
	//   printf("Game window size (16 - 25)\nEnter '0' to use config file values");
	//   scanf("%d", &arraySizeX);

	//   if ((!(arraySizeX < 16 || arraySizeX > 25)) || (arraySizeX == 0)) break;
	//}
	/*
	Speed = 5;
	arraySizeY = 20;
	arraySizeX = arraySizeY*2;*/


	Speed = 5;
	arraySizeY = 20;
	arraySizeX = arraySizeY;
	//if (arraySizeX == 0)          //디폴트파일 설정 불러오기
	//{
	//   ChetemConfig = 1;
	//   fp = fopen("config.cfg", "rt");
	//   if (fp == NULL)
	//   {
	//      printf("Cannot find config file. Check existance or start new game and choose value between 16-25 for window game size\nGame will now exit.");
	//      _getch();
	//      return 0;
	//   }
	//   for (i = 0; i < NUMBER_OF_CONFIG_ELEMENTS; i++)
	//   {
	//      if (i == 0) fscanf(fp, "%s%d", unused, &arraySizeX);
	//      if (i == 1) fscanf(fp, "%s%d", unused, &arraySizeY);
	//      if (i == 2) fscanf(fp, "%s%d", unused, &STARTING_DIRECTION);
	//      if (i == 3) fscanf(fp, "%s%d", unused, &INITIAL_SNAKE_SIZE);
	//      if (i == 4) fscanf(fp, "%s%d", unused, &INCREASE_SPEED_ON_EVERY_FOOD);
	//   }
	//   fclose(fp);
	//}


	arr = malloc(arraySizeX * arraySizeY * sizeof(char));            //메모리값 오류
	if (arr == NULL)
	{
		printf("cannot allocate memory\n"); _getch();
	}

	for (i = 0; i < arraySizeX * arraySizeY; i++) arr[i] = ' '; //맵 공백 초기화
																/* Create the frame arraySizeX * arraySizeY */




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





	for (i = 0; i < arraySizeX * arraySizeY; i++)
	{

		if (i < arraySizeX) arr[i] = '-';
		else if (i % arraySizeX == 0) { arr[i] = '|'; }
		else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '-';
		else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|';
		//else arr[i] = ' '; 
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
		if (!ChetemConfig) snakeSize = 3;
		else snakeSize = INITIAL_SNAKE_SIZE;
		z = 24; /* iterator for game life cycle - used to count moves after food appearence         z는 음식이 사라지기 전 움직일 수 있는 최대값*/
				/* this value should be afunction of the field size - if it si 16 -> then we have to have at least 24 moves before food dissapear*/
				/* Input validation for speed*/


				//while (1)            // 스네이크 speed 설정 부분
				//{
				//   system("cls");
				//   printf("During the game- press ESC to exit.. or DIE !\nSpeed level: (1-40)\n");
				//   fflush(stdin);
				//   scanf("%d", &Speed);
				//   if (Speed > 40) Speed = 40;
				//   if (!(Speed <= 0)) break; /* challenging levels up to speed = 30*/
				//}

				//system(cls); 추가하기  - 콘솔창 클리어


				/* Initialize snakePos with size 3 */
				//snakePos[0] = 8;  //    ------------  //Illustration, not actual represntation
				//snakePos[1] = 8;  //    ------------
				//snakePos[2] = 9;  //    ----***-----
				//snakePos[3] = 8;  //    ------------
				//snakePos[4] = 10;
				//snakePos[5] = 8;

		for (i = 0; i < snakeSize; i++)   //뱀 위치 랜덤 설정
		{
			if (i == 0)
			{
				while (1)
				{
					snakePos[i] = 1 + rand() % (arraySizeX - 2);
					snakePos[2 * i + 1] = 1 + rand() % (arraySizeX - 2);
					if ((snakePos[i] - (snakeSize + 1)) > 0 && (snakePos[i] + (snakeSize + 1)) < arraySizeX && (snakePos[2 * i + 1] - (snakeSize + 1)) > 0 && (snakePos[2 * i + 1] + (snakeSize + 1)) < arraySizeX)
						break;
				}
			}
			else
			{
				if (i == 1)
				{
					if (STARTING_DIRECTION == 0)
						direction_snake = 1 + rand() % 4;
					else
						direction_snake = STARTING_DIRECTION;
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
		fflush(stdin);

		while (1)
		{
			z--;
			if (z == 0) newFood = 1;
			/* Clear the screen and print the matrix and snake again */
			// z가 25번 넘어가면 음식 다시생기게하는 부분

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
				foodPos[0] = food_testX;
				foodPos[1] = food_testY;
				z = arraySizeX * 2;
				newFood = 0;
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
				/* wall check 벽돌과 충돌시*/
				if (!izqdeGolemiq)
				{
					if ((arr[snakePos[2 * snakeSize - 1] * arraySizeX + snakePos[2 * snakeSize - 2]] == '-') || (arr[snakePos[2 * snakeSize - 1] * arraySizeX + snakePos[2 * snakeSize - 2]] == '|'))
					{
						Dead = 1;
					}
				}
				else
				{
					if ((arr[snakePos[2 * snakeSize - 3] * arraySizeX + snakePos[2 * snakeSize - 4]] == '-') || (arr[snakePos[2 * snakeSize - 3] * arraySizeX + snakePos[2 * snakeSize - 4]] == '|'))
					{
						Dead = 1;
					}
				}
				/* snake self-impact check */
				if (i != (snakeSize - 1))
				{
					if ((snakePos[2 * (snakeSize - 1)] == snakePos[2 * i]) && (snakePos[2 * (snakeSize - 1) + 1] == snakePos[2 * i + 1]))
					{
						Dead = 1;
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

			/* Create the frame arraySizeX * arraySizeY */
			//for (i = 0; i < arraySizeX * arraySizeY; i++)
			//{

			//   if (i < arraySizeX) arr[i] = '-';
			//   else if (i % arraySizeX == 0) { arr[i] = '|'; }
			//   else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '-';
			//   else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|';
			//   //else arr[i] = ' ';
			//}

			/* Put the food on the matrix */
			arr[foodPos[1] * arraySizeX + foodPos[0]] = '+';
			//system("cls");
			pos.X = 0;
			pos.Y = 0;
			SetConsoleCursorPosition(output, pos);
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


			/* if condition Dead is satisfied -> break  키보드로 뱀 이동*/
			Key = 0;
			if (Dead) break;
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
			while (1)
			{
				printf("U R dead ! Game over\nStart new game? (Y/N and press ENTER)\n");
				fflush(stdin);
				scanf("%c", &newGameChoice);
				if (newGameChoice == 'n' || newGameChoice == 'N')
				{
					NoNewGame = 1; break;
				}
				if (newGameChoice == 'y' || newGameChoice == 'Y') break;
				system("cls");
			}
		}
		else
		{
			printf("Game over\n");
			break;
		}
		if (NoNewGame);

	}
	_getch();
	return 0;
}