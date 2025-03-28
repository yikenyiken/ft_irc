#ifndef Client_HPP
# define Client_HPP
# include <sstream>

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
		std::ostream	&operator << (std::string s);
		std::string		&operator >>(std::string &ostr);

		friend std::ostream	&operator << (std::ostream &os, Client &client);
};

#endif