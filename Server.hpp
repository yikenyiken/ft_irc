#ifndef Server_HPP
# define Server_HPP
# include "Monitor.hpp"
# include <vector>
# include "ClientList.hpp"

class Server
{
    private:
        int         servSock;
        Monitor     monitor;
        ClientList  clients;

    public:
        Server();
        Server(const char *port);
        Server(const Server &other);
        ~Server();

        Server	&operator = (const Server &rhs);
        void    launch();
        void    acceptCnts();
        void    handleClientEvents(const Client &client);

};

#endif