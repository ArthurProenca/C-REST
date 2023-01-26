#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rest_operations.h"

void check_args(int argc, char *argv[], int optional_headers, int optional_body)
{
    if (argc < 5)
    {
        printf("Usage: %s [METHOD] [HOST] [PATH] [BODY] [HEADERS], where headers and body are optional (use '-' to blank) \n"
               "\nExample: GET viacep.com.br /ws/37975000/json -"
               "\nExample: POST localhost:8080 /api/v1/create {\"user\": \"Lorem Ipsum\"}\n",
               argv[0]);
        return;
    }

    if (strcmp(argv[1], "GET") == 0)
    {
        optional_headers == 1 ? make_get_request(argv[2], argv[3], "") : make_get_request(argv[2], argv[3], argv[5]);
    }
    else if (strcmp(argv[1], "POST") == 0)
    {
        argv[3] = optional_body == 1 ? "" : argv[3];
        optional_headers == 1 ? make_post_request(argv[2], argv[3], argv[4], "") : make_post_request(argv[2], argv[3], argv[4], argv[5]);
    }
    else if (strcmp(argv[1], "PUT") == 0)
    {
        argv[3] = optional_body == 1 ? "" : argv[3];
        optional_headers == 1 ? make_put_request(argv[2], argv[3], argv[4], "") : make_post_request(argv[2], argv[3], argv[4], argv[5]);
    }
    else if (strcmp(argv[1], "DELETE") == 0)
    {
        argv[3] = optional_body == 1 ? "" : argv[3];
        optional_headers == 1 ? make_delete_request(argv[2], argv[3], argv[4], "") : make_post_request(argv[2], argv[3], argv[4], argv[5]);
    }
    else
    {
        printf("Invalid method: %s", argv[1]);
    }
}

int main(int argc, char *argv[])
{
    check_args(argc, argv, argv[5] == "-", argv[4] == "-");
    return 0;
}
