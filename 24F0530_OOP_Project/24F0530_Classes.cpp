#include<iostream>
#include<Windows.h> // for gotoxy, hideCursor, setColor
#include"24F0530_Header.h"
#include<conio.h> // for getch
#include<string>
#include<iomanip> // for setw

using namespace std;

void gotoxy(int x, int y);
void setColor(int color);
void hideCursor();


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
	world.loadPreset1();
	displayWorld();
	
}


void Game::displayFrame()
{
	frame.display();
}

void Game::displayWorld()
{
	world.display();
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
	for (int i = 0; i < length+2; i++)
	{
		if (i == 0 || i + 1 == length+2)
		{
			for (int j = 0; j < width+2; j++)
			{
				cout << "=";
			}
		}
		else
		{
			cout << "|";
			gotoxy((FRAME_COLS - 1 + 2) + x, i + y);
			cout << "|";
		}
		cout << endl;
	}
}

World::World() : starting(WORLD_START_X, WORLD_START_Y)
{
	createTiles();
	initializeTiles();
}

void World::loadPreset1()
{
	// Example: Place a 3x2 building at tile[5][10]
	Building* b1 = createBuilding(3, 2, 10, 5, 'f');
	placeBuilding(b1);

	// Example: Another building at tile[15][20]
	Building* b2 = createBuilding(4, 3, 20, 15, 'f');
	placeBuilding(b2);

	// Example: Create a horizontal path from tile[8][0] to tile[8][9]
	for (int x = 0; x < 10; ++x) {
		tiles[8][x]->type = PATH_X;
		tiles[8][x]->isOccupied = false;
		tiles[8][x]->building = nullptr;
	}

	// Example: Vertical path from tile[8][9] to tile[14][9]
	for (int y = 9; y <= 14; ++y) {
		tiles[y][10]->type = PATH_Y;
		tiles[y][10]->isOccupied = false;
		tiles[y][10]->building = nullptr;
	}

	// You can add more preset layout designs here...
}

void World::display()
{
	displayTiles();
	displayBuildings();
}

void World::displayBuildings()
{
	for (int i = 0; i < FRAME_ROWS / TILE_LENGTH; i++)
	{
		for (int j = 0; j < FRAME_COLS / TILE_WIDTH; j++)
		{
			if (tiles[i][j]->building)
			{
				tiles[i][j]->building->displayBuilding();
			}
		}
	}
}

void World::displayTiles()
{
	int rows = FRAME_ROWS / TILE_LENGTH;
	int cols = FRAME_COLS / TILE_WIDTH;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tiles[i][j]->displayTile();
		}
	}
}

World::~World()
{
	for (int i = 0; i < FRAME_ROWS / TILE_LENGTH; i++)
	{
		for (int j = 0; j < FRAME_COLS / TILE_WIDTH; j++)
		{
			delete[] tiles[i][j];
		}
		delete[] tiles[i];
	}
	delete[] tiles;
}

void World::placeBuilding(Building* b) {
	int startX = b->position.x; // Storing indexes of starting Tiles
	int startY = b->position.y;
	int width = b->width;   // storing the size in terms of Tiles 
	int height = b->height; 

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int tileY = startY + i;
			int tileX = startX + j;

			
			if (tileY >= (FRAME_ROWS / TILE_LENGTH) || tileX >= (FRAME_COLS / TILE_WIDTH)) // Out-of-Bound check
				cout << "ERROR: TILE INPUT GOING OUT OF BOUNDARY";

			tiles[tileY][tileX]->isOccupied = true; // updating info of those tiles
			tiles[tileY][tileX]->building = b;
			tiles[tileY][tileX]->type = STRUCTURE;
		}
	}
}

void World::createTiles()
{
	int rows = FRAME_ROWS / TILE_LENGTH;
	int cols = FRAME_COLS / TILE_WIDTH;

	tiles = new Tile * *[rows];
	for (int i = 0; i < rows; i++)
	{
		tiles[i] = new Tile * [cols];
	}
}

void World::initializeTiles()
{
	int rows = FRAME_ROWS / TILE_LENGTH;
	int cols = FRAME_COLS / TILE_WIDTH;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tiles[i][j] = new Tile(WORLD_START_X + (j * TILE_WIDTH), WORLD_START_Y + (i * TILE_LENGTH)); // correctly setting the starting position of each tile
		}
	}
}

int Tile::TileCount = 0; // the static int
Tile::Tile() : position(WORLD_START_X, WORLD_START_Y)
{
	isOccupied = FALSE;
	building = nullptr;
	type = EMPTY;

	ID = TileCount;
	TileCount++;
}
Tile::Tile(int x, int y) : position(x, y)
{
	isOccupied = FALSE;
	building = nullptr;
	type = EMPTY;

	ID = TileCount;
	TileCount++;
}


void Tile::displayEmptyTile()
{
	int x = position.x;
	int y = position.y;

	gotoxy(x, y);
	for (int i = 0; i < TILE_LENGTH; i++)
	{
		gotoxy(x, y + i);
		for (int j = 0; j < TILE_WIDTH; j++)
		{
			cout << " ";
		}
	}
}

void Tile::displayPathXTile()
{
	int x = position.x;
	int y = position.y;

	gotoxy(x, y);
	for (int i = 0; i < TILE_LENGTH; i++)
	{
		gotoxy(x, y + i);
		if (i == 0 || i + 1 == TILE_LENGTH)
		{
			cout << "=====";
		}
		else
		{
			for (int j = 0; j < TILE_WIDTH; j++)
			{
				cout << " ";
			}
		}
	}
}

void Tile::displayPathYTile()
{
	int x = position.x;
	int y = position.y;

	gotoxy(x, y);
	for (int i = 0; i < TILE_LENGTH; i++)
	{
		gotoxy(x, y + i);
		cout << "|   |";
	}
}

void Tile::displayTile()
{	
	switch (type)
	{
	case EMPTY:
		displayEmptyTile();
		break;
	case PATH_X:
		displayPathXTile();
		break;
	case PATH_Y:
		displayPathYTile();
		break;
	}
}

Building* World::createBuilding(int w, int h, int x, int y, char c)
{
	switch (c)
	{
	case 'f':
	case 'F':
		return new Farm(w, h, x, y, c);
		break;
	}
}


Building::Building()
{
	position.set(0, 0);
	width = height = 0;
	type = '\0';
}
Building::Building(int w, int h, int x, int y, char c)
{
	width = w;
	height = h;
	position.set(x, y); // in terms of Tile
	type = c;
}
void Building::displayBuilding() { }


Farm::Farm(int w, int h, int x, int y, char c)
{
	width = w;
	height = h;
	position.set(x, y); // in terms of Tile
	type = c;
}

void Farm::displayBuilding()
{
	int x = TILE_WIDTH * position.x; // storing character coordinates
	int y = TILE_LENGTH * position.y;
	int w = TILE_WIDTH * width; // storing character length and width
	int l = TILE_LENGTH * height;

	for (int i = 0; i < l; i++)
	{	
		gotoxy(x, y + i);
		if (i == 0 || i + 1 == l)
		{
			for (int j = 0; j < w; j++)
			{
				cout << "-";
			}
		}
		else
		{
			cout << "|";
			gotoxy(x + w - 1, y + i);
			cout << "|";
		}
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

void hideCursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
