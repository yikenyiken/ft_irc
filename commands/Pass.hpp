#ifndef Pass_HPP
# define Pass_HPP
# include "ICommand.hpp"

class Pass : public ICommand
{
	public:
		Pass();
		Pass(char **args);
		Pass(const Pass &other);
		~Pass();

		Pass			&operator = (const Pass &rhs);
		void			parse();
		void			execute();
		void			resp();

		static ICommand	*create(char **args);
};

#endif