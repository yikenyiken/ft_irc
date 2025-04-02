#ifndef Client_HPP
# define Client_HPP
# include <sstream>
# include <unistd.h>

class Client
{
	private:
		int					sockfd;
		std::stringstream	buf;
	public:
		Client();
		Client(int fd);
		Client(const Client &other);
		~Client();

		Client			&operator = (const Client &rhs);
		int				getSockfd() const;
		void			setSockfd(int fd);
		std::string		&operator >> (std::string &line);
		ssize_t			recvData();

		friend std::ostream	&operator << (std::ostream &os, Client &client);
};

#endif