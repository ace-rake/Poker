#include "../ClassHeaders/Game.hpp"
#include <iostream>

// Constructor
Game::Game()
{
	_participants.clear();
	_queu.clear();
	_deck = Deck();
	_field.clear();
	_pot = 0;
	_gameIsRunning = false;
	_inRound = false;
}

int	Game::startGame(std::vector<User *> participants)
{
	if (_gameIsRunning)
	{
		std::cout << "Game is already running" << std::endl;
		return 1;
	}
	// Add all current connected users to the starting game
	if (participants.size() <= 1)
	{
		std::cout << "Cant start a game with one participant" << std::endl;
		return 1;
	}
	for (User * user : participants)
	{
		_participants.push_back(user);
		user->setStatus(WAITING);
	}
	_gameIsRunning = true;	
	std::cout << "Starting game" << std::endl;
	sendToAllGame("Starting game");
	return 0;
}
void	Game::sendToAllGame(std::string msg)
{
	for (size_t i = 0; i < _participants.size(); i++)
		_participants[i]->sendToClient(msg.append("\n"));
}

void	Game::addToQueu(User & user)
{
	_queu.push_back(&user);
}

void	Game::addQueuToGame()
{
	for (User * user: _queu)
		_participants.push_back(user);
}

// Destructor
Game::~Game(void)
{
	std::cout << "Game:\tdestroying object\n";
}
