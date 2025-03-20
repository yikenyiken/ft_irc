#include "Monitor.hpp"
#include <iostream>
#include <cstring>

void	rtimeThrow(std::string syscall);

Monitor::Monitor()
{
	std::cout << "Monitor's Default Constructor called\n";
}

Monitor::Monitor(const Monitor &other) 
{
	std::cout << "Monitor's Copy Constructor called\n";

	*this = other;
}

Monitor::~Monitor() 
{
	std::cout << "Monitor's Destructor called\n";
}


Monitor	&Monitor::operator = (const Monitor &rhs) 
{
	(void)rhs;

	return (*this);
}

void	Monitor::add(int fd, short events)
{
	pollfd	pfd;

	pfd.fd = fd;
	pfd.events = events;

	pfds.push_back(pfd);
}

void	Monitor::listen()
{
	if (poll(pfds.data(), pfds.size(), -1) == -1)
		rtimeThrow("poll");
}

const pollfd	*Monitor::getList()
{
	return (pfds.data());
}