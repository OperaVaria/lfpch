/*

conn_test.c

Test if a connection with the haveibeenpwned.com servers can be established properly.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <assert.h>
#include "request.h"

int main() {

    // Declare variables.
    char url[] = "https://api.pwnedpasswords.com/range/00000";
    char header_data[] = "Add-Padding: true";
    int curl_response;

    // Create Memory struct instance to store response chunks.
    Memory memory;
    memory.string = malloc(1);
    memory.size = 0;

    // Call cURL session, check response code.
    curl_response = curl_session(url, header_data, &memory);
    if (curl_response != 0) {
        fprintf(stderr, "cURL error, code: %d.\n", curl_response);
    }
    assert(curl_response == 0);

    printf("Test successful!");

    return 0;
}
