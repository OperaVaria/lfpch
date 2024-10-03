/*

requests.c

Functions related to HTTP requests.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <curl/curl.h>
#include "requests.h"

/* Initiate a cURL session with the "easy" API, get a response and
store the data to a dynamically allocated char array. */

int curl_session(char *url) {

    // Declare cURL variables.
    CURL *curl;
    CURLcode res;

    // Init session + error handling.
    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "HTTP request failed\n");
        return -1;
    }
    
    // cURL setup.
    curl_easy_setopt(curl, CURLOPT_URL, url);
    
    // Perform request + error handling.
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
        return -1;
    }

    putchar('\n');

    // Close session.
    curl_easy_cleanup(curl);

    return 0;
}