#include "Server.hpp"
#include <iostream>

int getServSock(const char *port);

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
}


Server    &Server::operator = (const Server &rhs) 
{
    (void)rhs;

    return (*this);
}