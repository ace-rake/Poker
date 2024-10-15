#include "../ClassHeaders/Game.hpp"
#include "../ClassHeaders/Server.hpp"
#include <cstdlib>
#include <iostream>

void	Server::gameCommandHandler(User & user, std::vector<std::string> & words)
{
	_game.update(user, words);
}

void	Game::see(User & user)const
{
	user.sendToClient("Entered see");
	// Print total pot
	user.sendToClient("Total pot is :" + std::to_string(_pot));
	// Print players + status + bets
	for (User * p_user: _participants)
	{
		std::cout << *p_user;
		user.sendToClient(p_user->getName() + " " + (p_user->getStatus() == OUT ? "OUT ": "") + std::to_string(p_user->getBet()));
	}
	// Print table cards
	// Print own bet
	// Print own cards
	// Print own stack
}

void	Game::commandHandler(User & user, std::vector<std::string> & words)
{
	if (words.empty())
		return ;
	if (!words[0].compare("see"))
	{
		see(user);
		return ;
	}
	if (user.getStatus() != ACTIVE)
	{
		user.sendToClient("You are not the active player");
		return ;
	}
	/* else if (words[0].compare("fold")) */
	/* { */
	/* 	fold(user); */
	/* } */
	/* else if (words[0].compare("check")) */
	/* { */
	/* 	check(user); */
	/* } */
	/* else if (words[0].compare("raise")) */
	/* { */
	/* 	if (words.size() < 2) */
	/* 		return ; */
	/* 	raise(user, std::atoi(words[1].c_str())); */
	/* } */
	/* else if (words[0].compare("call")) */
	/* { */
	/* 	call(user); */
	/* } */
}
