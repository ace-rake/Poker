#include "../ClassHeaders/Server.hpp"

void	Server::startGame()
{
	std::vector<User *> clients;
	for (User & client: _clients)
		if (client.getFd().fd != -1)
			clients.push_back(&client);
	_game.startGame(clients);
}
void		Server::changeNick(User & user, std::vector<std::string> words)
{
	if (words.size() <= 1)
		user.sendToClient("ERROR: Please give a nick\n");
	else
		user.setName(words[1]);	
}

void	Server::serverCommandHandler(User & user, std::vector<std::string> & words)
{
	if (!words[0].compare("NICK"))
	{
		changeNick(user, words);
		return ;
	}
	if (!words[0].compare("START"))
	{
		startGame();
		return ;
	}
}
