#pragma once
#include<time.h>
#include"CPlayer.h"

enum bDirection
{
	STOP = 0,
	LEFT = 1,
	UPLEFT = 2,
	DOWNLEFT = 3,
	RIGHT = 4,
	UPRIGHT = 5,
	DOWNRIGHT = 6
};

//==============================
//==============================
class CBall
{
private:
	COORD _Coord;
	bDirection _Dir;
public:
	CBall();
	~CBall();

	COORD getCoord();
	bDirection getDir();

	bool isHitBy(CPlayer1*);
	bool isCollided(int);
	bool isGoal(int);
	
	void Generate(int, int);
	void Direct(CPlayer1*);
	void Direct();
	void Move();
};

//==============================
//==============================
CBall::CBall()
{
	_Coord = { 0,0 };
	_Dir = STOP;
}

CBall::~CBall()
{
	return;
}

COORD CBall::getCoord()
{
	return _Coord;
}

bDirection CBall::getDir()
{
	return _Dir;
}

bool CBall::isHitBy(CPlayer1* _player)
{
	int paddleCoordX = _player->getPaddleCoord().X;
	int paddleCoordY = _player->getPaddleCoord().Y;

	if (_Coord.Y >= paddleCoordY + 0
	 && _Coord.Y <= paddleCoordY + 4)	//paddleCoordY + 0 -> 4 is the vertical length of the paddle (hitting anywhere in range is counted)
		return (_Coord.X == paddleCoordX + 1 && _Dir >= LEFT && _Dir <= DOWNLEFT)
			|| (_Coord.X == paddleCoordX - 1 && _Dir >= RIGHT && _Dir <= DOWNRIGHT);
		//paddleCoordX +- 1 so the ball doesn't fly into the paddles on both sides (just bounces onto them)
		//_Dir in {LEFT, UPLEFT, DOWNLEFT} means the ball is being hit by 1st player (left) so we +1
		//_Dir in {RIGHT, UPRIGHT, DOWNRIGHT} means the ball is being hit by 2nd player (right) so we -1

	return false;
}

bool CBall::isCollided(int _fieldHeight)
{
	return _Coord.Y <= 0 || _Coord.Y >= _fieldHeight - 1;
}

bool CBall::isGoal(int _fieldWidth)
{
	return _Coord.X <= 0 || _Coord.X >= _fieldWidth - 1;
}

void CBall::Generate(int _fieldHeight, int _fieldWidth)
{
	srand((unsigned)time(NULL));

	SHORT initialCoordX = _fieldWidth / 2 + rand() % 5;
	SHORT initialCoordY = _fieldHeight / 2 + rand() % 5;

	_Coord = {initialCoordX, initialCoordY};
	_Dir = (bDirection)(rand() % 6 + 1);
}

void CBall::Direct(CPlayer1* _player)
{
	pDirection paddledir = _player->getPaddleDir();

	srand((unsigned)time(NULL));

	if (_Dir == UPLEFT || _Dir == DOWNLEFT)
	{
		_Coord.X += rand() % 2;

		if (paddledir == pUP)
		{
			_Dir = UPRIGHT;
			_Coord.Y -= rand() % 3;
		}
		else
		{
			_Dir = DOWNRIGHT;
			_Coord.Y += rand() % 3;
		}

		return;
	}

	if (_Dir == UPRIGHT || _Dir == DOWNRIGHT)
	{
		_Coord.X -= rand() % 2;

		if (paddledir == pUP)
		{
			_Dir = UPLEFT;
			_Coord.Y -= rand() % 3;
		}
		else
		{
			_Dir = DOWNLEFT;
			_Coord.Y += rand() % 3;
		}

		return;
	}

	if (_Dir == LEFT)
		_Dir = (bDirection)(_Dir + 3);
	else
		_Dir = (bDirection)(_Dir - 3);

	/*switch (paddledir)
	{
	case pUP:
	{
		if (_Dir == UPLEFT || _Dir == DOWNLEFT)
		{
			_Dir = UPRIGHT;
			_Coord.X += rand() % 2;
			_Coord.Y -= rand() % 3;
			break;
		}

		if (_Dir == UPRIGHT || _Dir == DOWNRIGHT)
		{
			_Dir = UPLEFT;
			_Coord.X -= rand() % 2;
			_Coord.Y -= rand() % 3;
			break;
		}
		
		if (_Dir == LEFT)
			_Dir = (bDirection)(_Dir + 3);
		else
			_Dir = (bDirection)(_Dir - 3);

		break;
	}
	case pDOWN:
	{
		if (_Dir == LEFT || _Dir == DOWNLEFT)
		{
			_Dir = DOWNRIGHT;
			_Coord.X += rand() % 2;
			_Coord.Y += rand() % 3;
			break;
		}
			
		if (_Dir == RIGHT || _Dir == DOWNRIGHT)
		{
			_Dir = DOWNLEFT;
			_Coord.X -= rand() % 2;
			_Coord.Y += rand() % 3;
			break;
		}
	
		break;
	}
	}*/
}

void CBall::Direct()
{
	switch (_Dir)
	{
	case UPLEFT:
		_Dir = DOWNLEFT;
		break;
	case DOWNLEFT:
		_Dir = UPLEFT;
		break;
	case UPRIGHT:
		_Dir = DOWNRIGHT;
		break;
	case DOWNRIGHT:
		_Dir = UPRIGHT;
		break;
	}
}

void CBall::Move()
{
	switch (_Dir)
	{
	case STOP:
		break;
	case LEFT:
		_Coord.X--;
		break;
	case UPLEFT:
		_Coord.X--;
		_Coord.Y--;
		break;
	case DOWNLEFT:
		_Coord.X--;
		_Coord.Y++;
		break;
	case RIGHT:
		_Coord.X++;
		break;
	case UPRIGHT:
		_Coord.X++;
		_Coord.Y--;
		break;
	case DOWNRIGHT:
		_Coord.X++;
		_Coord.Y++;
		break;
	}
}