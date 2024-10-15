#include "../ClassHeaders/User.hpp"
#include <iostream>
#include <sys/socket.h>

// Constructor
User::User()
{
	std::cout << "User:\tcreating object\n";
	_status = OUT;
	_bet = 0;
	_stack = 0;
}

User::User(std::string nick, int stack): _name(nick), _stack(stack), _bet(0)
{
	std::cout << "User:\tcreating object\n";
	_status = OUT;
}

// Destructor
User::~User(void)
{
	std::cout << "User:\tdestroying object\n";
}

void	User::sendToClient(std::string msg)
{
	msg.append("\n");
	send(_fd->fd, msg.c_str(), msg.size(), 0);
}

void	User::clear()
{
	_fd->fd = -1;
	_name = "";
	_stack = 0;
	_first = NULL;
	_second = NULL;
}

std::ostream &	operator<<(std::ostream & os, User & other)
{
	os << other._name << std::endl;
	os << other._fd->fd << std::endl;
	os << other._stack << std::endl;
	os << other._bet << std::endl;
	os << other._first << std::endl;
	os << other._second << std::endl;
	return (os);
}
