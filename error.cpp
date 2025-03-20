#include <string>
#include <cstring>
#include <stdexcept>

void	rtimeThrow(std::string syscall)
{
	std::string message = syscall + ": " + strerror(errno);

	throw std::runtime_error(message);
}