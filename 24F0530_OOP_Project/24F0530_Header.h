#pragma once

#include<iostream>
#include<string>
using namespace std;

const int FRAME_ROWS = 50;
const int FRAME_COLS = 200;

const int FRAME_X_OFFSET = 0;
const int FRAME_Y_OFFSET = 5;



struct Coords;
class Game;
class Frame;


enum Color
{
	RED = 4, GREEN = 2, YELLOW = 6, BLUE = 1, SKYBLUE = 3, WHITE = 7, DEFAULT = 7, MAGENTA = 5
};

struct Coords
{
	int x, y;
	Coords();
	Coords(int, int);
	void set(int a, int b);

};


class Frame
{
public:
	int width;
	int length;
	Coords starting;
	Frame();
	void display();
};

class Game
{
public:
	Frame frame;

	Game();
	~Game();
	void displayFrame();
};

