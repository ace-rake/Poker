#include "ClassHeaders/Deck.hpp"
#include "ClassHeaders/Server.hpp"
#include <iostream>

int	main(int argc, char ** argv)
{
	/* Deck deck; */
	/* for (int i = 0; i < 51; i++) */
	/* { */
	/* 	Card card = deck.randomCard(); */
	/* 	std::cout << "Gotten card: " << card << std::endl; */
	/* } */
	/* deck.display(); */

	Server server(argv, argc);
	server.run();
}
