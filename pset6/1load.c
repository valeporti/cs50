#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
    char* format = "QUERY_STRING=\"%s\" REDIRECT_STATUS=200 SCRIPT_FILENAME=\"%s\" php-cgi";
    char command[strlen(format) + (3 - 2) +(3 - 2) + 1];
    sprintf(command, format, "lal", "LOL");
    printf("%s\n", command);
    int primero = strlen(format) + (3 - 2) +(3 - 2) + 1;
    int despues = strlen(command);
    printf("%i,%i.\n%s\n", primero, despues, command);
    
    FILE* file = popen(command, "r");
        if (file != NULL)
    {
            for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        printf("%i ", c);
    }
    }

    

    printf("finito");
    
    pclose(file);

}


