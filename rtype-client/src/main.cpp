#include "Game.hpp"

int main()
{
	asio::io_context io_context;

	rtype::Game game(io_context);

	game.gameLoop();

	return 0;
}