#include "../ClassHeaders/Server.hpp"
#include "../ClassHeaders/Game.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <sys/socket.h>
#include <unordered_set>


void Server::handleNewConnection()
{
        int new_connection = accept(_server.fd, (struct sockaddr *) &_address, (socklen_t *)&_addrlen);
        for (int i = 0; i < MAX_CLIENTS ; ++i)
                if (_clients[i].getFd().fd == -1)
                {
                        _clients[i].getFd().fd = new_connection;
                        _clients[i].getFd().events = POLLIN;
                        std::cout << "Client connected with fd " << new_connection << std::endl;
			sendAll(_clients[i], "New client connected");
			std::cout << _clients[i];
                        break;
                }
}                                                                                                                                  


void Server::idle()                                                                                                 
{
        while (1)
        {
  
                try {
                        int retval = poll(_fds, MAX_CLIENTS, -1);
  
                        if (retval > 0)
                        {
                                if (_server.revents & POLLIN)
                                        handleNewConnection();
                                for (int i = 0; i < MAX_CLIENTS; ++i)
                                        if (_clients[i].getFd().fd != -1 && (_clients[i].getFd().revents & POLLIN))
					{
                                                handleClientMessage(_clients[i]);
					}
                        }
                }
                catch (std::runtime_error &e)
                {
                        std::cerr << e.what() << std::endl;
                }
        }
}

void	Server::handleClientMessage(User & client)
{
	char buffer[BUFFER_SIZE];                                                                 
	int clientFd = client.getFd().fd;
	int valread = recv(clientFd, buffer, BUFFER_SIZE, 0);
	if (valread == 0)
	{
		close(clientFd);
		client.clear();
		std::cout << "Client disconnected" <<std::endl;
	}
	else
	{
		buffer[valread] = '\0';
		std::string msg(buffer);
		std::cout << "Received from " << clientFd << ":" << msg << std::endl;
		try{
			commandHandler(client, msg);
		}                                                                                 
		catch (std::runtime_error &e)                                                     
		{                                                                                 
			std::cout << e.what();                                                    
		}                                                                                 
	}                                                                                         
}


std::vector<std::string> split_sentence(std::string sen) {

	// Create a stringstream object
	std::stringstream ss(sen);

	// Variable to hold each word
	std::string word;

	// Vector to store the words
	std::vector<std::string> words;

	// Extract words from the sentence
	while (ss >> word) {

		// Add the word to the vector
		words.push_back(word);
	}

	return words;
}

bool	Server::isServerCommand(std::string &command)const
{
	std::unordered_set<std::string> commands = {"NICK", "START"};
	return (commands.find(command) != commands.end());
}

void	Server::commandHandler(User & user, std::string command)
{
	std::vector<std::string> words = split_sentence(command);
	if (isServerCommand(words[0]))
	{
		// Handle server command
		serverCommandHandler(user, words);
	}
	else
	{
		// Handle game command
		gameCommandHandler(user, words);
	}
}

void	Server::sendAll(User & except, std::string msg)
{
	if (except.getName().empty())
		msg = "Client " + std::to_string(except.getFd().fd) + ": " + msg;
	else
		msg = except.getName() + ": " + msg;
	for (int i = 0; i < MAX_CLIENTS; i++)
		if (i != _server.fd && _clients[i].getFd().fd != -1 && _clients[i].getFd().fd != except.getFd().fd)
			_clients[i].sendToClient(msg);
}
