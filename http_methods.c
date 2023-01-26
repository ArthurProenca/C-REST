#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rest_operations.h"

const int PORT = 443;

SSL_CTX *get_ssl_context()
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX *ssl_ctx = SSL_CTX_new(TLSv1_2_client_method());
    if (!ssl_ctx)
    {
        printf("Error creating SSL context\n");
        return NULL;
    }
    return ssl_ctx;
}

BIO *get_bio(SSL_CTX *ssl_ctx)
{
    SSL *ssl;
    BIO *bio;

    bio = BIO_new_ssl_connect(ssl_ctx);
    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    return bio;
}

void make_get_request(char *host, char *path, char *headers)
{
    SSL_CTX *ssl_ctx = get_ssl_context();
    BIO *bio = get_bio(ssl_ctx);

    char hostname[256];
    snprintf(hostname, sizeof(hostname), "%s:%d", host, PORT);
    BIO_set_conn_hostname(bio, hostname);

    if (BIO_do_connect(bio) <= 0)
    {
        printf("Error connecting to server\n");
        return;
    }

    char request[512];
    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host);
    BIO_write(bio, request, strlen(request));

    char response[4096];
    int response_size = BIO_read(bio, response, sizeof(response));
    if (response_size < 0)
    {
        printf("Error reading response\n");
        return;
    }

    printf("%.*s\n", response_size, response);
    BIO_free_all(bio);
    SSL_CTX_free(ssl_ctx);
}

void make_post_request(const char *path, const char *body, char *host, char *headers)
{
    SSL_CTX *ssl_ctx = get_ssl_context();
    BIO *bio = get_bio(ssl_ctx);

    char hostname[256];
    snprintf(hostname, sizeof(hostname), "%s:%d", host, PORT);
    BIO_set_conn_hostname(bio, hostname);

    if (BIO_do_connect(bio) <= 0)
    {
        printf("Error connecting to server\n");
        return;
    }

    char request[2048];
    int request_len = snprintf(request, sizeof(request),
                               "POST %s HTTP/1.1\r\n"
                               "Host: %s\r\n"
                               "Content-Type: application/json\r\n"
                               "Content-Length: %ld\r\n"
                               "%s \r\n"
                               "\r\n"
                               "%s",
                               path, host, strlen(body), headers, body);

    BIO_write(bio, request, request_len);

    char response[4096];
    int response_size = BIO_read(bio, response, sizeof(response));
    if (response_size < 0)
    {
        printf("Error reading response\n");
        return;
    }

    printf("%.*s\n", response_size, response);
    BIO_free_all(bio);
    SSL_CTX_free(ssl_ctx);
}

void make_put_request(const char *path, const char *body, char *host, char *headers)
{
    SSL_CTX *ssl_ctx = get_ssl_context();
    BIO *bio = get_bio(ssl_ctx);

    char hostname[256];
    snprintf(hostname, sizeof(hostname), "%s:%d", host, PORT);
    BIO_set_conn_hostname(bio, hostname);

    if (BIO_do_connect(bio) <= 0)
    {
        printf("Error connecting to server\n");
        return;
    }

    char request[2048];
    int request_len = snprintf(request, sizeof(request),
                               "PUT %s HTTP/1.1\r\n"
                               "Host: %s\r\n"
                               "Content-Type: application/json\r\n"
                               "Content-Length: %ld\r\n"
                               "\r\n"
                               "%s",
                               path, host, strlen(body), body);

    BIO_write(bio, request, request_len);

    char response[4096];
    int response_size = BIO_read(bio, response, sizeof(response));
    if (response_size < 0)
    {
        printf("Error reading response\n");
        return;
    }

    printf("%.*s\n", response_size, response);
    BIO_free_all(bio);
    SSL_CTX_free(ssl_ctx);
}

void make_delete_request(const char *path, const char *body, char *host, char *headers)
{
    SSL_CTX *ssl_ctx = get_ssl_context();
    BIO *bio = get_bio(ssl_ctx);
    
    char hostname[256];
    snprintf(hostname, sizeof(hostname), "%s:%d", host, PORT);
    BIO_set_conn_hostname(bio, hostname);

    if (BIO_do_connect(bio) <= 0)
    {
        printf("Error connecting to server\n");
        return;
    }

    char request[2048];

    int request_len = 0;
    if (body == NULL)
    {
        request_len = snprintf(request, sizeof(request),
                               "DELETE %s HTTP/1.1\r\n"
                               "Host: %s\r\n"
                               "\r\n"
                               "%s",
                               path, host, body);
    }
    else
    {
        request_len = snprintf(request, sizeof(request),
                               "DELETE %s HTTP/1.1\r\n"
                               "Host: %s\r\n"
                               "Content-Type: application/json\r\n"
                               "Content-Length: %ld\r\n"
                               "\r\n"
                               "%s",
                               path, host, strlen(body), body);
    }

    BIO_write(bio, request, request_len);

    char response[4096];
    int response_size = BIO_read(bio, response, sizeof(response));
    if (response_size < 0)
    {
        printf("Error reading response\n");
        return;
    }

    printf("%.*s\n", response_size, response);
    BIO_free_all(bio);
    SSL_CTX_free(ssl_ctx);
}