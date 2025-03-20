#ifndef Monitor_HPP
# define Monitor_HPP
# include <vector>
# include <poll.h>

class Monitor
{
	private:
		std::vector<pollfd> pfds;
	public:
		Monitor();
		Monitor(const Monitor &other);
		~Monitor();

		Monitor			&operator = (const Monitor &rhs);
		void			listen();
		void			add(int fd, short events);
		const pollfd	*getList();
};

#endif