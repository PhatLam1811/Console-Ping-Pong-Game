#pragma once
#include"Declaration.h"

void Setup()
{
	system("cls");

	g_Ball = new CBall();

	g_1stPlayer = new CPlayer1();
	g_2ndPlayer = new CPlayer1();

	g_prevFrame = new CBuffer();
	g_nextFrame = new CBuffer();

	g_Ball->Generate(GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT);
	
	g_1stPlayer->Init(1, 1);
	g_2ndPlayer->Init(GAME_FIELD_WIDTH - 2, GAME_FIELD_HEIGHT - 5);

	g_prevFrame->Init(GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT);
	g_nextFrame->Init(GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT);

	createFieldBorder();
	hideConsoleCursor();
}

char Input()
{
	if (_kbhit())
		return _getch();

	return ' ';
}

void Processing()
{
	char inputKey = Input();

	g_1stPlayer->Direct(inputKey);
	g_2ndPlayer->Direct(inputKey);

	g_1stPlayer->Move(GAME_FIELD_HEIGHT);
	g_2ndPlayer->Move(GAME_FIELD_HEIGHT);

	if (g_Ball->isHitBy(g_1stPlayer))
		g_Ball->DirectOnHitBy(g_1stPlayer);

	if (g_Ball->isHitBy(g_2ndPlayer))
		g_Ball->DirectOnHitBy(g_2ndPlayer);

	if (g_Ball->isCollided(GAME_FIELD_HEIGHT))
		g_Ball->DirectOnColission();

	if (g_Ball->isGoal(GAME_FIELD_WIDTH))
	{
		g_Ball->Generate(GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT);
		Sleep(2000);
	}

	g_Ball->Move();

#pragma region MyRegion
	/*int Y;

	switch (inputKey)
	{
	case 'w':
	case 'W':
	case 's':
	case 'S':
		Y = g_1stPlayer->getPaddleCoord().Y;

		if (inputKey == 'w' || inputKey == 'W')
		{
			if (Y > 1)
				g_1stPlayer->MoveUp();
		}
		else
		{
			if (Y < GAME_FIELD_HEIGHT - 6)
				g_1stPlayer->MoveDown();
		}

		break;
	case 'i':
	case 'I':
	case 'k':
	case 'K':
		Y = g_2ndPlayer->getPaddleCoord().Y;

		if (inputKey == 'i' || inputKey == 'I')
		{
			if (Y > 1)
				g_2ndPlayer->MoveUp();
		}
		else
		{
			if (Y < GAME_FIELD_HEIGHT - 5)
				g_2ndPlayer->MoveDown();
		}

		break;
	}

	if (g_Ball->isHitBy(g_1stPlayer))
		g_Ball->Direct(g_1stPlayer);

	if (g_Ball->isHitBy(g_2ndPlayer))
		g_Ball->Direct(g_2ndPlayer);

	if (g_Ball->isCollided(GAME_FIELD_HEIGHT))
		g_Ball->Direct();

	if (g_Ball->isGoal(GAME_FIELD_WIDTH))
	{
		if (g_Ball->getDir() >= LEFT && g_Ball->getDir() <= DOWNLEFT)
			g_2ndPlayer->Scored();
		else
			g_1stPlayer->Scored();

		Sleep(2000);

		g_Ball->Generate(GAME_FIELD_HEIGHT, GAME_FIELD_WIDTH);
	}

	g_Ball->Move();

	COORD player1Coord = g_1stPlayer->getPaddleCoord();
	COORD player2Coord = g_2ndPlayer->getPaddleCoord();
	COORD ballCoord = g_Ball->getCoord();*/
#pragma endregion

	g_nextFrame->Clear();
	g_nextFrame->updatePlayer(g_1stPlayer->getPaddleCoord());
	g_nextFrame->updatePlayer(g_2ndPlayer->getPaddleCoord());
	g_nextFrame->updateBall(g_Ball->getCoord());
}

void Draw()
{
	for (int Row = 0; Row < GAME_FIELD_HEIGHT; Row++)
		for (int Col = 0; Col < GAME_FIELD_WIDTH; Col++)
			if (g_prevFrame->getField()[Row][Col] != g_nextFrame->getField()[Row][Col])
			{
				setConsoleCursorCoord(Col + 1, Row + 1);
				
				cout << g_nextFrame->getField()[Row][Col];
			}

	g_prevFrame->Imitate(g_nextFrame);
}

void Loop()
{
	while (true)
	{
		Processing();
		Draw();
		Sleep(100);
	}
}

void cleanUp()
{
	delete g_Ball;
	delete g_1stPlayer;
	delete g_2ndPlayer;
	delete g_prevFrame;
	delete g_nextFrame;

	g_Ball = NULL;
	g_1stPlayer = NULL;
	g_2ndPlayer = NULL;
	g_prevFrame = NULL;
	g_nextFrame = NULL;
}

void createFieldBorder()
{
	for (int Row = 0; Row < GAME_FIELD_HEIGHT + 2; Row++)
	{
		setConsoleCursorCoord(0, Row);

		for (int Col = 0; Col < GAME_FIELD_WIDTH + 2; Col++)
		{
			if (Row == 0 && Col == 0)
			{
				cout << '\xC9';
				continue;
			}
				
			if (Row == 0 && Col == GAME_FIELD_WIDTH + 1)
			{
				cout << '\xBB';
				continue;
			}

			if (Row == GAME_FIELD_HEIGHT + 1 && Col == 0)
			{
				cout << '\xC8';
				continue;
			}

			if (Row == GAME_FIELD_HEIGHT + 1 && Col == GAME_FIELD_WIDTH + 1)
			{
				cout << '\xBC';
				continue;
			}

			if (Row == 0 || Row == GAME_FIELD_HEIGHT + 1)
			{
				cout << '\xCD';
				continue;
			}

			if (Col == 0 || Col == GAME_FIELD_WIDTH + 1)
			{
				cout << '\xBA';
				continue;
			}
				
			cout << ' ';
		}
	}
}

void setConsoleCursorCoord(SHORT X, SHORT Y)
{
	static HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	cout.flush();

	COORD cursorCoord = { X, Y };

	SetConsoleCursorPosition(handleOut, cursorCoord);
}

void hideConsoleCursor()
{
	static HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(handleOut, &cursorInfo);

	cursorInfo.bVisible = false;

	SetConsoleCursorInfo(handleOut, &cursorInfo);
}