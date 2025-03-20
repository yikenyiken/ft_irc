#define SUCCESS 0
#define FAILURE 1
#include <iostream>
#include <string>
#include "Server.hpp"

using namespace std;

void    usrInpParse(int ac, char **av);

int main(int argc, char **argv)
{
    usrInpParse(argc, argv);
    
    Server  server(argv[1]);

    try
    {
        server.launch();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;

        return (FAILURE);
    }

    return (SUCCESS);
}