#include "Client.hpp"
#include <iostream>
#include <unistd.h>

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