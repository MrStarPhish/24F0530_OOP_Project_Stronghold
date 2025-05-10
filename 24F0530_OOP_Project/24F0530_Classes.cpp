#include<iostream>
#include<Windows.h> // for gotoxy, hideCursor, setColor
#include"24F0530_Header.h"
#include<conio.h> // for getch
#include<string>
#include<iomanip> // for setw

using namespace std;

void gotoxy(int x, int y);
void setColor(int color);
void hideConsoleCursor();


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
	world.loadPreset1Labels();
	
}


void Game::displayFrame()
{
	frame.display();
}

void Game::displayWorld()
{
	world.display();
}

Cursor::Cursor(int a, int b)
{
	position.set(a, b);
}

void Cursor::moveCursor(int direction)
{
	switch (direction)
	{
	case UP:
		moveCursorUp();
		break;
	case DOWN:
		moveCursorDown();
		break;
	case LEFT:
		moveCursorLeft();
		break;
	case RIGHT:
		moveCursorRight();
		break;
	}
}

bool Cursor::isOutOfBoundary(int x, int y)
{	// AGar boudnary se baahir jaye toh return 1, warna return 0
	int topBound = WORLD_START_Y;
	int leftBound = WORLD_START_X;
	int rightBound = (leftBound)+(FRAME_COLS * ((FRAME_COLS / TILE_WIDTH) - 1));
	int bottomBound = (topBound)+(FRAME_ROWS * ((FRAME_ROWS / TILE_LENGTH) - 1));

	if (x > rightBound)
		return 1;
	if (x < leftBound)
		return 1;
	if (y > bottomBound)
		return 1;
	if (y < topBound)
		return 1;

	return 0;

}

void Cursor::moveCursorUp()
{
	int newX = position.x + 0;
	int newY = position.y - 3;
	if (!isOutOfBoundary(newX, newY))
	{
		position.x = newX;
		position.y = newY;
	}
}
void Cursor::moveCursorDown()
{
	int newX = position.x + 0;
	int newY = position.y + 3;
	if (!isOutOfBoundary(newX, newY))
	{
		position.x = newX;
		position.y = newY;
	}
}
void Cursor::moveCursorLeft()
{
	int newX = position.x - 5;
	int newY = position.y + 0;
	if (!isOutOfBoundary(newX, newY))
	{
		position.x = newX;
		position.y = newY;
	}
}
void Cursor::moveCursorRight()
{
	int newX = position.x + 5;
	int newY = position.y + 0;
	if (!isOutOfBoundary(newX, newY))
	{
		position.x = newX;
		position.y = newY;
	}
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

template <typename T>
Resource<T>::Resource()
{
	quantity = 0;
}

template <typename T>
Resource<T>::Resource(int q)
{
	quantity = q;
}
template <typename T>
void Resource<T>::set(T q) { quantity = q; }
template <typename T>
void Resource<T>::add(T q) { quantity += q; }

template <typename T>
bool Resource<T>::consume(T q) // agar successfully consume ho jaye, toh 1 return krdo
{
	if (quantity >= q)
	{
		quantity -= q;
		return 1;
	}
	return 0;
}

template <typename T>
T Resource<T>::get() { return quantity; }

Economy::Economy(int food, int wood, int weapons, float stone, float gold)
{
	this->food.set(food);
	this->wood.set(wood);
	this->weapons.set(weapons);
	this->stone.set(stone);
	this->gold.set(gold);
}

void Economy::displayResources(int x, int y) const
{
	gotoxy(x, y);
	cout << "Food: " << food.quantity;
	//gotoxy(x, y + 1);
	cout << " | Wood: " << wood.quantity;
	//gotoxy(x, y + 2);
	cout << " | Stone: " << stone.quantity;
	//gotoxy(x, y + 3);
	cout << " | Gold: " << gold.quantity;
	//gotoxy(x, y + 4);
	cout << " | Weapons: " << weapons.quantity;
}

void Economy::add(string resource, int amount)
{
	if (resource == "food") food.add(amount);
	else if (resource == "wood") wood.add(amount);
	else if (resource == "stone") stone.add(amount);
	else if (resource == "gold") gold.add(amount);
	else if (resource == "weapons") weapons.add(amount);
}

bool Economy::consume(string resource, int amount)   // successfully consume ho jaye toh TRUE return ho jaye ga
{
	if (resource == "food") return food.consume(amount);
	if (resource == "wood") return wood.consume(amount);
	if (resource == "stone") return stone.consume(amount);
	if (resource == "gold") return gold.consume(amount);
	if (resource == "weapons") return weapons.consume(amount);
	return 0;
}


World::World() : starting(WORLD_START_X, WORLD_START_Y)
{
	createTiles();
	initializeTiles();
	initializeEmpires();
}

void World::loadPreset1Labels()
{

	int maxRows = FRAME_ROWS / TILE_LENGTH; // here rows and cols mean TILES
	int maxCols = FRAME_COLS / TILE_WIDTH;

	gotoxy((maxCols - 6) * TILE_WIDTH, (maxRows)*TILE_LENGTH + 2);
	cout << "EMPIRE-B";
	gotoxy(WORLD_START_X + 19, WORLD_START_Y + 3);
	cout << "EMPIRE-A";
	gotoxy(WORLD_START_X + 160, WORLD_START_Y + 3);  // near bottom-left corner
	cout << "TRADE CENTER";
	gotoxy(WORLD_START_X + 19, (maxRows-1)*TILE_LENGTH);
	cout << "BATTLEFIELD";
}

void World::loadPreset1()
{

	int maxRows = FRAME_ROWS / TILE_LENGTH; // here rows and cols mean TILES
	int maxCols = FRAME_COLS / TILE_WIDTH;

	
	// EMPIRE - A 

	Building* aCastle = createBuilding(3, 3, 1, 2, 'C'); // a 3x3 Castle starting at Tile(1,2)
	placeBuilding(aCastle);

	Building* aBarracks = createBuilding(2, 3, 6, 2, 'B');
	placeBuilding(aBarracks);

	Building* aFarm1 = createBuilding(2, 2, 2, 6, 'F');
	placeBuilding(aFarm1);

	Building* aFarm2 = createBuilding(3, 2, 5, 6, 'F');
	placeBuilding(aFarm2);

	// EMPIRE - B

	Building* bCastle = createBuilding(3, 3, maxCols - 5, maxRows - 5, 'C');
	placeBuilding(bCastle);

	Building* bBarracks = createBuilding(2, 3, maxCols - 8, maxRows - 5, 'B');
	placeBuilding(bBarracks);

	Building* bFarm1 = createBuilding(2, 2, maxCols - 5, maxRows - 8, 'F');
	placeBuilding(bFarm1);

	Building* bFarm2 = createBuilding(3, 1, maxCols - 9, maxRows - 9, 'F');
	placeBuilding(bFarm2);


	// THe Paths
	int midY = maxRows / 2;

	for (int x = 0; x < maxCols; ++x) // Horizontral Path in Mid
	{
		tiles[midY][x]->type = PATH_X;
	}

	for (int y = 2; y < midY; ++y) // Vertical path from Castle A to center
	{
		tiles[y][4]->type = PATH_Y;
	}

	for (int y = midY+1; y < maxRows-2; y++) // // Vertical path from Castle B to center
	{
		tiles[y][maxCols-6]->type = PATH_Y;
	}

	tiles[midY][4] -> type = EMPTY; // placing the intersections for better visibility
	tiles[midY][maxCols-6]->type = EMPTY;

	// TRADE CENTER or Market Place

	Building* marketplace = createBuilding(3, 2, maxCols - 6, 3, 'M'); // 'M' for Marketplace
	placeBuilding(marketplace);

	Building* tradePost = createBuilding(2, 2, maxCols - 9, 7, 'T');   // 'T' for Trade Post
	placeBuilding(tradePost);

	Building* bank = createBuilding(2, 2, maxCols - 9, 2, 'N');       // 'N' for Bank
	placeBuilding(bank);

	
}



void World::display()
{
	displayTiles();
	displayBuildings();
	displayEconomies();
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

void World::displayEconomies()
{
	gotoxy(0, 0);
	cout << "EMPIRE-A Stats:-";
	empireA->displayEconomy();
	gotoxy(0, 2);
	cout << "EMPIRE-B Stats:-";
	empireB->displayEconomy();
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

	delete empireA;
	delete empireB;
}

void World::placeBuilding(Building* b)
{
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

void World::initializeEmpires()
{
	initializeEmpireA();
	initializeEmpireB();
}

void World::initializeEmpireA()
{
	// Loading presets of Empire Stats here. Initialize them here, and pass them into the empireA constructor below.
	Economy* eco = new Economy(200, 300, 400, 500, 600);

	empireA = new Empire(0, 0, 10, 1, eco);
}

void World::initializeEmpireB()
{
	Economy* eco = new Economy(200, 300, 400, 500, 600);

	empireB = new Empire(0, 0, 10, 3, eco);
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
	case 'c':
	case 'C':
		return new Castle(w, h, x, y, c);
		break;
	case 'b':
	case 'B':
		return new Barracks(w, h, x, y, c);
		break;
	case 'm':
	case 'M':
		return new Market(w, h, x, y, c);
		break;
	case 't':
	case 'T':
		return new Tradepost(w, h, x, y, c);
		break;
	case 'n':
	case 'N':
		return new Bank(w, h, x, y, c);
		break;
	default:
		return nullptr;
	}
}


Empire::Empire() : EMPIRE_STATS_X(0) , EMPIRE_STATS_Y(0)
{
	position.set(0, 0);
}

Empire::Empire(int x, int y, int a, int b, Economy* e, Politics* p, Army* ar, Population* pop) : EMPIRE_STATS_X(a), EMPIRE_STATS_Y(b)
{
	position.set(x, y);
	economy = e;
	politics = p;
	army = ar;
	population = pop;
}
Empire::~Empire()
{
	delete politics;
	delete army;
	delete population;
	delete economy;
}
void Empire::displayEconomy()
{
	economy->displayResources(EMPIRE_STATS_X, EMPIRE_STATS_Y);
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
	int x = WORLD_START_X + (TILE_WIDTH * position.x); // storing character coordinates
	int y = WORLD_START_Y + (TILE_LENGTH * position.y);
	int w = TILE_WIDTH * width; // storing character length and width
	int l = TILE_LENGTH * height;

	setColor(GREEN);

	int mid_y = (l - 1) / 2 + y;

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
	setColor(DEFAULT);
	gotoxy(x+1, mid_y);
	cout << setw(w-2) << left <<"FARM";
}

Castle::Castle(int w, int h, int x, int y, char c)
{
	width = w;
	height = h;
	position.set(x, y); // in terms of Tile
	type = c;
}

void Castle::displayBuilding()
{
	int x = WORLD_START_X + (TILE_WIDTH * position.x); // storing character coordinates
	int y = WORLD_START_Y + (TILE_LENGTH * position.y);
	int w = TILE_WIDTH * width; // storing character length and width
	int l = TILE_LENGTH * height;

	setColor(SKYBLUE);

	int mid_y = (l - 1) / 2 + y;

	for (int i = 0; i < l; i++)
	{
		gotoxy(x, y + i);
		if (i == 0)
		{
			for (int j = 0; j < w; j++)
			{
				cout << "^";
			}
		}
		else if (i + 1 == l)
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
	setColor(DEFAULT);
	gotoxy(x + 1, mid_y);
	cout << setw(w - 2) << left << "CASTLE";
}

Barracks::Barracks(int w, int h, int x, int y, char c)
{
	width = w;
	height = h;
	position.set(x, y); // in terms of Tile
	type = c;
}

void Barracks::displayBuilding()
{
	int x = WORLD_START_X + (TILE_WIDTH * position.x); // storing character coordinates
	int y = WORLD_START_Y + (TILE_LENGTH * position.y);
	int w = TILE_WIDTH * width; // storing character length and width
	int l = TILE_LENGTH * height;

	setColor(RED);

	int mid_y = (l - 1) / 2 + y;

	for (int i = 0; i < l; i++)
	{
		gotoxy(x, y + i);
		if (i == 0 || i + 1 == l)
		{
			for (int j = 0; j < w; j++)
			{
				cout << "^";
			}
		}
		else
		{
			cout << "|";
			gotoxy(x + w - 1, y + i);
			cout << "|";
		}
	}
	setColor(DEFAULT);
	gotoxy(x + 1, mid_y);
	cout << setw(w - 2) << left << "BARRACKS";
}

Market::Market(int w, int h, int x, int y, char c)
{
	width = w;
	height = h;
	position.set(x, y); // in terms of Tile
	type = c;
}

void Market::displayBuilding()
{
	int x = WORLD_START_X + (TILE_WIDTH * position.x); // storing character coordinates
	int y = WORLD_START_Y + (TILE_LENGTH * position.y);
	int w = TILE_WIDTH * width; // storing character length and width
	int l = TILE_LENGTH * height;

	setColor(RED);

	int mid_y = (l - 1) / 2 + y;

	for (int i = 0; i < l; i++)
	{
		gotoxy(x, y + i);
		if (i == 0 || i + 1 == l)
		{
			for (int j = 0; j < w; j++)
			{
				cout << "^";
			}
		}
		else
		{
			cout << "|";
			gotoxy(x + w - 1, y + i);
			cout << "|";
		}
	}
	setColor(DEFAULT);
	gotoxy(x + 1, mid_y);
	cout << setw(w - 2) << left << "MARKET";
}

Tradepost::Tradepost(int w, int h, int x, int y, char c)
{
	width = w;
	height = h;
	position.set(x, y); // in terms of Tile
	type = c;
}

void Tradepost::displayBuilding()
{
	int x = WORLD_START_X + (TILE_WIDTH * position.x); // storing character coordinates
	int y = WORLD_START_Y + (TILE_LENGTH * position.y);
	int w = TILE_WIDTH * width; // storing character length and width
	int l = TILE_LENGTH * height;

	setColor(SKYBLUE);

	int mid_y = (l - 1) / 2 + y;

	for (int i = 0; i < l; i++)
	{
		gotoxy(x, y + i);
		if (i == 0 || i + 1 == l)
		{
			for (int j = 0; j < w; j++)
			{
				cout << "^";
			}
		}
		else
		{
			cout << "|";
			gotoxy(x + w - 1, y + i);
			cout << "|";
		}
	}
	setColor(DEFAULT);
	gotoxy(x + 1, mid_y);
	cout << setw(w - 2) << left << "TRADEPOST";
}

Bank::Bank(int w, int h, int x, int y, char c)
{
	width = w;
	height = h;
	position.set(x, y); // in terms of Tile
	type = c;
}

void Bank::displayBuilding()
{
	int x = WORLD_START_X + (TILE_WIDTH * position.x); // storing character coordinates
	int y = WORLD_START_Y + (TILE_LENGTH * position.y);
	int w = TILE_WIDTH * width; // storing character length and width
	int l = TILE_LENGTH * height;

	setColor(GREEN);

	int mid_y = (l - 1) / 2 + y;

	for (int i = 0; i < l; i++)
	{
		gotoxy(x, y + i);
		if (i == 0 || i + 1 == l)
		{
			for (int j = 0; j < w; j++)
			{
				cout << "^";
			}
		}
		else
		{
			cout << "|";
			gotoxy(x + w - 1, y + i);
			cout << "|";
		}
	}
	setColor(DEFAULT);
	gotoxy(x + 1, mid_y);
	cout << setw(w - 2) << left << "BANK $";
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

void hideConsoleCursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
