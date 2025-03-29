#include "../include/Client.hpp"
#include "../include/error.h"
#include <iostream>
#include <unistd.h>
#include <netdb.h>

#define BUFLEN 2
#define RDLEN BUFLEN - 1

Client::Client()
{
	std::cout << "Client's Default Constructor called\n";
}

Client::Client(int fd) : sockfd(fd)
{
	std::cout << "Client's Parametrized Constructor called\n";
}

Client::Client(const Client &other) 
{
	std::cout << "Client's Copy Constructor called\n";

	*this = other;
}

Client::~Client() 
{
	std::cout << "Client's Destructor called\n";
}


Client	&Client::operator = (const Client &rhs) 
{
	sockfd = rhs.sockfd;

	return (*this);
}

int	Client::getSockfd() const
{
	return (sockfd);
}

void	Client::setSockfd(int fd)
{
	sockfd = fd;
}

//getting a line from the buffer
std::string	&Client::operator >> (std::string &line)
{
	std::getline(buf, line);

	if (buf.eof())
	{
		buf.clear();
		buf << line;
		line = "";
	}

	return (line);
}

// reads from socket to buffer
// returns 0 if connection closed ;otherwise non-zero is returned
ssize_t	Client::recvData()
{
	char	data[BUFLEN];
	ssize_t	bytes_read = recv(sockfd, data, RDLEN, 0);

	while (bytes_read && bytes_read != -1) // read all available data into client buffer
	{
		data[bytes_read] = '\0';
		buf << data;
		bytes_read = recv(sockfd, data, RDLEN, 0);
	}

	if (bytes_read == (ssize_t)-1 && errno != EWOULDBLOCK)
		rtimeThrow("recv");

	return (bytes_read);
}


std::ostream	&operator << (std::ostream &os, Client &client)
{
	os << "fd: " << client.getSockfd() << std::endl;
	os << "buf: " << client.buf.str();

	return (os);
}
