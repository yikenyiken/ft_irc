#ifndef Client_HPP
# define Client_HPP

class Client
{
	private:
		int	sockfd;
	public:
		Client();
		Client(int fd);
		Client(const Client &other);
		~Client();

		Client	&operator = (const Client &rhs);
		int		getSockfd() const;
		void	setSockfd(int fd);
};

#endif