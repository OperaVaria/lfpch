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

// Static cURL callback function prototype.
static size_t write_chunk_cb(char *data, size_t size, size_t nmemb, void *clientp);

/* Initiate a cURL session with the "easy" API. Get a response and
store the data to a dynamically allocated char array. Takes a url string
and a Memory struct as argument. Returns status code.*/
int curl_session(const char *url, Memory *struct_ptr) {

    // Declare cURL variables.
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;

    // Init session + error handling.
    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "HTTP request failed\n");
        return -1;
    }
    
    // Set headers.
    headers = curl_slist_append(headers, "Add-Padding: true"); /*  Add padding to the haveibeenpwned.com
                                                                for more obfuscation. */        
    // Session options.
    curl_easy_setopt(curl, CURLOPT_URL, url); // Pass URL.
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Pass headers.  
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)struct_ptr); // Pass chunks to cb function.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);  // Set timeout of 10 seconds.
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);  // Connection timeout of 5 seconds.
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);  // Fail if HTTP code >= 400.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_chunk_cb); // Set callback function.
    // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // For debugging.
    
    // Perform request + error handling.
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
        return -1;
    }   
    
    // Close session.
    curl_easy_cleanup(curl);

    // Free custom headers.
    curl_slist_free_all(headers);

    return 0;
}

/* Callback function for cURL to store response data, chunk-by-chunk,
to dynamically allocated memory. Returns the number of elements (nmemb) received. */
static size_t write_chunk_cb(char *data, size_t size, size_t nmemb, void *clientp) {

    // Initialize variables.
    size_t real_size = size * nmemb;
    Memory *mem = (Memory *)clientp;

    // Reallocate memory + error handling
    char *ptr = realloc(mem->string, mem->size + real_size + 1);
    if (ptr == NULL) {
        free(mem->string);
        return CURL_WRITEFUNC_ERROR;
    }

    // Update Memory instance.
    mem->string = ptr;
    memcpy(&(mem->string[mem->size]), data, real_size);
    mem->size += real_size;
    mem->string[mem->size] = '\0';

    return nmemb;
}