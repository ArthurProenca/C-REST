#define CREATOR "# CREATOR: HTTP Methods [GET, POST, PUT, DELETE] using C-Ansi and OpenSSL - ArthurProenca\n"

#include <openssl/ssl.h>
#include <openssl/err.h>

enum
{
    GET,
    POST,
    PUT,
    DELETE
};

void make_get_request(char *host, char *path, char *headers);
void make_post_request(const char *path, const char *body, char *host, char *headers);
void make_put_request(const char *path, const char *body, char *host, char *headers);
void make_delete_request(const char *path, const char *body, char *host, char *headers);
SSL_CTX *get_ssl_context();
BIO *get_bio(SSL_CTX *ssl_ctx);