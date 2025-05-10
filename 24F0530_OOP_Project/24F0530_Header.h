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
void hideConsoleCursor();


struct Coords;
class Game;
class Frame;
class Cursor;
class World;
class Empire;
class Tile;
class Building;
class Economy;


enum Color
{
	RED = 4, GREEN = 2, YELLOW = 6, BLUE = 1, SKYBLUE = 3, WHITE = 7, DEFAULT = 7, MAGENTA = 5
};

enum Terrain
{
	PATH_X, PATH_Y, STRUCTURE, EMPTY
};

enum Direction
{
	LEFT, RIGHT, UP, DOWN
};

struct Coords
{
	// basic struct for storing coordinates
	int x, y;
	Coords();
	Coords(int, int);
	void set(int a, int b);

};

class Cursor
{
	Coords position; // character position , top left corner

	Cursor(int x = 0, int y = 0);

	void moveCursor(int direction);
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();
	bool isOutOfBoundary(int x, int y);
	void displayCursor();
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

template <typename T> // # TEMPLATE
class Resource
{
public:
	T quantity;

	Resource();
	Resource(int);
	void set(T q);
	void add(T q);
	bool consume(T q);
	T get();
};

class Economy {
public:
	Resource<int> food, wood, weapons;
	Resource<float> stone, gold;
	
	Economy(int = 0, int = 0, int = 0, float = 0, float = 0);

	void displayResources(int x = 0, int y = 0) const;
	void add(string resource, int amount);
	bool consume(string resource, int amount);   // successfully consume ho jaye toh TRUE return ho jaye ga
};

class Population
{
public:
	int happiness;
	int hunger;
	int employment;
};

class Army
{
	int soldierCount;
	int morale, trainedUnits;
};

class Politics
{
	float tax;
	int kingLeadershipStyle;
};

class Empire
{
public:
	const int EMPIRE_STATS_X; // # CONSTANT
	const int EMPIRE_STATS_Y;
	Coords position; // starting position in terms of tiles
	Politics *politics;
	Army *army;
	Population *population;
	Economy *economy;

	Empire();
	Empire(int x, int y, int a, int b, Economy* = NULL, Politics* = NULL, Army* = NULL, Population* = NULL ); // character position in World, and character position of STATS
	~Empire();
	void displayEconomy();
};

class World
{
public:
	// FRAME ke andar jo saara gameplay ho ga, basically the actual Gameplay

	const Coords starting; // start inside the Frame
	Tile*** tiles; // 2D array of Tiles Pointer
	Empire *empireA;
	Empire *empireB;

	World();
	~World();

	void loadPreset1();
	void loadPreset1Labels();

	void display();
	void initializeTiles();
	void createTiles();
	void displayTiles();
	void placeBuilding(Building*);
	Building* createBuilding(int, int, int, int, char);
	void displayBuildings();

	void initializeEmpires();
	void initializeEmpireA();
	void initializeEmpireB();
	void displayEconomies();

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
	// Farm, source of revenue, variable size
	Farm(int, int, int, int, char);

	void displayBuilding();
};

class Castle : public Building {
public:
	// A 3x3 building be default
	Castle(int w, int h, int x, int y, char c);

	void displayBuilding();
};

class Barracks : public Building {
public:
	// A big building that represents soldiers 2x3 by default
	Barracks(int w, int h, int x, int y, char c);

	void displayBuilding();
};

class Market : public Building {
public:
	// A big building that represents soldiers 2x3 by default
	Market(int w, int h, int x, int y, char c);

	void displayBuilding();
};

class Tradepost : public Building {
public:
	// A big building that represents soldiers 2x3 by default
	Tradepost(int w, int h, int x, int y, char c);

	void displayBuilding();
};

class Bank : public Building {
public:
	// A big building that represents soldiers 2x3 by default
	Bank(int w, int h, int x, int y, char c);

	void displayBuilding();
};
