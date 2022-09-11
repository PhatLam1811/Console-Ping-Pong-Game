#include<iostream>
#include<Windows.h>
#include<chrono>
using namespace std;

const int nScreenWidth = 120;
const int nScreenHeight = 80;

const int nFontX = 6;
const int nFontY = 6;

static HANDLE hConsole;

SMALL_RECT g_WinRect;
CHAR_INFO* pBuffer = nullptr;

struct Circle
{
	float cx, cy, vx, vy, ax, ay, r;
};
Circle g_Ball;

float g_fElapsedTime;

void ConsoleConstruct();
void BufferConstruct();
void BorderConstruct();

void Setup();
void Loop();
void Draw(int, int);

void Cls();
void UpdateBall();
void DrawBall();

int main()
{
	Setup();

	Loop();

	return 0;

	//===z613z===//
}

void ConsoleConstruct()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	g_WinRect = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &g_WinRect);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = nFontX;
	cfi.dwFontSize.Y = nFontY;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hConsole, false, &cfi);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	if (csbi.dwMaximumWindowSize.X < nScreenWidth)
		return;
	if (csbi.dwMaximumWindowSize.Y < nScreenHeight)
		return;

	g_WinRect = { 0, 0, (short)(nScreenWidth - 1), (short)(nScreenHeight - 1) };
	SetConsoleWindowInfo(hConsole, TRUE, &g_WinRect);

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)true, TRUE);
}

void BufferConstruct()
{
	SetConsoleActiveScreenBuffer(hConsole);
	SetConsoleScreenBufferSize(hConsole, { (short)(nScreenWidth - 1), (short)(nScreenHeight - 1) });

	pBuffer = new CHAR_INFO[nScreenWidth * nScreenHeight];
	memset(pBuffer, 0, sizeof(CHAR_INFO) * nScreenWidth * nScreenHeight);
}

void BorderConstruct()
{
	for (int i = 1; i < nScreenWidth - 1; i++)
	{
		pBuffer[nScreenWidth + i].Char.UnicodeChar = 0x2588;
		pBuffer[nScreenWidth + i].Attributes = 0x000F;

		pBuffer[nScreenWidth * (nScreenHeight - 2) + i].Char.UnicodeChar = 0x2588;
		pBuffer[nScreenWidth * (nScreenHeight - 2) + i].Attributes = 0x000F;
	}

	for (int i = 2; i < nScreenHeight - 2; i++)
	{
		pBuffer[nScreenWidth * i + 1].Char.UnicodeChar = 0x2588;
		pBuffer[nScreenWidth * i + 1].Attributes = 0x000F;

		pBuffer[nScreenWidth * i + 59].Char.UnicodeChar = 0x2588;
		pBuffer[nScreenWidth * i + 59].Attributes = 0x000F;

		pBuffer[nScreenWidth * i + nScreenWidth - 2].Char.UnicodeChar = 0x2588;
		pBuffer[nScreenWidth * i + nScreenWidth - 2].Attributes = 0x000F;
	}
}

void Setup()
{
	ConsoleConstruct();

	BufferConstruct();

	BorderConstruct();

	g_Ball.cx = nScreenWidth / 2 + 5;
	g_Ball.cy = nScreenHeight / 2;
	g_Ball.vx = 20.0f;
	g_Ball.vy = 20.0f;
	g_Ball.ax = 1.0f;
	g_Ball.ay = 1.0f;
	g_Ball.r = 2.0f;
}

void Draw(int x, int y)
{
	pBuffer[nScreenWidth * y + x].Char.UnicodeChar = 0x2588;
	pBuffer[nScreenWidth * y + x].Attributes = 0x000F;
}

void Loop()
{
	auto aTimePoint1 = std::chrono::system_clock::now();
	auto aTimePoint2 = std::chrono::system_clock::now();

	while (true)
	{
		aTimePoint2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = aTimePoint2 - aTimePoint1;
		aTimePoint1 = aTimePoint2;
		g_fElapsedTime = elapsedTime.count();

		Cls();

		UpdateBall();

		DrawBall();

		wchar_t s[256];
		swprintf_s(s, 256, L"Ping Pong Game - %s - FPS: %3.2f", L"PPG", 1.0f / g_fElapsedTime);
		SetConsoleTitle(s);
		WriteConsoleOutput(hConsole, pBuffer, { (short)nScreenWidth, (short)nScreenHeight }, { 0,0 }, &g_WinRect);
	}
}

void Cls()
{
	for (int i = 2; i < nScreenWidth - 2; i++)
	{
		if (i == 59)
			continue;

		for (int j = 2; j < nScreenHeight - 2; j++)
			pBuffer[nScreenWidth * j + i].Char.UnicodeChar = ' ';
	}
}

void UpdateBall()
{
	g_Ball.ax = g_Ball.ax > 1.0f ? -g_Ball.vx * 0.1f : 0;
	g_Ball.ay = g_Ball.ax > 1.0f ? -g_Ball.vy * 0.1f : 0;
	g_Ball.vx += g_Ball.ax * g_fElapsedTime;
	g_Ball.vy += g_Ball.ay * g_fElapsedTime;
	g_Ball.cx += g_Ball.vx * g_fElapsedTime;
	g_Ball.cy += g_Ball.vy * g_fElapsedTime;

	if (g_Ball.cx + g_Ball.r >= nScreenWidth - 2)
	{
		g_Ball.vx *= -1;
		g_Ball.ax *= -10;
		g_Ball.cx = nScreenWidth - 2 - g_Ball.r;
	}

	if (g_Ball.cx - g_Ball.r <= 2)
	{
		g_Ball.vx *= -1;
		g_Ball.ax *= -10;
		g_Ball.cx = 2 + g_Ball.r;
	}

	if (g_Ball.cy + g_Ball.r >= nScreenHeight - 2)
	{
		g_Ball.vy *= -1;
		g_Ball.ay *= -10;
		g_Ball.cy = nScreenHeight - 2 - g_Ball.r;
	}

	if (g_Ball.cy - g_Ball.r <= 2)
	{
		g_Ball.vy *= -1;
		g_Ball.ay *= -10;
		g_Ball.cy = 2 + g_Ball.r;
	}
}

void DrawBall()
{
	int x = 0;
	int y = g_Ball.r;
	int d = 3 - 2 * g_Ball.r;

	while (y > x)
	{
		Draw(g_Ball.cx - x, g_Ball.cy - y);
		Draw(g_Ball.cx - y, g_Ball.cy - x);
		Draw(g_Ball.cx + x, g_Ball.cy - y);
		Draw(g_Ball.cx + y, g_Ball.cy - x);
		Draw(g_Ball.cx - x, g_Ball.cy + y);
		Draw(g_Ball.cx - y, g_Ball.cy + x);
		Draw(g_Ball.cx + x, g_Ball.cy + y);
		Draw(g_Ball.cx + y, g_Ball.cy + x);

		if (d < 0)
			d = d + 4 * x++ + 6;
		else
			d = d + 4 * (x++ - y--) + 10;
	}
}