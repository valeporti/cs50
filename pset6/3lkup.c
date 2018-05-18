/**
 * 2lkup.c
 *
 * Computer Science 50
 * Problem Set 6
 * lookup function
 *
 * The sole intention of this program is to undertand how const char* works
 * and dynamically allocate memory for array
 * 
 */
 
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
//for printing pointers
#include <inttypes.h>

const char* func1(const char* ruta);

int main(void)
{
    char path[6];
    for (int i = 0; i < 5; i ++)
    {
        path[i] = 'a'+ i;
    }
    path[2] = '.';
    path[5] = '\0';
    
    const char* type = func1(path);
    printf("%s\n", type);

}

const char* func1(const char* path)
{
     char css[4] = ".css";
    char html[5] = ".html";
    char gif[4] = ".gif";
    char ico[4] = ".ico";
    char jpg[4] = ".jpg";
    char js[4] = ".de";
    char php[4] = ".php";
    char png[4] = ".png";
    
    char* point = strrchr(path,'.');
    
    if (strcasecmp(point, css) == 0)
    {
        return "text/css";
    }
    else if (strcasecmp(point, html) == 0)
        return "text/html";
    else if (strcasecmp(strrchr(path,'.'), gif) == 0)
        return "image/gif";
    else if (strcasecmp(strrchr(path,'.'), ico) == 0)
        return "image/x-icon";
    else if (strcasecmp(strrchr(path,'.'), jpg) == 0)
        return "image/jpeg";
    else if (strcasecmp(strrchr(path,'.'), js) == 0)
        return "text/javascript";
    else if (strcasecmp(strrchr(path,'.'), php) == 0)
        return "text/x-php";
    else if (strcasecmp(strrchr(path,'.'), png) == 0)
        return "image/png";
    else
        return NULL;

    
}

