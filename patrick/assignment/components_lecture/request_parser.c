#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define GET_ROOT "GET / HTTP/1.1"
#define GET_INFO "GET /info HTTP/1.1"
#define POST_INFO "POST /info HTTP/1.1"
#define GET_RESPONSE_TAIL "\r\n\r\n"
#define HEADER_BODY_SEPARATOR "\n\n"
#define HTTP_HEADER "HTTP/1.1 200 OK"

#define GET_RESPONSE_BODY "<html><head></head><body>Welcome to Jake, Antonio Patrick's AWESOME Page</body></html>"
#define GET_RESPONSE HTTP_HEADER HEADER_BODY_SEPARATOR GET_RESPONSE_BODY

#define GET_INFO_BODY "{\"info\": {\"name\":\"Jake, Antonio & Patrick\", \"url_request\": \"/info\", \"last_message\": \":::undefined::: OR :::POST message:::\"}}"
#define GET_INFO_RESPONSE HTTP_HEADER HEADER_BODY_SEPARATOR GET_INFO_BODY

#define POST_INFO_BODY "Thanks for posting that!"
#define POST_INFO_RESPONSE HTTP_HEADER HEADER_BODY_SEPARATOR POST_INFO_BODY

#define NOT_FOUND_HEADER "HTTP/1.1 404 Not Found"
#define NOT_FOUND_BODY "That route isn't supported!!!"
#define NOT_FOUND NOT_FOUND_HEADER HEADER_BODY_SEPARATOR NOT_FOUND_BODY

#define CONTENT_LENGTH "Content-Length: "
#define CONTENT_LENGTH_HEADER_LENGTH 16

/******************************************************************************
 * parse_client_request takes a single HTTP request as a STRING
 * and PROCESSES it.
 * NOTE: The 'request' char* could contain binary data, which we
 * are not handling. If it did get binary data, it would crash (or worse).
 * TODO: handle Chrome request for /favicon.ico BINARY data
 * TODO: refactor time() into a helper function? Possibly a time.c and time.h file?
 ******************************************************************************/

char* parse_client_request(const char* request, int size) {
    printf("Parsing data of size: %d\n", size);
    printf("Client opened socket and sent: \n\n%s\n", request);
    // int double_newline = memchr(buffer, "\n", 1024);
    // printf("read_result: %d\n", double_newline);

// LS: parse the input and determine what result to send

/******************************************************************************
 * HEADER INFO TO SEND:
 * HTTP/1.1 200 OK                              <~~~ bare minimum header
 * Date: xxxx (formatted time or Unix time)
 * Server: Name of Student
 * Content-Length: yy                           <~~~ Pointer Arithmetic!!!!!
 * Connection: close
 * Content-Type: text/html                      <~~~ GET / vs GET /info (JSON)
 ******************************************************************************/


// 1: must handle GET /
// look for 'GET/' inside request
    char* find_GET = strnstr(request, GET_ROOT, size);
    if (find_GET != NULL) {
        puts("I found GET!");
        /* UNIX TIME AND LOCAL TIME */
        time_t the_time = time(NULL);
        printf("The current UNIX time: %ld\n", the_time);
        struct tm * ptr_time;
        time(&the_time);
        ptr_time = localtime(&the_time);
        printf ("Current local date and time: %s\n", asctime(ptr_time));

        return GET_RESPONSE;
    }
/******************************************************************************
 * BODY DATA TO SEND:
 * Content-Type: text/html
 * <html><head></head><body>Welcome to :::students' names:::</body></html>
 ******************************************************************************/

// 2: must handle GET /info
// look for 'GET/info' inside request
    char* find_GET_info = strnstr(request, GET_INFO, size);
    if (find_GET_info != NULL) {
        puts("I found GET /info!");
        /* UNIX TIME AND LOCAL TIME */
        time_t the_time = time(NULL);
        printf("The current UNIX time: %ld\n", the_time);
        struct tm * ptr_time;
        time(&the_time);
        ptr_time = localtime(&the_time);
        printf ("Current local date and time: %s\n", asctime(ptr_time));

        // TODO: SPECIFY JSON CONTENT TYPE

        return GET_INFO_RESPONSE;
    }
/******************************************************************************
 * BODY DATA TO SEND:
 * Content-Type: application/json
 * {"info": {"name":":::student name:::", "url_request": "/info", "last_message": ":::undefined::: OR :::POST message:::"}}
 ******************************************************************************/


// 3: must handle POST /info
    char* find_POST = strnstr(request, POST_INFO, size);
    if (find_POST != NULL) {
        puts("I found POST /info!");
        /* UNIX TIME AND LOCAL TIME */
        time_t the_time = time(NULL);
        printf("The current UNIX time: %ld\n", the_time);
        struct tm * ptr_time;
        time(&the_time);
        ptr_time = localtime(&the_time);
        printf ("Current local date and time: %s\n", asctime(ptr_time));

        // char* find_Content_Length = strnstr(request, CONTENT_LENGTH, size);
        // char* find_len_cont_len = strnstr(find_Content_Length, "\n", size-strlen(find_Content_Length));
        // // puts("Did we find Content-Length: here?");
        // // printf("%s\n", find_Content_Length);
        // // printf("%s\n", find_len_cont_len);
        // // puts("Did we find next line here?");
        // // printf("%p\n", find_Content_Length);
        // // printf("%p\n", find_len_cont_len);
        //
        // int len_con_len_line = find_len_cont_len - find_Content_Length-1;
        // char len_str[1024];
        // strncpy(len_str, find_Content_Length + CONTENT_LENGTH_HEADER_LENGTH, len_con_len_line - CONTENT_LENGTH_HEADER_LENGTH);
        // int body_length = atoi(len_str);
        // // printf("Content Length? %d\n", body_length);
        // // printf("Difference between two pointers: %ld\n", find_len_cont_len - find_Content_Length);
        //
        // char* body = strnstr(request, HEADER_BODY_SEPARATOR, size);
        // printf("BODY! %s\n", body);
        //
        // char the_body[1024];
        // memset(the_body, 0, sizeof(the_body));
        // strncpy(the_body, body+4, body_length);
        // printf("THE BODY: %s\n", the_body);

        return POST_INFO_RESPONSE;
    }

    return NOT_FOUND;
}
