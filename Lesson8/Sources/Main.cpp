#include "Lesson8PCH.h"

#include <conio.h>

int main()
{
	setlocale(LC_ALL, "");

	size_t fs;

	std::cout << "Enter field size: ";
	std::cin >> fs;

	Game game;
	game.CreateField(fs);
	game.DrawField();

	return game.Run();
}


