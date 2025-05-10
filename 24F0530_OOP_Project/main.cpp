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
		if (frame % 25) // tick rate 
			game.progress();

		if (requireGameRender)
		{
			game.displayWorld();
			requireGameRender = 0;
		}
		if (key = _kbhit())
		{
			key = _getch();
			game.keyPressed(key);

		}
		game.displayCursor();
		game.interactCursor();
		game.displayLabels();

		gotoxy(0, 70);
		frame++;
		Sleep(100);
	}
	


	gotoxy(0, 70);
	cout << endl;
	system("pause");
	return 0;
}