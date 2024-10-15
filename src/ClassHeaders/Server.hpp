#ifndef SERVER_HPP
# define SERVER_HPP

// Custom class: Server
#include "Game.hpp"
#include "User.hpp"
#include <vector>
# include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <vector>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

class	Server
{
	public:
		// Constructor
		Server	(	char **av, int argc	);

		// Destructor
		~Server	(void);

		// Start the server
		void	run(void);

		// Start a game with all current users
		void	startGame(void);

	private:
		void		createSocket		(void);
		void		setupPolling		(void);
		void		bindSocketToAddress		(void);
		void		listenIncomingConnections	(void);
		bool		findSuitableIp		(struct addrinfo *res);
		void		noSuitableIpFound	(void);
		void		getIpAddress		(const std::string& port);
		void 		handleNewConnection();
		void		idle			(void);


		void		handleClientMessage(User &);
		void		commandHandler(User &, std::string);
		bool		isServerCommand(std::string &)const;
		void		serverCommandHandler(User &, std::vector<std::string> &);
		void		gameCommandHandler(User &, std::vector<std::string>&);
		void		sendAll(User &, std::string);

		void		changeNick(User &, std::vector<std::string>);

	private:
		/* int			_server_socket; */
		struct sockaddr_in	_address;
		struct sockaddr_in	_fall_back_address;
		int			_addrlen;
		struct pollfd &		_server;
		std::string         _serverPassword;

		User			_clients[MAX_CLIENTS];
		struct pollfd		_fds[MAX_CLIENTS + 1];
		std::vector<User>	_users;

		// Game stuff
		Game			_game;
};

#endif

