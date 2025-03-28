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

std::ostream	&Client::operator << (std::string s)
{
	buf << s;

	return (buf);
}

std::string	&Client::operator >> (std::string &ostr)
{
	std::string	line;

	std::getline(buf, line);

	if (buf.eof())
	{
		buf.clear();
		buf << line;
		line = "";
	}

	ostr = line;

	return (ostr);
}

std::ostream	&operator << (std::ostream &os, Client &client)
{
	os << "fd: " << client.getSockfd() << std::endl;
	os << "buf: " << client.buf.str();

	return (os);
}