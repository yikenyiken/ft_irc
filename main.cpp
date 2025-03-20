#include <iostream>
#include <string>
#include "Server.hpp"

void    usrInpParse(int ac, char **av);

int main(int argc, char **argv)
{
    usrInpParse(argc, argv);

    Server  server(argv[1]);
}