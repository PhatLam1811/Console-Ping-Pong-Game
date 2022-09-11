#pragma once
#include <Windows.h>

struct sKeyState
{
	bool Pressed;
	bool Hold;
	bool Released;
};

class cEngine
{
private:
	int a_nConsoleWidth;
	int a_nConsoleHeight;
	short a_mKeyPrevState[256] = { 0 };
	short a_mKeyNextState[256] = { 0 };
	sKeyState a_mKeys[256];
	HANDLE a_hConsoleOut;
	HANDLE a_hConsoleIn;

protected:
	cEngine();
	~cEngine();

	void consoleConstruct(int, int, int, int);
};

cEngine::cEngine()
{
	a_nConsoleWidth = 120;
	a_nConsoleHeight = 80;

	memset(a_mKeyPrevState, 0, 256 * sizeof(short));
	memset(a_mKeyNextState, 0, 256 * sizeof(short));
	memset(a_mKeys, 0, 256 * sizeof(sKeyState));

	a_hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	a_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
}

cEngine::~cEngine()
{
	return;
}

void cEngine::consoleConstruct(int _Width, int _Height, int _fontWidth, int _fontHeight)
{
	/*if (a_hConsoleOut == INVALID_HANDLE_VALUE)
		return Error(L"Bad Handle");*/

	a_nConsoleWidth = _Width;
	a_nConsoleHeight = _Height;


}