#include "../include/Server.hpp"
#include "../include/error.h"
#include "../include/utils.h"
#include "../include/servSock.h"
#include "../include/commands/Pass.hpp"
#include "../include/utils.h"
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <new>

using namespace std;

Server::Server()
{
	std::cout << "Server's Default Constructor called\n";
}

Server::Server(const char *port) 
	: servSock(getServSock(port))
{
	std::cout << "Server's Parametrized Constructor called\n";

	string	tmpCmdNames[CMDS_N] = {"PASS"}; // add command names here

	ACommand	*(*tmpCmdFactory[CMDS_N])(Server &server, Client &client, char **args)
	= {Pass::create}; // add facatory methods here

	for (int i = 0; i < CMDS_N; i++)
	{
		cmdNames[i] = tmpCmdNames[i];
		cmdFactory[i] = tmpCmdFactory[i];
	}
}

Server::Server(const Server &other) 
{
	std::cout << "Server's Copy Constructor called\n";

	*this = other;
}

Server::~Server() 
{
	std::cout << "Server's Destructor called\n";

	if (close(servSock) == -1)
		perror("close");
}


Server    &Server::operator = (const Server &rhs) 
{
	(void)rhs;

	return (*this);
}

void    Server::launch()
{
	monitor.add(servSock, POLLIN);

	while(true)
	{
		const vector<pollfd>	&lst = monitor.getList();

		monitor.listen();

		int	fdsHandled = 0;

		for (std::size_t i = 0; i < lst.size(); i++)
		{
			if (lst[i].revents & POLLIN)
			{
				if (lst[i].fd == servSock)
					acceptCnts();
				else
					handleClientEvents(clients.getClientByFd(lst[i].fd));

				++fdsHandled;
			}

			if (monitor.getReadyFds() == fdsHandled)
				break ;
		}
	}
}

void    Server::acceptCnts()
{
	int fd;

	if ((fd = accept(servSock, NULL, NULL)) == -1)
		rtimeThrow("accept");

	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		rtimeThrow("fcntl");

	monitor.add(fd, POLLIN);
	clients.add(fd);
}

void	Server::handleClientEvents(Client &client)
{
	int closed = !client.recvData();

	if (closed) // connection closed
	{
		monitor.remove(client.getSockfd());
		clients.remove(client.getSockfd());
		return ;
	}

	procCmds(client);
}

 // process data (i.e lines) stored in client buffer
void	Server::procCmds(Client &client)
{
	ACommand	*cmd;
	string		line;

	client >> line;

	while (!line.empty())
	{
		for (int i = 0; i < CMDS_N; i++)
		{
			if (foundWrd(line, cmdNames[i])) // command [name and factoryMethod] share same index
			{
				cmd = cmdFactory[i](*this, client, split(line.c_str(), ' ')); // cmdFactory[indexOfFactoryMethod](argsList)

				cmd->parse();
				cmd->execute();
				cmd->resp();

				delete cmd;
				break ;
			}
		}

		client >> line;
	}
}