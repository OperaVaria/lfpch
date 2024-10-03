/*

requests.c

Functions related to HTTP requests.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "requests.h"

// Static callback function prototype.
static size_t write_chunk_cb(char *data, size_t size, size_t nmemb, void *clientp);

/* Initiate a cURL session with the "easy" API, get a response and
store the data to a dynamically allocated char array. Takes a url string
and a Memory struct as argument, returns status code.*/
int curl_session(char *url, Memory *struct_ptr) {

    // Declare cURL variables.
    CURL *curl;
    CURLcode res;

    // Init session + error handling.
    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "HTTP request failed\n");
        return -1;
    }
    
    // Session options.
    curl_easy_setopt(curl, CURLOPT_URL, url); // Pass URL.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_chunk_cb); // Set callback function.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)struct_ptr); // Pass chunks to cb function.
    
    // Perform request + error handling.
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
        return -1;
    }   
    
    // Close session.
    curl_easy_cleanup(curl);

    return 0;
}

/* Callback function for cURL to store response data, chunk-by-chunk,
to dynamically allocated memory. Returns the number of elements (nmemb) received. */
static size_t write_chunk_cb(char *data, size_t size, size_t nmemb, void *clientp) {

    // Initialize variables.
    size_t real_size = size * nmemb;
    Memory *mem = (Memory *)clientp;

    // Reallocate memory + error handling
    char *ptr = realloc(mem->res_str, mem->size + real_size + 1);
    if (ptr == NULL) {
        return CURL_WRITEFUNC_ERROR;
    }

    // Update Memory instance.
    mem->res_str = ptr;
    memcpy(&(mem->res_str[mem->size]), data, real_size);
    mem->size += real_size;
    mem->res_str[mem->size] = '\0';

    return nmemb;
}