#include "Server.hpp"
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include "commands/Pass.hpp"

#define LEN 2
#define READING LEN - 1

using namespace std;

int     getServSock(const char *port);
void	rtimeThrow(std::string syscall);
char	**split(const char *str, char sep);

Server::Server()
{
	std::cout << "Server's Default Constructor called\n";
}

Server::Server(const char *port) 
	: servSock(getServSock(port))
{
	std::cout << "Server's Parametrized Constructor called\n";

	string	tmpCmdNames[CMDS_N] = {"PASS"}; // add command names here
	
	for (int i = 0; i < CMDS_N; i++)
		cmdNames[i] = tmpCmdNames[i];

	ICommand	*(*tmpCmdFactory[CMDS_N])(char **args) = {Pass::create}; // add facatory methods here

	for (int i = 0; i < CMDS_N; i++)
		cmdFactory[i] = tmpCmdFactory[i];
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

		for (std::size_t i = 0; i < lst.size(); i++)
		{
			if ((lst[i].revents & POLLIN) && lst[i].fd == servSock)
				acceptCnts();
			if ((lst[i].revents & POLLIN) && lst[i].fd != servSock)
				handleClientEvents(clients.getClientByFd(lst[i].fd));
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
	int		fd = client.getSockfd();
	char	data[LEN];
	ssize_t	bytes_read = recv(fd, data, READING, 0);

	while (bytes_read && bytes_read != -1) //read all available data into client buffer
	{
		data[bytes_read] = '\0';
		client << data;
		bytes_read = recv(fd, data, READING, 0);
	}

	if (bytes_read == (ssize_t)-1 && errno != EWOULDBLOCK)
		rtimeThrow("recv");

	if (!bytes_read) // connection closed
	{
		monitor.remove(fd);
		clients.remove(fd);
		return ;
	}

	procCmds(client);
}

// search for word (delimited by spaces or start/end of string)
int	foundWrd(string str, string word)
{
	size_t	pos = str.find(word);

	while (pos != string::npos)
	{
		if (
				(!pos && (str[word.size()] == ' ' || str.size() == word.size()))
				||
				(pos && str[pos - 1] == ' ' &&
					(
						str[pos + word.size()] == ' ' ||
						str[pos + word.size()] == '\0'
					)
				)
		)
			return (1);
		
		pos = str.find(word, pos + word.size());
	}

	return (0);
}

 // process data (lines) stored in client buffer
void	Server::procCmds(Client &client)
{
	string		line;
	ICommand	*cmd = NULL;

	client >> line; //getting line from client buffer

	while (!line.empty())
	{
		for (int i = 0; i < CMDS_N; i++)
		{
			if (foundWrd(line, cmdNames[i]))
			{
				cmd = cmdFactory[i](split(line.c_str(), ' '));
				cmd->parse();
				cmd->execute();
				cmd->resp();
				break ;
			}

		}
		client >> line;
	}
}