#ifndef ClientList_HPP
# define ClientList_HPP
# include <vector>
# include "Client.hpp"

class ClientList
{
	private:
		std::vector<Client> lst;
	public:
		ClientList();
		ClientList(const ClientList &other);
		~ClientList();

		ClientList		&operator = (const ClientList &rhs);
		void			add(int fd);
		void			remove(int fd);
		Client	&getClientByFd(int fd);
};

#endif