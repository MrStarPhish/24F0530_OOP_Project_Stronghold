#pragma once

#include<iostream>
#include<string>
using namespace std;

const int FRAME_ROWS = 60;
const int FRAME_COLS = 200;

const int FRAME_X_OFFSET = 0;
const int FRAME_Y_OFFSET = 5;

void gotoxy(int x, int y);
void setColor(int color);

struct Coords;
class Game;
class Frame;
class World;
class Tile;
class Building;

enum Color
{
	RED = 4, GREEN = 2, YELLOW = 6, BLUE = 1, SKYBLUE = 3, WHITE = 7, DEFAULT = 7, MAGENTA = 5
};

enum Terrain
{
	GRASS, PATH, STRUCTURE
};

struct Coords
{
	// basic struct for storing coordinates
	int x, y;
	Coords();
	Coords(int, int);
	void set(int a, int b);

};


class Frame
{
	// You could say it's umm some HUD...or boundary of the gameplay screen
public:
	int width;
	int length;
	Coords starting;
	Frame();
	void display();
};

class World
{
	Tile*** tiles; // 2D array of Tiles Pointer
};

class Game
{
	// Game hai, game ke andar Frame hai. Game ke andar World hai.
	// Frame is like the HUD, and World is the In-Game stuff
public:
	Frame frame;
	World world;

	Game();
	void displayFrame();
};



class Tile
{
	// The smallest storing Unit for the game...like, a Tile could be 5x5 characters.
	Coords position; // top left corner aka starting position's coords
	bool isOccupied;
	Building* building; // the building that will be stored here (if any)
	Terrain type;
};

class Building
{
	Coords position; // starting position's coords
	int width, height; // the size of the building, in terms of TIle
};