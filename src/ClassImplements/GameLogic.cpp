#include "../ClassHeaders/Game.hpp"

void	Game::updateNextActive(void)
{
	std::vector<User *>::iterator it = _participants.begin();
	while (it != _participants.end())
	{
		if ((*it)->getStatus() == ACTIVE)
		{
			(*it)->setStatus(PARTICIPATING);
			if (++it != _participants.end())
				(*it)->setStatus(ACTIVE);
			else
				(*_participants.begin())->setStatus(ACTIVE);
		}
		it++;
	}
}

void	Game::update(User & user, std::vector<std::string> words)
{
	commandHandler(user, words);
	// TODO:Set next user as active
	// TODO:Let new people enter if round isnt active
}
