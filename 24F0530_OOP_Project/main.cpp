#include<iostream>
#include<windows.h>
#include<conio.h>
#include"24F0530_Header.h"

using namespace std;


int main()
{
	int frame = 0;
	hideConsoleCursor();
	ios::sync_with_stdio(false);
	Game game;

	char key;

	while (true)
	{
		//if (frame % 5)
			//game.displayWorld();

		key = _getch();
		game.keyPressed(key);
		game.displayCursor();
		game.displayLabels();

		gotoxy(0, 70);
		frame++;
		//Sleep(5);
	}
	


	gotoxy(0, 70);
	cout << endl;
	system("pause");
	return 0;
}