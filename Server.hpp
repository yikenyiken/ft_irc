#ifndef Server_HPP
# define Server_HPP
# define CMDS_N 1
# include <vector>
# include "Monitor.hpp"
# include "ClientList.hpp"
# include "commands/ICommand.hpp"

class Server
{
    private:
        int         servSock;
        Monitor     monitor;
        ClientList  clients;
        std::string	cmdNames[CMDS_N];
        ICommand    *(*cmdFactory[CMDS_N])(char **args);

    public:
        Server();
        Server(const char *port);
        Server(const Server &other);
        ~Server();

        Server	&operator = (const Server &rhs);
        void    launch();
        void    acceptCnts();
        void    handleClientEvents(Client &client);
        void    procCmds(Client &client);
};

#endif