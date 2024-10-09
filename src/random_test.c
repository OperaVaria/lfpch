#include <curl/curl.h>
#include "types.h"

int main(int argc, char const *argv[])
{
    // Build request url.
    char url[] = "https://www.random.org/integers/?num=10&min=1&max=6&col=10&base=10&format=plain&rnd=new";

    // Create Memory struct instance to store response chunks.
    Memory memory;
    memory.string = malloc(1);
    memory.size = 0;

    // Call cURL session function with error handling.
    int curl_response = curl_session(url, &memory,) != 0;
    if (curl_response != 0) {
        fprintf(stderr, "cURL error, code: %d, exiting app.\n", curl_response);
        exit(EXIT_FAILURE);
    }
    


    return 0;
}
