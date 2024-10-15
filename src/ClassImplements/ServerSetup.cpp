#include "../ClassHeaders/Server.hpp"
#include <iostream>
#include <sstream>
// Constructor
Server::Server(char **av, int argc): _server(_fds[0])
{
	_addrlen = sizeof(_address);
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	unsigned short port;
	if (argc > 1)
		port = std::atoi(av[1]);//TODO check if av[1] is number
	else
		port = 6667;
	if (port == 0 || port > 65535) {
		std::cerr << "Invalid port number. Should be between 1 and 65535.\n";
		exit(EXIT_FAILURE);
	}
	_address.sin_port = htons(port);
	if (argc == 3)
		_serverPassword = av[2];
	else
		_serverPassword.clear();

	std::cout << "Port provided: " << port << std::endl; // Print the port number provided

	std::stringstream converter;
	converter << port;

	getIpAddress(converter.str()); // Gets the first available ip address
}

Server::~Server(void)
{
	std::cout << "Destroying server" << std::endl;
}

void    Server::createSocket(void)
{
    if ((_server.fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
}

void    Server::setupPolling(void)
{		
    _fds[0].fd = _server.fd;
	_fds[0].events = POLLIN;
	_server.events = POLLIN;
	for (int i = 1; i < MAX_CLIENTS + 1; ++i)// The +1 offset is to compensate for the server fd being a t_fds[0]
	{
		_fds[i].fd = -1;
		_fds[i].events = POLLIN;
		_clients[i - 1].setFd(&_fds[i]);
	}
}

void    Server::bindSocketToAddress(void)
{
	size_t timeout = 0;
	while (bind(_server.fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		if (!timeout)
		{
			std::cerr << "Bind failed for 0.0.0.0\nRetrying to bind " << inet_ntoa(this->_fall_back_address.sin_addr) <<  " (this may take a while)\n";
			this->_address = this->_fall_back_address;
		}

		else if (timeout > 179)
		{
			std::cerr << "Error: Unable to bind: Timeout\n";
			close(this->_server.fd);
			exit(EXIT_FAILURE);
		}

		sleep(1);
		timeout++;
	}
	std::cout << "Successfully bound to " << inet_ntoa(this->_address.sin_addr) << '\n';
}

void    Server::listenIncomingConnections(void)
{
	if (listen(_server.fd, 1) < 0)
	{
		perror("listen");
		close(_server.fd);
		exit(EXIT_FAILURE);
	}
}
bool Server::findSuitableIp(struct addrinfo *res)
{
    for (struct addrinfo *p = res; p != NULL; p = p->ai_next)
    {
        if (p->ai_family != AF_INET)
            continue;

        struct sockaddr_in *addr = (struct sockaddr_in *)p->ai_addr;
        if (strcmp(inet_ntoa(addr->sin_addr), "127.0.0.1"))
        {
            std::cout << "Resolved IP: " << inet_ntoa(addr->sin_addr) << '\n';
            this->_fall_back_address = *addr;

            createSocket();
            setupPolling();

            if (bind(this->_server.fd, p->ai_addr, p->ai_addrlen) < 0)
            {
                std::cerr << "Bind failed for " << inet_ntoa(addr->sin_addr) << '\n';
                continue;
            }

            std::cout << "Using IP address: " << inet_ntoa(addr->sin_addr) << '\n';
            this->_address = *addr;

            freeaddrinfo(res);
            return true;
        }
    }
    freeaddrinfo(res);
    return false;
}

void Server::noSuitableIpFound(void)
{
    this->_address.sin_addr.s_addr = INADDR_ANY;
    std::cerr << "No suitable IP address found, using 0.0.0.0 instead" << std::endl;

    createSocket();
    setupPolling();
    bindSocketToAddress();
}
void Server::getIpAddress(const std::string& port)
{
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)))
    {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (int status = getaddrinfo(hostname, port.c_str(), &hints, &res))
    {
        std::cerr << "Error: getaddrinfo: " << gai_strerror(status) << '\n';
        exit(EXIT_FAILURE);
    }

    if (!findSuitableIp(res))
        noSuitableIpFound();
}

// Setup the server and then goes in idle state
void    Server::run(void)
{
    listenIncomingConnections();
	std::cout << "Server listening on port " << ntohs(_address.sin_port) << std::endl;

	idle();
}
