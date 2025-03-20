#include <iostream>
#define SUCCESS 0
#define FAILURE 1

using namespace std;

int isZeroSeq(char *str)
{
    if (*str == '\0')
        return (0);

    while (*str)
    {
        if (*str != '0')
            return (0);

        str++;
    }

    return (1);
}

int portEval(char *port)
{
    int n = strtol(port, NULL, 10);

    if ((n == 0 && !isZeroSeq(port)) || n < 0 || n > 65536)
    {
        cerr << "Invalid Port: " << port << endl;
        return (FAILURE);
    }

    return (SUCCESS);
}

int argNumEval(int ac)
{
    if (ac != 2)
    {
        cerr << "usage: ./server port\n";
        return (FAILURE);
    }

    return (SUCCESS);
}

void    usrInpParse(int ac, char **av)
{
    if (argNumEval(ac) || portEval(av[1]))
        exit(FAILURE);
}

