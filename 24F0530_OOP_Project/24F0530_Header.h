#pragma once

#include<iostream>
#include<string>
using namespace std;

const int FRAME_ROWS = 60;
const int FRAME_COLS = 200;

const int FRAME_X_OFFSET = 0;
const int FRAME_Y_OFFSET = 5;

const int WORLD_START_X = FRAME_X_OFFSET + 1;
const int WORLD_START_Y = FRAME_Y_OFFSET + 1;

const int TILE_WIDTH = 5;
const int TILE_LENGTH = 3;


void gotoxy(int x, int y);
void setColor(int color);
void hideCursor();


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
	PATH_X, PATH_Y, STRUCTURE, EMPTY
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
public:
	// FRAME ke andar jo saara gameplay ho ga
	const Coords starting; // start inside the Frame
	Tile*** tiles; // 2D array of Tiles Pointer

	World();
	~World();

	void loadPreset1();

	void display();
	void initializeTiles();
	void createTiles();
	void displayTiles();
	void placeBuilding(Building*);
	Building* createBuilding(int, int, int, int, char);
	void displayBuildings();
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
	void displayWorld();
};



class Tile
{
public:
	// The smallest storing Unit for the game...like, a Tile could be 5x5 characters.
	const Coords position; // top left corner aka starting position's coords
	bool isOccupied;
	Building* building; // the building that will be stored here (if any)
	Terrain type;
	int ID;

	static int TileCount;

	Tile();
	Tile(int x, int y);
	void displayTile();
	void displayEmptyTile();
	void displayPathXTile();
	void displayPathYTile();

};

class Building
{
public:
	Coords position; // starting Tile
	int width, height; // the size of the building, in terms of TIle
	char type;

	Building();
	Building(int, int, int, int, char = '\0');
	virtual void displayBuilding(); // #POLYMORPHISM

};


class Farm : public Building  
{
public:
	Farm(int, int, int, int, char);

	void displayBuilding();
};
