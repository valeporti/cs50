//
// server.c
//
// Computer Science 50
// Problem Set 6
//

// feature test macro requirements
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LimitRequestFields 50
#define LimitRequestFieldSize 4094
#define LimitRequestLine 8190

// number of bytes for buffers
#define BYTES 512

// header files
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

// types
typedef char BYTE;

// prototypes
bool connected(void);
void error(unsigned short code);
void freedir(struct dirent** namelist, int n);
void handler(int signal);
char* htmlspecialchars(const char* s);
char* indexes(const char* path);
void interpret(const char* path, const char* query);
void list(const char* path);
bool load(FILE* file, BYTE** content, size_t* length);
const char* lookup(const char* path);
bool parse(const char* line, char* path, char* query);
const char* reason(unsigned short code);
void redirect(const char* uri);
bool request(char** message, size_t* length);
void respond(int code, const char* headers, const char* body, size_t length);
void start(short port, const char* path);
void stop(void);
void transfer(const char* path, const char* type);
char* urldecode(const char* s);

// server's root
/**
 * Es la ruta que tiene que seguir el servidor (en este caso public)
 */
char* root = NULL;

// file descriptor for sockets
/**
 * Son como punteros (como FILE* pointers), pero las funciones que lo utilizarán no trabajarán con punteros
 * son funciones que leen archivos o leer de conexiones de red
 * Se mantiene localizado el "pointer" del cliente (client file descriptor), y el del servidor al servidor web
 */
int cfd = -1, sfd = -1;

// flag indicating whether control-c has been heard
/**
 * Para detener el programa (del infinite loop)
 */
bool signaled = false;

int main(int argc, char* argv[])
{
    // a global variable defined in errno.h that's "set by system 
    // calls and some library functions [to a nonzero value]
    // in the event of an error to indicate what went wrong"
    errno = 0;

    // default to port 8080
    int port = 8080;

    // usage
    const char* usage = "Usage: server [-p port] /path/to/root";
    
    /**
     * Para empezar, "parse" = "Analizar"
     * Este loop, analiza cada argumento entrado en main (marca -1 cuando se acaban los argumentos) y de acuerdo al caso realiza una acción
     * si es 'h' entonces indica como se debería usar con varibale "usage" y si es 'p port' 
     */
    // parse command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, "hp:")) != -1)
    {
        switch (opt)
        {
            // -h
            case 'h':
                printf("%s\n", usage);
                return 0;

            // -p port
            case 'p':
                port = atoi(optarg);//optarg es un pointer al valor de "option argument" en getopt el cual debería ser número por eso atoi()
                break;// finalmente break porque el port debe ser 8080 el default pues en realidad no queremos salir a la internet
        }
    }

    // ensure port is a non-negative short and path to server's root is specified
    if (port < 0 || port > SHRT_MAX || argv[optind] == NULL || strlen(argv[optind]) == 0)// "optind" es un int puesto por getopt que indica una posición en el array de argv
    {
        // announce usage
        printf("%s\n", usage);

        // return 2 just like bash's builtins
        return 2;
    }

    // start server (en ese port)
    start(port, argv[optind]);

    // listen for SIGINT (aka control-c)
    /**
     * Es un "event listener" para detener el programa ci ctl^c es pulsado
     */
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);

    // a message and its length
    char* message = NULL;
    size_t length = 0;

    // path requested
    char* path = NULL;

    // accept connections one at a time
    /**
     * Esteinfinite loop sirve para simular que el servidor está esperando por alguna request de algun user en la internet
     */
    while (true)// infinite loop
    {
        /**
         * Se liberan variables pues luego se usará malloc para estas y es para asegurar que no haya nada
         */
        // free last path, if any
        if (path != NULL)
        {
            free(path);
            path = NULL;
        }

        // free last message, if any
        if (message != NULL)
        {
            free(message);
            message = NULL;
        }
        length = 0;

        // close last client's socket, if any
        if (cfd != -1)
        {
            close(cfd);
            cfd = -1;
        }

        // check for control-c
        if (signaled)
        {
            stop();
        }

        // check whether client has connected
        /**
         * Como decir, sí el cliente está conectado al servidor o no
         */
        if (connected())
        {
            // check for request
            /**
             * Como decir, sí el cliente está conectado al servidor o no
             * message is a char*: it's a double pointer 
             * request (char** message, ...) pues lo que hará será modificar el address del string donde apunta *message
             */
            if (request(&message, &length))
            {
                /**
                 * Nos permite leer la primera línea del request (HTTP / 1.1)
                 */
                // extract message's request-line
                // http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
                const char* haystack = message;
                const char* needle = strstr(haystack, "\r\n");//reading string by string, to read end of line
                if (needle == NULL)
                {
                    error(500);
                    continue;
                }
                /**
                 * Digamos, el lenght de los chars mas 2 de \r y \n más 1 para \0
                 */
                char line[needle - haystack + 2 + 1];//Subtracting two pointers gives a logically explainable result - the offset in memory between two pointers
                strncpy(line, haystack, needle - haystack + 2);//char * strncpy(char * dest, const char * src, size_t n)
                line[needle - haystack + 2] = '\0';

                // log request-line
                printf("%s", line);

                // parse request-line
                char abs_path[LimitRequestLine + 1];
                char query[LimitRequestLine + 1];
                if (parse(line, abs_path, query))
                {
                    // URL-decode absolute-path
                    char* p = urldecode(abs_path);
                    if (p == NULL)
                    {
                        error(500);
                        continue;
                    }

                    // resolve absolute-path to local path
                    /**
                     * path será formada por dos partes, el root que es la dirección que se tomó al principio de argumento
                     * y por "p" que es la dirección URL sin signos de % u otros especiales (con función urldecode)
                     */
                    path = malloc(strlen(root) + strlen(p) + 1);
                    if (path == NULL)
                    {
                        error(500);
                        continue;
                    }
                    strcpy(path, root);
                    strcat(path, p);
                    free(p);

                    // ensure path exists
                    if (access(path, F_OK) == -1)
                    {
                        error(404);
                        continue;
                    }

                    // if path to directory
                    struct stat sb;//struct star es una estructura especial que da detalles del la información enviada
                    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
                    {
                        /**
                         * Por convención al final de un request debe de haber un '/' por ello, si no existe , ponerlo
                         */
                        // redirect from absolute-path to absolute-path/
                        if (abs_path[strlen(abs_path) - 1] != '/')
                        {
                            char uri[strlen(abs_path) + 1 + 1];
                            strcpy(uri, abs_path);
                            strcat(uri, "/");
                            redirect(uri);
                            continue;
                        }

                        // use path/index.php or path/index.html, if present, instead of directory's path
                        /**
                         * si el path implica apertura de archivo terminación .html o .php, ponerlo en path, si no, abrir directory y enlistar contenido
                         */
                        char* index = indexes(path);
                        if (index != NULL)
                        {
                            free(path);
                            path = index;
                        }

                        // list contents of directory
                        else
                        {
                            list(path);
                            continue;
                        }
                    }

                    // look up MIME type for file at path
                    /**
                     * es para ahora sí ver que se hace con cada tipo de archivo, si es php, interpretar, si no transferir el arcchivo para mostrarlo
                     */
                    const char* type = lookup(path);
                    if (type == NULL)
                    {
                        error(501);
                        continue;
                    }

                    // interpret PHP script at path
                    if (strcasecmp("text/x-php", type) == 0)
                    {
                        interpret(path, query);
                    }

                    // transfer file at path
                    else
                    {
                        transfer(path, type);
                    }
                }
            }
        }
    }
}

/**
 * Checks (without blocking) whether a client has connected to server. 
 * Returns true iff so.
 */
bool connected(void)
{
    struct sockaddr_in cli_addr;
    memset(&cli_addr, 0, sizeof(cli_addr));
    socklen_t cli_len = sizeof(cli_addr);
    /**
     * The  accept()  system call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET).  It extracts the first connection request on the
       queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor  referring  to  that
       socket.  The newly created socket is not in the listening state.  The original socket sockfd is unaffected by this call.
    */
    cfd = accept(sfd, (struct sockaddr*) &cli_addr, &cli_len);
    if (cfd == -1)
    {
        return false;
    }
    return true;
}

/**
 * Responds to client with specified status code.
 */
void error(unsigned short code)
{
    // determine code's reason-phrase
    const char* phrase = reason(code);
    if (phrase == NULL)
    {
        return;
    }

    // template for response's content
    char* template = "<html><head><title>%i %s</title></head><body><h1>%i %s</h1></body></html>";

    // render template
    char body[(strlen(template) - 2 - ((int) log10(code) + 1) - 2 + strlen(phrase)) * 2 + 1];
    int length = sprintf(body, template, code, phrase, code, phrase);
    if (length < 0)
    {
        body[0] = '\0';
        length = 0;
    }

    // respond with error
    char* headers = "Content-Type: text/html\r\n";
    respond(code, headers, body, length);
}

/**
 * Frees memory allocated by scandir.
 */
void freedir(struct dirent** namelist, int n)
{
    if (namelist != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            free(namelist[i]);
        }
        free(namelist);
    }
}
 
/**
 * Handles signals.
 */
void handler(int signal)
{
    // control-c
    if (signal == SIGINT)
    {
        signaled = true;
    }
}

/**
 * Escapes string for HTML. Returns dynamically allocated memory for escaped
 * string that must be deallocated by caller.
 */
char* htmlspecialchars(const char* s)
{
    // ensure s is not NULL
    if (s == NULL)
    {
        return NULL;
    }

    // allocate enough space for an unescaped copy of s
    char* t = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        return NULL;
    }
    t[0] = '\0';

    // iterate over characters in s, escaping as needed
    for (int i = 0, old = strlen(s), new = old; i < old; i++)
    {
        // escape &
        if (s[i] == '&')
        {
            const char* entity = "&amp;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // escape "
        else if (s[i] == '"')
        {
            const char* entity = "&quot;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // escape '
        else if (s[i] == '\'')
        {
            const char* entity = "&#039;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // escape <
        else if (s[i] == '<')
        {
            const char* entity = "&lt;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // escape >
        else if (s[i] == '>')
        {
            const char* entity = "&gt;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // don't escape
        else
        {
            strncat(t, s + i, 1);
        }
    }

    // escaped string
    return t;
}

/**
 * Checks, in order, whether index.php or index.html exists inside of path.
 * Returns path to first match if so, else NULL.
 */
char* indexes(const char* path)
{
    //path contiene el path + ...php o ...html entonces es lo que hay que verificas
    //char* documento = strrchr(path, 47);// este sería el "/index.php" o.html
    //char* directorio = strncpy(directorio, path, documento - path);// este sería el path al directory
    /**
     * ya entendí, la parte de char documento no podría existir pues cuando esta funci´n es activada significa que no hay ningún
     * documento .php o lo que sea para abrir, sino únicamente un directorio
     * imagino es para darle formato al directorio este index.php o html
     */

    char* indexphp = malloc(strlen(path) + strlen("index.php") + 1);
    strcpy(indexphp, path);
    strcat(indexphp, "index.php");
    char* indexhtml = malloc(strlen(path) + strlen("index.html") + 1);
    strcpy(indexhtml, path);
    strcat(indexhtml, "index.html");
    
    // ensure path is readable
    if (access(indexphp, R_OK) == 0)
    {
        free(indexhtml);
        return indexphp;
    }
    else if (access(indexhtml, R_OK) == 0)
    {
        free(indexphp);
        return indexhtml;
    }
    else
    {
        free(indexphp);
        free(indexhtml);
        return NULL;
    }
}

/**
 * Interprets PHP file at path using query string.
 */
void interpret(const char* path, const char* query)
{
    // ensure path is readable
    if (access(path, R_OK) == -1)
    {
        error(403);
        return;
    }

    // open pipe to PHP interpreter
    char* format = "QUERY_STRING=\"%s\" REDIRECT_STATUS=200 SCRIPT_FILENAME=\"%s\" php-cgi";
    char command[strlen(format) + (strlen(path) - 2) + (strlen(query) - 2) + 1];
    if (sprintf(command, format, query, path) < 0)
    {
        error(500);
        return;
    }
    FILE* file = popen(command, "r");
    if (file == NULL)
    {
        error(500);
        return;
    }

    // load interpreter's content
    char* content;
    size_t length;
    if (load(file, &content, &length) == false)
    {
        error(500);
        return;
    }

    // close pipe
    pclose(file);

    // subtract php-cgi's headers from content's length to get body's length
    char* haystack = content;
    char* needle = strstr(haystack, "\r\n\r\n");
    if (needle == NULL)
    {
        free(content);
        error(500);
        return;
    }

    // extract headers
    char headers[needle + 2 - haystack + 1];
    strncpy(headers, content, needle + 2 - haystack);
    headers[needle + 2 - haystack] = '\0';

    // respond with interpreter's content
    respond(200, headers, needle + 4, length - (needle - haystack + 4));

    // free interpreter's content
    free(content);
}

/**
 * Responds to client with directory listing of path.
 */
void list(const char* path)
{
    // ensure path is readable and executable
    if (access(path, R_OK | X_OK) == -1)
    {
        error(403);
        return;
    }

    // open directory
    DIR* dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }

    // buffer for list items
    char* list = malloc(1);
    list[0] = '\0';

    // iterate over directory entries
    struct dirent** namelist = NULL;
    int n = scandir(path, &namelist, NULL, alphasort);
    for (int i = 0; i < n; i++)
    {
        // omit . from list
        if (strcmp(namelist[i]->d_name, ".") == 0)
        {
            continue;
        }

        // escape entry's name
        char* name = htmlspecialchars(namelist[i]->d_name);
        if (name == NULL)
        {
            free(list);
            freedir(namelist, n);
            error(500);
            return;
        }

        // append list item to buffer
        char* template = "<li><a href=\"%s\">%s</a></li>";
        list = realloc(list, strlen(list) + strlen(template) - 2 + strlen(name) - 2 + strlen(name) + 1);
        if (list == NULL)
        {
            free(name);
            freedir(namelist, n);
            error(500);
            return;
        }
        if (sprintf(list + strlen(list), template, name, name) < 0)
        {
            free(name);
            freedir(namelist, n);
            free(list);
            error(500);
            return;
        }

        // free escaped name
        free(name);
    }

    // free memory allocated by scandir
    freedir(namelist, n);

    // prepare response
    const char* relative = path + strlen(root);
    char* template = "<html><head><title>%s</title></head><body><h1>%s</h1><ul>%s</ul></body></html>";
    char body[strlen(template) - 2 + strlen(relative) - 2 + strlen(relative) - 2 + strlen(list) + 1];
    int length = sprintf(body, template, relative, relative, list);
    if (length < 0)
    {
        free(list);
        closedir(dir);
        error(500);
        return;
    }

    // free buffer
    free(list);

    // close directory
    closedir(dir);

    // respond with list
    char* headers = "Content-Type: text/html\r\n";
    respond(200, headers, body, length);
}

/**
 * Loads a file into memory dynamically allocated on heap.
 * Stores address thereof in *content and length thereof in *length.
 */
bool load(FILE* file, BYTE** content, size_t* length)
{
    //File ya viene con información que es la que se va a cargar en la memoria
    *content = NULL;
    *length = 0;
    
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        //append each char red in content
        *content = realloc(*content, *length + sizeof(c) + 1);
        if (*content == NULL)
        {
            *length = 0;
            break;
        }
        memcpy(*content + *length, &c, 1);//copiar c a la distancia "lenght" del punetro del principio de content (un c a la vez.)
        *length += 1;
        
        // null-terminate message thus far
        *(*content + *length) = '\0';

    }
    return true;
}

/**
 * Returns MIME type for supported extensions, else NULL.
 */
const char* lookup(const char* path)
{
    char css[5] = ".css";//antes tenía los # de arrays como el # de letras, pero ya entendí que da igual al momento de comparar tener # letras + \0
    char html[6] = ".html";
    char gif[5] = ".gif";
    char ico[5] = ".ico";
    char jpg[5] = ".jpg";
    char js[4] = ".js";
    char php[5] = ".php";
    char png[5] = ".png";
    
    if (strcasecmp(strrchr(path,'.'), css) == 0)
        return "text/css";
    else if (strcasecmp(strrchr(path,'.'), html) == 0)
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

/**
 * Parses a request-line, storing its absolute-path at abs_path 
 * and its query string at query, both of which are assumed
 * to be at least of length LimitRequestLine + 1.
 */
bool parse(const char* line, char* abs_path, char* query)
{

    char* needle1 = strstr(line, " "); // el puntero que regresa es a "espacio" 
    char* needle2 = strstr(needle1 + 1, " ");//en el puntero donde queremos que empiece a
                                                //buscar es saltandose ese "espacio" para que no se quede en el mismo lugar por ello "needle1 +1"
    char* endneedle = strstr(needle2, "\r\n");//punero al final de line justo en *\r\n
    
    int meth = needle1 - line + 1;
    char method[meth];//un +1 por el "espacio" y otro +1 para el "\0"
    strncpy(method, line, needle1 - line);
    method[meth - 1] = '\0';
    //char* metodo = &method[0];
    printf("method[%i]=%s.\n", meth, method);
    
    int req = needle2 - needle1;
    char request_target[req];
    strncpy(request_target, needle1 + 1, needle2 - needle1 - 1);//+1 para que se salte el espacio y -1 para que no cuente el espacio
    request_target[req - 1] = '\0';
    //char* pedir = &request_target[0];
    printf("request_target[%i]=%s.\n", req, request_target);
    
    int ver = endneedle - needle2;//no es más uno porque para el '\0' ya se puede considerar contado por el espacio que cuenta al marcar needle2 un espacio
    char HTTP_version[ver];
    strncpy(HTTP_version, needle2 + 1, endneedle - needle2 - 1);
    HTTP_version[ver - 1] = '\0';
    printf("HTTP_version[%i]=%s.\n", ver, HTTP_version);

    // Primero , whereby absolute-path (which will not contain ?)
    //must start with / and might optionally be followed by a ? followed by a query, which may not contain ".
    //(estas reglas ya están tomadas en cuenta en los puntos inmediaos de abajo)
    //Even if request-line is consistent with these rules,
    //if method is not GET, respond to the browser with 405 Method Not Allowed and return false;
    if ((strncmp(method, "GET", meth - 1)) != 0)// el - 1 es para que no compare el último char ue es '\0'
    {
        error(405);
        return false;
    }
    //if request-target does not begin with /, respond to the browser with 501 Not Implemented and return false;
    if ((strncmp(request_target, "/", 1)) != 0)
    {
        error(501);
        return false;
    }
    //if request-target contains a ", respond to the browser with 400 Bad Request and return false;
    if ((strchr(request_target, 34)) != NULL)
    {
        error(400);
        return false;
    }
    //if HTTP-version is not HTTP/1.1, respond to the browser with 505 HTTP Version Not Supported and return false; or
    if ((strncmp(HTTP_version, "HTTP/1.1", req - 1)) != 0)
    {
        error(505);
        return false;
    }
    
    //depués para comprobar con valgrind si senecesitaban
    //free(needle1);
    //free(needle2);
    //free(endneedle);
    
    //absolute_path and query
    char* point_query = strstr(request_target, "?");
    //char* end_req = strstr(request_target, ""); !! no necesitamos este puntero pues en realidad ya conocemos el largo de request_target
    int largo_query = 0;
    
    if(point_query != NULL)
    {
        largo_query = strlen(request_target) - (point_query - request_target) - 1;// para entender si sólo es un "?" o hay más después
        // el -1 es para quitar el espacio que tomaría "?"
    }

    //ver si en realidad está el inicio de query
    if (point_query == NULL)
    {
        //si no, pues sólo se asigna "" o '\0' a query y absolute path es todo el request_target
        char poss_query[1] = {'\0'};
        strcpy(query, poss_query);
        strcpy(abs_path, request_target);
    }
    //else if ((strncmp(point_query, "?", 2)) != 0)
    else if (largo_query == 1)
    {
        //si existe una parte de query, sólo el signo de pregunta, entonces, igual para query, se asigna "" o '\0' y absolute path se le quita el "?"
        char absolute_path[point_query - request_target + 1]; 
        strncpy(absolute_path, request_target, point_query - request_target);
        absolute_path[point_query - request_target] = '\0';
        //abs_path = absolute_path;
        strcpy(abs_path, absolute_path);
        char poss_query[1] = {'\0'};
        //query = poss_query;
        strcpy(query, poss_query);
    }
    else
    {
        //signigica que existe un query, entonces sólo hay que hacer la diferenciación
        char absolute_path[point_query - request_target + 1]; 
        strncpy(absolute_path, request_target, point_query - request_target);
        absolute_path[point_query - request_target] = '\0';
        //abs_path = absolute_path;
        strcpy(abs_path, absolute_path);
        char poss_query[req - (point_query - request_target) - 1];// el pointers arithemtic es el largo de query contando '\0' y el - 1 porque no contamos el "?"
        strncpy(poss_query, point_query + 1, req - (point_query - request_target) - 1);// el + 1 es para saltarse el "?" pues no debe de ser tomado en cuenta
                                                                                //y el - 1 para no contar más allá del '\0'
        //poss_query[end_req - point_query] = '\0';
        //query = poss_query;
        strcpy(query, poss_query);
    }
    
    return true;
}

/**
 * Returns status code's reason phrase.
 *
 * http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6
 * https://tools.ietf.org/html/rfc2324
 */
const char* reason(unsigned short code)
{
    switch (code)
    {
        case 200: return "OK";
        case 301: return "Moved Permanently";
        case 400: return "Bad Request";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 414: return "Request-URI Too Long";
        case 418: return "I'm a teapot";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 505: return "HTTP Version Not Supported";
        default: return NULL;
    }
}

/**
 * Redirects client to uri.
 */
void redirect(const char* uri)
{
    char* template = "Location: %s\r\n";
    char headers[strlen(template) - 2 + strlen(uri) + 1];
    if (sprintf(headers, template, uri) < 0)
    {
        error(500);
        return;
    }
    respond(301, headers, NULL, 0);
}

/**
 * Reads (without blocking) an HTTP request's headers into memory dynamically allocated on heap.
 * Stores address thereof in *message and length thereof in *length.
 */
 // Tenemos     char* message = NULL;
 //             size_t length = 0; 
 //             y en main ---> request(&message, &length)
 // entonces por main los valores que pasan es un pointer (la dirección) del pointer "message"
 // y el pointer (la dirección) del size_t (= unsigned int) 
 // por ello char ** que es a dirección de la dirección ( o level 2 pointer) y size_t* que es la dirección del valor 
bool request(char** message, size_t* length)
{
    // ensure socket is open
    if (cfd == -1)// es un socket que se estudia en la función connected
    {
        return false;
    }

    // initialize message and its length
    *message = NULL;
    *length = 0;

    /**
     *  #define LimitRequestFields 50
        #define LimitRequestFieldSize 4094
        #define LimitRequestLine 8190
     */
    // read message 
    while (*length < LimitRequestLine + LimitRequestFields * LimitRequestFieldSize + 4)
    {
        /**
         *  typedef char BYTE;
            #define BYTES 512
         */

        // read from socket
        BYTE buffer[BYTES];
        ssize_t bytes = read(cfd, buffer, BYTES);
        /**
         * int  read(  int  handle,  void  *buffer,  int  nbyte );
         * The read() function attempts to read nbytes from the file associated with handle, and places the characters read into buffer.
         * 
         * read() regresa el número de bytes leídos
         *  el siguiente if se enfoca a aestidiar si read() saca un error pues si es así marca -1
         * y ahí es donde termina de analizar pues algo está mal
         */
        if (bytes < 0)
        {
            if (*message != NULL)
            {
                free(*message);
                *message = NULL;
            }
            *length = 0;
            break;
        }

        // append bytes to message 
        /**
         *  void *realloc(void *ptr, size_t size)
         * resize de memory block
         * 
         * ptr -- This is the pointer to a memory block previously allocated
         * with malloc, calloc or realloc to be reallocated. If this is NULL, 
         * a new block is allocated and a pointer to it is returned by the function.
         */
        *message = realloc(*message, *length + bytes + 1);
        if (*message == NULL)// para ver si existe un error, pues realloc() regresa NULL si el size es 0 
        {
            *length = 0;
            break;
        }
        /**
         * void *memcpy(void *str1, const void *str2, size_t n)
         * str1 -- This is pointer to the destination array where the content is to be copied, type-casted to a pointer of type void*.
         * str2 -- This is pointer to the source of data to be copied, type-casted to a pointer of type void*.
         * n -- This is the number of bytes to be copied.
         */
        memcpy(*message + *length, buffer, bytes);  //*message + *lenght = digamos que el pointer que está al principio de message pues apunta a *message
                                                    // se mueve del valor de lenght apuntando a digamos 0 (donde apunta *message) + lenght y ahí trabaja
                                                    // en este caso, copia "buffer"  en esa parte, del tamaño size
        *length += bytes;// a lenght se le suman bytes para siguiente conteo

        // null-terminate message thus far
        *(*message + *length) = '\0';   // sería el valor en el pointer del pointer message + el valor en el ppointer de lenght
        /**
         * ver un poco en función "1point", también se puede jugar con diferentes tipos para cuando se avance en la dirección donde está el pointer
         * se avance de 1 en 1 byte (char) o de 4 en 4 bytes (int) .. etc
         */        

        // search for CRLF CRLF
        int offset = (*length - bytes < 3) ? *length - bytes : 3;
        char* haystack = *message + *length - bytes - offset;// pointer
        char* needle = strstr(haystack, "\r\n\r\n");// pointer a donde encuentra \r\n\r\n en haystack
        if (needle != NULL)
        {
            // trim to one CRLF and null-terminate
            *length = needle - *message + 2;//Subtracting two pointers gives a logically explainable result - the offset in memory between two pointers
            *message = realloc(*message, *length + 1);
            if (*message == NULL)
            {
                break;
            }
            *(*message + *length) = '\0';

            // ensure request-line is no longer than LimitRequestLine
            haystack = *message;
            needle = strstr(haystack, "\r\n");
            if (needle == NULL || (needle - haystack + 2) > LimitRequestLine)
            {
                break;
            }

            // count fields in message
            int fields = 0;
            haystack = needle + 2;
            while (*haystack != '\0')
            {
                // look for CRLF
                needle = strstr(haystack, "\r\n");
                if (needle == NULL)
                {
                    break;
                }

                // ensure field is no longer than LimitRequestFieldSize
                if (needle - haystack + 2 > LimitRequestFieldSize)
                {
                    break;
                }

                // look beyond CRLF
                haystack = needle + 2;
            }

            // if we didn't get to end of message, we must have erred
            if (*haystack != '\0')
            {
                break;
            }

            // ensure message has no more than LimitRequestFields
            if (fields > LimitRequestFields)
            {
                break;
            }

            // valid
            return true;
        }
    }

    // invalid
    if (*message != NULL)
    {
        free(*message);
    }
    *message = NULL;
    *length = 0;
    return false;
}

/**
 * Responds to a client with status code, headers, and body of specified length.
 */
void respond(int code, const char* headers, const char* body, size_t length)
{
    // determine Status-Line's phrase
    // http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6.1
    const char* phrase = reason(code);
    if (phrase == NULL)
    {
        return;
    }

    // respond with Status-Line
    if (dprintf(cfd, "HTTP/1.1 %i %s\r\n", code, phrase) < 0)
    {
        return;
    }

    // respond with headers
    if (dprintf(cfd, "%s", headers) < 0)
    {
        return;
    }

    // respond with CRLF
    if (dprintf(cfd, "\r\n") < 0)
    {
        return;
    }

    // respond with body
    if (write(cfd, body, length) == -1)
    {
        return;
    }

    // log response line
    if (code == 200)
    {
        // green
        printf("\033[32m");
    }
    else
    {
        // red
        printf("\033[33m");
    }
    printf("HTTP/1.1 %i %s", code, phrase);
    printf("\033[39m\n");
}

/**
 * Starts server on specified port rooted at path.
 */
void start(short port, const char* path)
{
    // path to server's root
    root = realpath(path, NULL);
    if (root == NULL)
    {
        stop();
    }

    // ensure root is executable
    if (access(root, X_OK) == -1)
    {
        stop();
    }

    // announce root
    printf("\033[33m");
    printf("Using %s for server's root", root);
    printf("\033[39m\n");

    // create a socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        stop();
    }

    // allow reuse of address (to avoid "Address already in use")
    int optval = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // assign name to socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("\033[33m");
        printf("Port %i already in use", port);
        printf("\033[39m\n");
        stop();
    }

    // listen for connections
    if (listen(sfd, SOMAXCONN) == -1)
    {
        stop();
    }

    // announce port in use
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    if (getsockname(sfd, (struct sockaddr*) &addr, &addrlen) == -1)
    {
        stop();
    }
    printf("\033[33m");
    printf("Listening on port %i", ntohs(addr.sin_port));
    printf("\033[39m\n");
}

/**
 * Stop server, deallocating any resources.
 */
void stop(void)
{
    // preserve errno across this function's library calls
    int errsv = errno;

    // announce stop
    printf("\033[33m");
    printf("Stopping server\n");
    printf("\033[39m");

    // free root, which was allocated by realpath
    if (root != NULL)
    {
        free(root);
    }

    // close server socket
    if (sfd != -1)
    {
        close(sfd);
    }

    // stop server
    exit(errsv);
}

/**
 * Transfers file at path with specified type to client.
 */
void transfer(const char* path, const char* type)
{
    // ensure path is readable
    if (access(path, R_OK) == -1)
    {
        error(403);
        return;
    }

    // open file
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        error(500);
        return;
    }

    // load file's content
    BYTE* content;
    size_t length;
    if (load(file, &content, &length) == false)
    {
        error(500);
        return;
    }

    // close file
    fclose(file);

    // prepare response
    char* template = "Content-Type: %s\r\n";
    char headers[strlen(template) - 2 + strlen(type) + 1];
    if (sprintf(headers, template, type) < 0)
    {
        error(500);
        return;
    }

    // respond with file's content
    respond(200, headers, content, length);

    // free file's content
    free(content);
}

/**
 * URL-decodes string, returning dynamically allocated memory for decoded string
 * that must be deallocated by caller.
 */
char* urldecode(const char* s)
{
    // check whether s is NULL
    if (s == NULL)
    {
        return NULL;
    }

    // allocate enough (zeroed) memory for an undecoded copy of s
    char* t = calloc(strlen(s) + 1, 1);
    if (t == NULL)
    {
        return NULL;
    }
    
    // iterate over characters in s, decoding percent-encoded octets, per
    // https://www.ietf.org/rfc/rfc3986.txt
    for (int i = 0, j = 0, n = strlen(s); i < n; i++, j++)
    {
        if (s[i] == '%' && i < n - 2)
        {
            char octet[3];
            octet[0] = s[i + 1];
            octet[1] = s[i + 2];
            octet[2] = '\0';
            t[j] = (char) strtol(octet, NULL, 16);
            i += 2;
        }
        else if (s[i] == '+')
        {
            t[j] = ' ';
        }
        else
        {
            t[j] = s[i];
        }
    }

    // escaped string
    return t;
}
