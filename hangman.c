// Jivaj Brar hangman.c

// includes
#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *__asan_default_options(void) {
    return "detect_leaks=0";
}

//main
int main(int argc, char **argv) {
    //input error: incorrect amount of arguments

    if (argc != 2) {
        fprintf(stderr, "wrong number of arguments\n");
        exit(1);
    }

    //input error: too long
    if ((int) strlen(argv[1]) > MAX_LENGTH) {
        printf("the secret phrase is over 256 characters\n");
        exit(1);
    }

    //initalize variables
    int correctguesses = 0, lives_used = 0, guesscount = 0;
    //array for lives
    char eliminated[8] = { ' ' };
    char guessinguesses[27] = { ' ' };
    //copies the message into secret
    char *secret = argv[1];

    bool p_input[strlen(argv[1])];
    for (int j = 0; j < (int) sizeof(p_input); j++) {

        if (string_contains_character(punctuation, secret[j]) == true) {
            p_input[j] = true;
        } else {
            p_input[j] = false;
        } //false statement
    }

    //if validate secret comes back false prints error message
    if (validate_secret(secret) != true) {
        char notc = ' ';
        for (int c = 0; c < (int) strlen(secret); c++) {
            if (string_contains_character(punctuation, secret[c]) != true
                && is_lowercase_letter(secret[c]) != true) {
                notc = secret[c]; //set notc as the invalid character
                //printf("BROKE HERE: %c", notc);
                break; //breaks loops and prints error statement
            }
        }
        printf("invalid character: '%c'\nthe secret phrase must contain only lowercase letters, "
               "spaces, hyphens, and apostrophes\n",
            notc);
        exit(1);
    }

    int secret_clean = (int) strlen(secret);

    for (int i = 0; i < (int) strlen(secret); i++) {
        if (secret[i] == ' ' || secret[i] == '\'' || secret[i] == '-') {
            secret_clean = secret_clean - 1;
        }
    }

    int rcount = 0;
    bool gamedone = true;

    do {

        printf(CLEAR_SCREEN); //clears screen
        //prints secret hidden
        printf("%s\n\n", arts[lives_used]);
        printf("    Phrase: ");
        for (int j = 0; j < (int) sizeof(p_input); j++) {
            //revealed letters
            if (p_input[j] == true) {
                printf("%c", secret[j]);
            }
            //hidden letters
            else {
                printf("_");
            }
        }
        // alphabitizes characters
        char temp;
        for (int i = 0; i < (int) strlen(eliminated); i++) {
            for (int j = i + 1; j < (int) strlen(eliminated); j++) {
                if ((int) eliminated[i] > (int) eliminated[j]) {
                    temp = eliminated[i];
                    eliminated[i] = eliminated[j];
                    eliminated[j] = temp;
                }
            }
        }
        //eliminated characters
        if (eliminated[0] != ' ') {
            printf("\nEliminated: %s\n\n", eliminated);
        } else {
            printf("\nEliminated:%s\n\n", eliminated);
        }

        //guess
        char guess;
        bool done = false;
        char rtemp;
        while (done == false) {
            printf("Guess a letter: ");

            if (rcount == 0) {
                guess = read_letter();
                rcount = 1;
            } else {
                rtemp = read_letter(); //temp value
                //(rtemp) is valid so it becomes the guess
                if ((is_lowercase_letter(rtemp) == true)) {
                    guess = rtemp;
                }
                //if the guess(rtemp) a space pushes it still
                else if (rtemp == ' ') {
                    guess = rtemp;
                }
                //if rtemp doesnt fit any of the criteria it just runs the next letter with read_letter
                else if (rtemp != '\0' && rtemp != '\n') {
                    guess = rtemp;
                } else {
                    guess = read_letter();
                }
            }

            //already guessed
            bool alreadyused = false;

            for (int i = 0; i <= guesscount + 2; i++) {
                if (guessinguesses[i] == guess) {
                    alreadyused = true;
                }
            }
            //tests validity of guess
            if (((is_lowercase_letter(guess) == true)) && (alreadyused == false)) {
                guessinguesses[guesscount] = guess;
                guesscount++;
                done = true;
            }
        }

        char *read = strchr(secret, guess);
        // guess loop
        if (read != NULL) {
            for (int j = 0; j < (int) strlen(secret); j++) {
                if (guess == secret[j]) {
                    p_input[j] = true;
                    correctguesses++;
                }
            }
        } else {

            lives_used++;
            eliminated[lives_used] = guess;
        }

        //ends game
        if (secret_clean == correctguesses || LOSING_MISTAKE == lives_used) {

            gamedone = false;
        }

    } while (gamedone);

    // win or losing arguments:

    if (correctguesses != secret_clean) {
        printf(CLEAR_SCREEN);
        printf("%s\n\n", arts[lives_used]);
        printf("    Phrase: ");
        for (int j = 0; j < (int) sizeof(p_input); j++) {
            if (p_input[j] == true) {
                printf("%c", secret[j]);
            }

            else {
                printf("_");
            }
        }
        //alpHA
        char temp;
        for (int i = 0; i < (int) strlen(eliminated); i++) {
            for (int j = i + 1; j < (int) strlen(eliminated); j++) {
                if ((int) eliminated[i] > (int) eliminated[j]) {
                    temp = eliminated[i];
                    eliminated[i] = eliminated[j];
                    eliminated[j] = temp;
                }
            }
        }

        if (eliminated[0] != ' ') {
            printf("\nEliminated: %s\n", eliminated);
        } else {
            printf("\nEliminated:%s\n", eliminated);
        }
        printf("\nYou lose! The secret phrase was: %s\n", secret);

    }

    else {
        printf(CLEAR_SCREEN);
        printf("%s\n\n", arts[lives_used]);
        printf("    Phrase: ");
        for (int j = 0; j < (int) sizeof(p_input); j++) {
            if (p_input[j] == true) {
                printf("%c", secret[j]);
            } else {
                printf("_");
            }
        }

        //alpHA
        char temp;
        for (int i = 0; i < (int) strlen(eliminated); i++) {
            for (int j = i + 1; j < (int) strlen(eliminated); j++) {
                if ((int) eliminated[i] > (int) eliminated[j]) {
                    temp = eliminated[i];
                    eliminated[i] = eliminated[j];
                    eliminated[j] = temp;
                }
            }
        }

        if (eliminated[0] != ' ') {
            printf("\nEliminated: %s\n", eliminated);
        } else {
            printf("\nEliminated:%s\n", eliminated);
        }
        printf("\nYou win! The secret phrase was: %s\n", secret);
    }
    return 0;
}
