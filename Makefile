NAME	= server
FLAGS	= -Werror -Wall -Wextra -std=c++98
HEADERS	= Server.hpp Client.hpp ClientList.hpp Monitor.hpp
SRCS	= src/main.cpp src/Server.cpp src/Monitor.cpp src/Client.cpp src/ClientList.cpp src/userInpParse.cpp \
		  src/error.cpp src/split.cpp src/commands/Pass.cpp src/servSockGen.cpp src/utils.cpp
OBJS	= $(SRCS:.cpp=.o)
CXX		= c++

all	: $(NAME)

%.o	: %.cpp $(HEADERS)
	$(CXX) -c $< -o $@ $(FLAGS)

$(NAME)	: $(OBJS)
	$(CXX) $^ -o $@ $(FLAGS)

clean	:
	@rm -rf $(OBJS)

fclean	: clean
	@rm -rf $(NAME)

re	: fclean all

.PHONY	: clean