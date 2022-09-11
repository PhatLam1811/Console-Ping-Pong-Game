#pragma once
#include<wincontypes.h>

//==============================
//==============================
class CPlayer1
{
private:
	COORD _paddleCoord;
	int _paddleVerticalDir;
	int _paddleHorizontalDir;
	int _AccelY;
	int _Score;
public:

	CPlayer1();
	~CPlayer1();

	COORD getPaddleCoord();
	int getPaddleVerticalDir();
	int getPaddleHorizontalDir();
	int getScore();

	void Init(SHORT, SHORT);
	void Direct(char);
	void Move(int);
	void Scored();
};

//==============================
//==============================
CPlayer1::CPlayer1()
{
	_paddleCoord = { 0,0 };
	_paddleVerticalDir = 0;
	_paddleHorizontalDir = 0;
	_AccelY = 0;
	_Score = 0;
}

CPlayer1::~CPlayer1()
{
	return;
}

COORD CPlayer1::getPaddleCoord()
{
	return _paddleCoord;
}

int CPlayer1::getPaddleVerticalDir()
{
	return _paddleVerticalDir;
}

int CPlayer1::getPaddleHorizontalDir()
{
	return _paddleHorizontalDir;
}

int CPlayer1::getScore()
{
	return _Score;
}

void CPlayer1::Init(SHORT initialCoordX, SHORT initialCoordY)
{
	_paddleCoord = { initialCoordX, initialCoordY };
	_paddleVerticalDir = 0;

	if (initialCoordX == 1)
		_paddleHorizontalDir = -1;
	else
		_paddleHorizontalDir = 1;

	_AccelY = 0;
	_Score = 0;
}

void CPlayer1::Direct(char inputKey)
{
	switch (inputKey)
	{
	case 'w':
	case 'W':
		if (_paddleCoord.X == 1)
			_paddleVerticalDir = 1;
		break;
	case 'i':
	case 'I':
		if (_paddleCoord.X != 1)
			_paddleVerticalDir = 1;
		break;
	case 's':
	case 'S':
		if (_paddleCoord.X == 1)
			_paddleVerticalDir = -1;
		break;
	case 'k':
	case 'K':
		if (_paddleCoord.X != 1)
			_paddleVerticalDir = -1;
		break;
	default:
		_paddleVerticalDir = 0;
//		if (_AccelY > 0) _AccelY--;
//		if (_AccelY == 0) _paddleVerticalDir = 0;
		break;
	}
}

void CPlayer1::Move(int _heightRange)
{
	if (_paddleVerticalDir == 0)
		return;

	if (_paddleVerticalDir == 1 && _paddleCoord.Y > 0)
		_paddleCoord.Y--;
	
	if (_paddleVerticalDir == -1 && _paddleCoord.Y < _heightRange - 4)
		_paddleCoord.Y++;

//	if (_AccelY < 3) _AccelY++;
}

void CPlayer1::Scored()
{
	_Score++;
}