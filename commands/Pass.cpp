#include "Pass.hpp"
#include <iostream>

Pass::Pass()
{
	std::cout << "Pass's Default Constructor called\n";
}

Pass::Pass(char **args)
{
	std::cout << "Pass's Parametrized Constructor called\n";

	this->args = args;
}

Pass::Pass(const Pass &other) 
{
	std::cout << "Pass's Copy Constructor called\n";

	*this = other;
}

Pass::~Pass() 
{
	std::cout << "Pass's Destructor called\n";
}


Pass	&Pass::operator = (const Pass &rhs) 
{
	(void)rhs;

	return (*this);
}

void	Pass::parse()
{
	// for example check for argument number

	// if any issue occurs set respval (which will trigger the correspodning response in Pass::resp)
}

void	Pass::execute()
{
	// compare server Password with the one in argument list
	// if same allow connection
	// ;reject otherwise
}

void	Pass::resp()
{
	// handle one or multiple responses

	// for example only one to be handled in Pass case
}


ICommand	*Pass::create(char **args)
{
	return (new Pass(args));
}