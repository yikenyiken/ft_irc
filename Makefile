NAME	= server
FLAGS	= -Werror -Wall -Wextra -std=c++98
HEADERS	= Server.hpp Client.hpp ClientList.hpp Monitor.hpp
SRCS	= main.cpp Server.cpp Monitor.cpp Client.cpp ClientList.cpp userInpParse.cpp servSockGen.cpp error.cpp
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