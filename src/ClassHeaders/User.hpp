#ifndef USER_HPP
# define USER_HPP

// Custom class: User
#include "Card.hpp"
#include <ostream>
#include <string>
#include <sys/poll.h>

enum	status
{
	WAITING,
	PARTICIPATING,
	OUT,
	ACTIVE
};

class	User
{
	public:
		// Constructor
		User	(	void	);
		User	(std::string, int);

		// Destructor
		~User	(void);

		void	sendToClient(std::string);

		// Getters and Setter

		void	setFirst(Card &card){_first = &card;}
		void	setSecond(Card &card){_second = &card;}
		struct pollfd&	getFd(void)const{return *_fd;}
		void	setFd(struct pollfd *fd){_fd = fd;}
		void	setStack(int newStack){_stack = newStack;}
		void	setName(std::string name){_name = name;}
		void	setStatus(status status){_status = status;}
		status	getStatus(void)const{return _status;}
		std::string getName(void)const{return _name;}
		int	getBet()const{return _bet;}
		void	setBet(int newBet){_bet = newBet;}

		void	clear(void);

		friend std::ostream & operator << (std::ostream & os, User & other);

	protected:
		/*_*/;

	private:
		struct pollfd*		_fd;
		std::string	_name;
		int		_stack;
		int		_bet;
		Card *		_first;
		Card *		_second;
		status		_status;
		/*_*/;
};

#endif

