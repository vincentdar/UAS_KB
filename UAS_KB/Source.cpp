#include "Game.h"

int main()
{
	std::cout << "Branch ARF" << std::endl;
	UAS_KB::Game game(SCREEN_WIDTH, SCREEN_HEIGHT, "Hex Game Minimax");
	return EXIT_SUCCESS;
}
