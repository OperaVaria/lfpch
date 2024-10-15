/*

generator_test.c

Test if the password generator consistently generates maximum score passwords.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <assert.h>
#include "checker.h"
#include "generator.h"

int main() {

    // Declare variables.
    char password[17];
    size_t length = 16;
    int score;

    // Call functions 100 times and assert max score.
    for(int i = 1; i == 100; i++) {
        password_generator(password, length, true, true, true, true);
        score = password_strength_check(password, length);
        assert(score == 100);
        printf("Loop no. %d successful.\n", i);
    }

    printf("Test successful!\n");

    return 0;
}