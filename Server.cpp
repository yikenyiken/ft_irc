#include "Server.hpp"
#include <iostream>
#include <unistd.h>

int     getServSock(const char *port);
void    handleEvents(const pollfd *pfds);

Server::Server()
{
    std::cout << "Server's Default Constructor called\n";
}

Server::Server(const char *port) 
    : fd(getServSock(port))
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

    if (close(fd) == -1)
        perror("close");
}


Server    &Server::operator = (const Server &rhs) 
{
    (void)rhs;

    return (*this);
}

void    Server::launch()
{
    monitor.add(fd, POLLIN);

    while(true)
    {
        monitor.listen();
        handleEvents(monitor.getList());
    }
}