#pragma once

#pragma once
#include<wincontypes.h>
#include<math.h>
#include"CPlayer1.h"
#include <stdlib.h>
#include <time.h>

class CBall
{
private:
	COORD _Coord;
	int _VerticalDir; // {1: UP, 0: NONE, -1:DOWN}
	int _HorizontalDir; // {1: LEFT, 0: NONE, -1:RIGHT}
	int _AccelX;
	int _AccelY;
public:
	CBall();
	~CBall();

	COORD getCoord();

	bool isHitBy(CPlayer1*);
	bool isCollided(int);
	bool isGoal(int);

	void Generate(int, int);
	void DirectOnHitBy(CPlayer1*);
	void DirectOnColission();
	void Move();
};

CBall::CBall()
{
	_Coord = { 0,0 };
	_VerticalDir = 0;
	_HorizontalDir = 0;
	_AccelY = 0;
	_AccelX = 0;
}

CBall::~CBall()
{
	return;
}

bool CBall::isHitBy(CPlayer1* _pPlayer)
{
	COORD paddleCoord = _pPlayer->getPaddleCoord();

	return _Coord.Y >= paddleCoord.Y
		&& _Coord.Y <= paddleCoord.Y + 3
		&& abs(_Coord.X - paddleCoord.X) == 1;
}

bool CBall::isCollided(int _fieldVerticalRange)
{
	return _Coord.Y == 0 || _Coord.Y == _fieldVerticalRange - 1;
}

bool CBall::isGoal(int _widthRange)
{
	return _Coord.X == 0 || _Coord.X == _widthRange;
}

COORD CBall::getCoord()
{
	return _Coord;
}

void CBall::Generate(int _maxWidth, int _maxHeight)
{
	srand((unsigned)time(NULL));

	_Coord.X = _maxWidth / 2 + rand() % 6 - 4;
	_Coord.Y = _maxHeight / 2 + rand() % 6 - 4;

	bool randomizeVar;

	randomizeVar = rand() % 2;
	_VerticalDir = randomizeVar ? 1 : -1;

	randomizeVar = rand() % 2;
	_HorizontalDir = randomizeVar ? 1 : -1;
}

void CBall::DirectOnHitBy(CPlayer1* _pPlayer)
{
	COORD paddleCoord = _pPlayer->getPaddleCoord();

	int paddleVerticalImpact = _pPlayer->getPaddleVerticalDir();
	int paddleHorizontalImpact = _pPlayer->getPaddleHorizontalDir();

	_HorizontalDir = paddleHorizontalImpact;
	_AccelX = 1;

	if (paddleVerticalImpact != 0 || _VerticalDir == 0)
	{
		_AccelY == paddleVerticalImpact != _VerticalDir ? -1 : 1;
		_VerticalDir = paddleVerticalImpact;
		return;
	}

	if (_Coord.Y >= paddleCoord.Y && _Coord.Y >= paddleCoord.Y + 1)
		_VerticalDir = 1;
	else
		_VerticalDir = -1;

}

void CBall::DirectOnColission()
{
	srand((unsigned)time(NULL));

	_VerticalDir *= -1;
	_AccelY = rand() % 2;
}

void CBall::Move()
{
	if (_VerticalDir > 0) _Coord.Y = _Coord.Y - _AccelY - 1;
	if (_VerticalDir < 0) _Coord.Y = _Coord.Y + _AccelY + 1;
	if (_HorizontalDir > 0) _Coord.X = _Coord.X - _AccelX - 1;
	if (_HorizontalDir < 0) _Coord.X = _Coord.X + _AccelX + 1;
	_AccelY = 0;
	_AccelX = 0;
}