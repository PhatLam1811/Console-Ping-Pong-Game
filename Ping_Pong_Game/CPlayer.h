#pragma once

enum pDirection
{
	pSTOP,
	pUP,
	pDOWN
};

//==============================
//==============================
class CPlayer1
{
private:
	COORD _paddleCoord;
	pDirection _paddleDir;
	int _paddleVerticalDir;
	int _paddleHorizontalDir;
	int _Score;
public:

	CPlayer1();
	~CPlayer1();

	COORD getPaddleCoord();
	pDirection getPaddleDir();
	int getScore();

	void Init(SHORT, SHORT, int);
	void MoveUp();
	void MoveDown();
	void Stop();
	void Scored();
};

//==============================
//==============================
CPlayer1::CPlayer1()
{
	_paddleCoord = { 0,0 };
	_paddleDir = pSTOP;
	_paddleVerticalDir = 0;
	_paddleHorizontalDir = 0;
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

pDirection CPlayer1::getPaddleDir()
{
	return _paddleDir;
}
	
int CPlayer1::getScore()
{
	return _Score;
}

void CPlayer1::Init(SHORT initialCoordX, SHORT initialCoordY, int _playerSide)
{
	_paddleCoord = { initialCoordX, initialCoordY };
	_paddleDir = pSTOP;
	_paddleHorizontalDir = _playerSide;
	_Score = 0;
}

void CPlayer1::MoveUp()
{
	_paddleCoord.Y -= 2;
	_paddleDir = pUP;
}

void CPlayer1::MoveDown()
{
	_paddleCoord.Y += 2;
	_paddleDir = pDOWN;
}

void CPlayer1::Stop()
{
	_paddleDir = pSTOP;
}

void CPlayer1::Scored()
{
	_Score++;
}