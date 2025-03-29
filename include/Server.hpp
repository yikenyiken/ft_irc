#ifndef Server_HPP
# define Server_HPP
# include "Monitor.hpp"
# include "ClientList.hpp"
# include "commands/ICommand.hpp"
# include <vector>

# define CMDS_N 1

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