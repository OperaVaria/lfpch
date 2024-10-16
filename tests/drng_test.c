/*

drng_test.c

Test if the RDSEED instruction is available and working correctly.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <assert.h>
#include <immintrin.h>
#include <stdio.h>

int main() {

    // Declare variables.
    int status;
    unsigned int result;
    
    // Call instruction and assert. Success = 1, Fail = 0.
    status = _rdseed32_step(&result);
    assert(status == 1);

    printf("Test successful! Generated number: %u\n", result);

    return 0;
}
