#include<iostream>
#include<Windows.h>
#include"24F0530_Header.h"
#include<conio.h>
#include<string>
#include<iomanip>

using namespace std;

void gotoxy(int x, int y);
void setColor(int color);


void Coords::set(int a, int b)
{
	x = a; y = b;
}

Coords::Coords()
{
	x = y = 0;
}
Coords::Coords(int a, int b)
{
	set(a, b);
}

Game::Game()
{
	displayFrame();
}

Game::~Game()
{
	//
}

void Game::displayFrame()
{
	frame.display();
}

Frame::Frame()
{
	width = FRAME_COLS;
	length = FRAME_ROWS;

	starting.x = FRAME_X_OFFSET;
	starting.y = FRAME_Y_OFFSET;
}

void Frame::display()
{
	int x = starting.x;
	int y = starting.y;

	gotoxy(0 + x, 0 + y);
	for (int i = 0; i < length; i++)
	{
		if (i == 0 || i + 1 == length)
		{
			for (int j = 0; j < width; j++)
			{
				cout << "=";
			}
		}
		else
		{
			cout << "|";
			gotoxy((FRAME_COLS - 1) + x, i + y);
			cout << "|";
		}
		cout << endl;
	}
}




void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
