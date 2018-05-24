
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
Config 파일 안의 내용 (게임 환경 초기 설정 값들)
Config file:  config.cfg
content:

arraySizeX					16 // these two values should be equal
arraySizeY					16 // no bigger than 16
StartingDirection			2  // 0 - random.  1 - nadqsno, 2 - nagore, 3 -nalqvo, 4, nadolu
snakeSize					5  // no longer than 5;
IncreaseSpeedOnEveryFood	1

The config value is opened only if the user choose '0' for the size of the array.
*/
int main()
{
	FILE *fp;
	int NUMBER_OF_CONFIG_ELEMENTS = 5;
	int STARTING_DIRECTION = 0;			//초기 방향 설정
	int INITIAL_SNAKE_SIZE = 3;			//초기 지렁이 사이즈
	int INCREASE_SPEED_ON_EVERY_FOOD = 0;//먹이 먹으면 스피드 증가 여부->추후 변수 삭제
	char newGameChoice = 0;				//새로운 게임 시작 여부  Y/N으로 구분
	char Key;
	int CurrentDir = 0;					//현재 방향
	int direction_snake = 0;			//지렁이 방향
	int Dead = 0;						//game over 여부
	int i, j, z;		
	int Speed;							//스피드 변수
	char *arr = NULL;					
	int CheckFoodCoord = 0;				//먹이 좌표 체크 변수
	char unused[30];
	int arraySizeX = 16;				//게임보드 가로
	int arraySizeY = 16;				//게임보드 세로
	int newFood = 1;					//새 먹이 생성 여부
	int NoNewGame = 0;
	int foodPos[2];						//먹이 좌표
	int izqdeGolemiq = 0;				//먹이를 먹었는 지 여부를 알려주는 변수 //먹이 충돌 시에만 값 1
	int food_testX = 0;					//새 먹이 생성 전 temp좌표
	int food_testY = 0;					//새 먹이 생성 전 temp좌표
	int ChetemConfig = 0;
	int snakePos[100];  //x,y pos for 50 snake elements. If the snake is getting bigger -> malloc for new 10 elements
	int snakeSize = 3;
	int snakeDir = 1; /* 1 - nadqsno, 2 - nagore, 3 -nalqvo, 4, nadolu */
	COORD pos = { 0, 0 };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int textColor = 7; //기본 컬러 하얀색 


	while (1)
	{
		fflush(stdin);
		printf("Game window size (16 - 25)\nEnter '0' to use config file values");
		scanf("%d", &arraySizeX);

		if ((!(arraySizeX < 16 || arraySizeX > 25)) || (arraySizeX == 0)) break;
		//
	}
	arraySizeY = arraySizeX;

	if (arraySizeX == 0) //처음 게임 시작 시 0 입력하면 초기세팅을 파일에서 받아서 해줌
	{
		ChetemConfig = 1;
		fp = fopen("config.cfg", "rt");
		if (fp == NULL)
		{
			printf("Cannot find config file. Check existance or start new game and choose value between 16-25 for window game size\nGame will now exit.");
			_getch();
			return 0;
		}
		for (i = 0; i < NUMBER_OF_CONFIG_ELEMENTS; i++)
		{
			if (i == 0) fscanf(fp, "%s%d", unused, &arraySizeX);
			if (i == 1) fscanf(fp, "%s%d", unused, &arraySizeY);
			if (i == 2) fscanf(fp, "%s%d", unused, &STARTING_DIRECTION);
			if (i == 3) fscanf(fp, "%s%d", unused, &INITIAL_SNAKE_SIZE);
			if (i == 4) fscanf(fp, "%s%d", unused, &INCREASE_SPEED_ON_EVERY_FOOD);
		}
		fclose(fp);
	}

	arr = malloc(arraySizeX * arraySizeY * sizeof(char));
	if (arr == NULL)
	{
		printf("cannot allocate memory\n"); _getch();
	}

	while (1)
	{ // new game cycle
		srand(time(NULL));

		for (i = 0; i < arraySizeX * arraySizeY; i++) arr[i] = ' ';
		for (j = 0; j < 100; j++) snakePos[j] = 1;
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
			
		z = 24; /* iterator for game life cycle - used to count moves after food appearence */
				/* this value should be afunction of the field size - if it si 16 -> then we have to have at least 24 moves before food dissapear*/
				/* Input validation for speed*/
		while (1) //초기 설정값 
		{
			system("cls");
			printf("During the game- press ESC to exit.. or DIE !\nSpeed level: (1-40)\n");
			fflush(stdin);
			scanf("%d", &Speed);
			if (Speed > 40) Speed = 40;
			if (!(Speed <= 0)) break; /* challenging levels up to speed = 30*/
		}

		/* Initialize snakePos with size 3 */
		//snakePos[0] = 8;  //    ------------  //Illustration, not actual represntation
		//snakePos[1] = 8;  //    ------------
		//snakePos[2] = 9;  //    ----***-----
		//snakePos[3] = 8;  //    ------------
		//snakePos[4] = 10;
		//snakePos[5] = 8;

		for (i = 0; i < snakeSize; i++)
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

		//-----------------------------------------------------------------------------------------------
		while (1)
		{
			if (z < 5)
				textColor = 12; //빨간색 
			else
				textColor = 7;
			z--; 
			if (z == 0) newFood = 1; //일정 움직임 뒤에도 먹이 먹지 못하면 사라지게
			/* Clear the screen and print the matrix and snake again */

			izqdeGolemiq = 0;
			CurrentDir = snakeDir;

			/* Create the frame arraySizeX * arraySizeY */
			for (i = 0; i < arraySizeX * arraySizeY; i++)
			{

				if (i < arraySizeX) arr[i] = '-';
				else if (i % arraySizeX == 0) { arr[i] = '|'; }
				else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '-';
				else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|';
				else arr[i] = ' ';
			}

			/* Create the food - place '+' on a random coordinates different than the snake coordinates */
			//+ 표시가 먹이 
			//newFood 1이면 화면에 먹이가 없음을 의미
			if (newFood)
			{
				CheckFoodCoord = 0; //지렁이와 
				/*랜덤으로 지정한 먹이 좌표가 지렁이 좌표와 겹치는 지 확인하는 for 구문
				겹치는 유무 확인 변수 CheckFoodCoord 
				지렁이와 겹치지 않으면  CheckFoodCoord 0->1로 변경*/
				for (;;) 
				{
					food_testX = 1 + rand() % (arraySizeX - 2);
					food_testY = 1 + rand() % (arraySizeY - 2);
					for (i = 0; i < snakeSize; i++)
					{
						if ((snakePos[2 * i] != food_testX) && (snakePos[2 * i + 1] != food_testY))
							CheckFoodCoord = 1; //지렁이와 좌표가 겹치지 않으면 값 1로 변경 
					}
					if (CheckFoodCoord) break; //지렁이와 좌표 겹치지 않으면 break; 루프 탈출 
				}
				//새로운 먹이 좌표 설정
				foodPos[0] = food_testX;  
				foodPos[1] = food_testY;
				z = arraySizeX * 2; //적어도 화면 사이즈 이상의 move수는 주어져야 지렁이가 먹이를 먹을 수 있음 
				newFood = 0; //화면에 먹이 생성 되었으므로 newFood 변수 0으로 변경
			}

			/* Check snake coordinates for food for impact or walls - for food -> increase snake_size +1; - for impact and walls -> Dead = 1 */
			for (i = 0; i < snakeSize; i++)
			{
				/* 먹이 충돌검사
				지렁이 좌표와 먹이 좌표가 충돌 시 */
				if ((snakePos[2 * i] == foodPos[0]) && (snakePos[2 * i + 1] == foodPos[1]))
				{
					newFood = 1; //화면에 먹이 없음을 알려줌 
					/* the snake cannot be longer than 25 elements. */
					if (snakeSize < 50) snakeSize++; //지렁이 사이즈 증가
					izqdeGolemiq = 1; //먹이를 먹었는 지 여부를 알려주는 변수 //먹이 충돌 시에만 값 1
					if (INCREASE_SPEED_ON_EVERY_FOOD && (Speed < 40))Speed++; //스피드 증가
				}
				/* wall check */
				//먹이를 먹으면 지렁이 사이즈 변경되므로 
				//먹이먹은 경우, 먹이 안 먹은 경우 벽충돌 구분
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
			//먹이 먹었을 시 지렁이 좌표 다시 설정 
			if (izqdeGolemiq)
			{
				for (i = snakeSize; i > 1; i--)
				{
					snakePos[2 * i - 1] = snakePos[2 * i - 3];
					snakePos[2 * i - 2] = snakePos[2 * i - 4];
				}
				//먹이를 먹은 방향에 따라 새로 증가된 지렁이 길이 좌표 설정 
				if (snakeDir == 1) { snakePos[0] = snakePos[2] - 1; snakePos[1] = snakePos[3]; } // move right
				if (snakeDir == 2) { snakePos[0] = snakePos[2];	   snakePos[1] = snakePos[3] + 1; } // move up
				if (snakeDir == 3) { snakePos[0] = snakePos[2] + 1; snakePos[1] = snakePos[3]; } // move left
				if (snakeDir == 4) { snakePos[0] = snakePos[2];	   snakePos[1] = snakePos[3] - 1; } // move down
			}

			/* move array - dir condition */
			//방향키 변경 시 지렁이 좌표 다시 설정
			for (i = 0; i < snakeSize - 1; i++)
			{
				snakePos[2 * i] = snakePos[2 * i + 2];
				snakePos[2 * i + 1] = snakePos[2 * i + 3];
			}

			if (snakeDir == 1) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4] + 1; snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3]; } // move right
			if (snakeDir == 2) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4];	   snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3] - 1; } // move up
			if (snakeDir == 3) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4] - 1; snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3]; } // move left
			if (snakeDir == 4) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4];	   snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3] + 1; } // move down

																																								/* Create the snake */
			for (i = 0; i < snakeSize; i++)
			{
				arr[snakePos[2 * i + 1] * arraySizeX + snakePos[2 * i]] = '*';
			}

			/* Create the frame arraySizeX * arraySizeY */
			for (i = 0; i < arraySizeX * arraySizeY; i++)
			{

				if (i < arraySizeX) arr[i] = '-';
				else if (i % arraySizeX == 0) { arr[i] = '|'; }
				else if (i > arraySizeX * (arraySizeY - 1)) arr[i] = '-';
				else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|';
				//else arr[i] = ' ';
			}

			/* Put the food on the matrix */
			//먹이 그리는 부분 
			SetConsoleTextAttribute(hOut, textColor);
			arr[foodPos[1] * arraySizeX + foodPos[0]] = '+';
			

			//system("cls");
			pos.X = 0;
			pos.Y = 0;
			SetConsoleCursorPosition(output, pos);

			/* print the matrix with the snake and the food*/
			//게임보드 전체 그리는 부분 
			for (i = 0; i < arraySizeX; i++)
			{
				for (j = 0; j < arraySizeY; j++)
				{
					printf("%c", arr[i * arraySizeX + j]);
				}
				printf("\n");
			}

			/* if condition Dead is satisfied -> break */
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
		//while문 끝 -------------------------------------------------------------------------------------------------

		if (Dead)
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
		if (NoNewGame) break;
	}
	_getch();
	return 0;
	//업데이트 확인
}
