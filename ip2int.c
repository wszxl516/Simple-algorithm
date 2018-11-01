#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned int str2int(char string[])
{
    unsigned int num = 0;
    char *delim = ".";
    int move = 24;
    char *str = strtok(string, delim);
    num += atoi(str) << move;
    while(1)
    {
        move -= 8;
        str = strtok(NULL, delim);
        if (str == NULL)
            break ;
        num += atoi(str) << move;
    }
    return num;
}

void int2str(int num, char *str)
{
    
    char *delim = ".";
    char n[3] = {};
    int move = 24;
    while(1)
    {
        sprintf(n, "%u", (num >> move)& 255);
        strcat(str, n);
        if (move == 0) break;
        strcat(str, delim);
        move -= 8;
    }

}

int main(int argv, char **args)
{
    if(argv < 2)
    {
        printf("Usage:\n"
                    "\tEnter an ip address to return a number.\n"
                    "\tEnter a number to return an IP address.\n");
        exit(0);
    }
    if( NULL == strstr(args[1], "."))
    {
        char ip_str[16] = {} ;
        int num = atoi(args[1]);
        int2str(num, ip_str);
        printf("%s\n", ip_str);
    }
    else
    {
        unsigned int ret = 0;
        ret = str2int(args[1]);
        printf("%u\n", ret);
    }
}
