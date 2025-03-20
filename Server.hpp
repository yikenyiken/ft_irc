#ifndef Server_HPP
# define Server_HPP

class Server
{
    private:
        int port;
        int fd;

    public:
        Server();
        Server(const char *port);
        Server(const Server &other);
        ~Server();

        Server	&operator = (const Server &rhs);
};

#endif