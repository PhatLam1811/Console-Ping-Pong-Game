#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

class cEngine
{
private:
	int m_nScreenWidth;
	int m_nScreenHeight;
	
	CHAR_INFO* pBuffer;
	
	SMALL_RECT m_WinRect;
	COORD m_ScreenSize;

	HANDLE hConsole;
	HANDLE hConsoleIn;

public:
	cEngine()
	{
		m_nScreenWidth = 0;
		m_nScreenHeight = 0;

		pBuffer = nullptr;

		m_WinRect = { 0,0,1,1 };
		m_ScreenSize = { 0,0 };

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	}

	~cEngine()
	{
		delete[] pBuffer;
	}

	bool ConsoleWindowConstruct(int _nWidth, int _nHeight, int _nFontX, int _nFontY)
	{
		m_nScreenWidth = _nWidth;
		m_nScreenHeight = _nHeight;

		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = _nFontX;
		cfi.dwFontSize.Y = _nFontY;
		cfi.FontWeight = FW_NORMAL;
		cfi.FontFamily = FF_DONTCARE;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(hConsole, false, &cfi);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		if (m_nScreenWidth > csbi.dwMaximumWindowSize.X ||
			m_nScreenHeight > csbi.dwMaximumWindowSize.Y)
		{
			cfi.dwFontSize.X = 8;
			cfi.dwFontSize.Y = 16;

			SetCurrentConsoleFontEx(hConsole, false, &cfi);

			m_WinRect = { 0, 0, 120, 80 };

			SetConsoleWindowInfo(hConsole, TRUE, &m_WinRect);

			cout << "Invalid Screen Size!";

			return false;
		}

		m_WinRect = { 0, 0, (short)(m_nScreenWidth - 1), (short)(m_nScreenHeight - 1) };
		SetConsoleWindowInfo(hConsole, TRUE, &m_WinRect);
		SetConsoleMode(hConsole, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT);
		
		SetConsoleCtrlHandler((PHANDLER_ROUTINE)true, TRUE);

		return true;
	}

	bool ScreenBufferConstruct()
	{
		m_ScreenSize = { (short)m_nScreenWidth, (short)m_nScreenHeight };
		SetConsoleScreenBufferSize(hConsole, m_ScreenSize);
		SetConsoleActiveScreenBuffer(hConsole);

		pBuffer = new CHAR_INFO[m_nScreenWidth * m_nScreenHeight];

		if (!pBuffer)
			return false;

		memset(pBuffer, 0, sizeof(CHAR_INFO) * m_nScreenWidth * m_nScreenHeight);

		return true;
	}
};