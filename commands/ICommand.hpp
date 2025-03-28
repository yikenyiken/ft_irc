#ifndef ICommand_HPP
# define ICommand_HPP

class ICommand
{	
	public:
		char	**args;
		int		respVal;

		virtual void	parse() = 0;
		virtual void	execute() = 0;
		virtual void	resp() = 0;
};

#endif