/*

gen_test.c

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

    // Call functions 1000 times and assert max score.
    for (int i = 0; i < 1000; i++) {
        password_generator(password, length, true, true, true, true);
        score = password_strength_check(password, length);
        printf("Loop no. %d, Score: %d, Password: %s\n", i + 1, score, password);
        assert(score == 100);       
    }

    printf("Test successful!\n");

    return 0;
}
