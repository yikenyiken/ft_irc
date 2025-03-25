#include "Server.hpp"
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#define LEN 2
#define READING LEN - 1

using namespace std;

int     getServSock(const char *port);
void	rtimeThrow(std::string syscall);

Server::Server()
{
	std::cout << "Server's Default Constructor called\n";
}

Server::Server(const char *port) 
	: servSock(getServSock(port))
{
	std::cout << "Server's Parametrized Constructor called\n";
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

void	Server::handleClientEvents(const Client &client)
{
	int		fd = client.getSockfd();
	char	data[LEN];
	ssize_t	bytes_read = recv(fd, data, READING, 0);
	string	temp;

	while (bytes_read && bytes_read != -1)
	{
		data[bytes_read] = '\0';
		temp += data;
		bytes_read = recv(fd, data, READING, 0);
	}

	if (bytes_read == (ssize_t)-1 && errno != EWOULDBLOCK)
		rtimeThrow("recv");

	if (!bytes_read)
	{
		monitor.remove(fd);
		clients.remove(fd);
		return ;
	}

	cout << temp;
}