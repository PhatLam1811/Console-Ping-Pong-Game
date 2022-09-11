#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include"CBall1.h"
#include"CPlayer1.h"
#include"CBuffer.h"
using namespace std;

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

const int GAME_FIELD_WIDTH = 61;
const int GAME_FIELD_HEIGHT = 15;

CBall* g_Ball = NULL;

CPlayer1* g_1stPlayer = NULL;
CPlayer1* g_2ndPlayer = NULL;

CBuffer* g_prevFrame = NULL;
CBuffer* g_nextFrame = NULL;

bool _isGameOver;

//==============================
//==============================
void Setup();
char Input();
void Processing();
void Draw();
void Loop();
void cleanUp();

//==============================
//==============================
void setConsoleCursorCoord(SHORT, SHORT);
void hideConsoleCursor();
void createFieldBorder();