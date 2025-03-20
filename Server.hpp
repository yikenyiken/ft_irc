#ifndef Server_HPP
# define Server_HPP
# include "Monitor.hpp"

class Server
{
    private:
        int     fd;
        Monitor monitor;

    public:
        Server();
        Server(const char *port);
        Server(const Server &other);
        ~Server();

        Server	&operator = (const Server &rhs);
        void    launch();
};

#endif