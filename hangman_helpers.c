#include "hangman_helpers.h"

//JIVAJ BRAR hangman_helpers.h

bool is_lowercase_letter(char c) {
    if (c <= 'z' && c >= 'a') {
        return true;
    } else {
        return false;
    }
}

bool validate_secret(const char *secret) {
    for (int j = 0; j < (int) strlen(secret); j++) {
        if (is_lowercase_letter(secret[j]) != true && secret[j] != '\'' && secret[j] != ' '
            && secret[j] != '-') {
            //printf("lowercase function failed in validate secret");
            return false;
        }
    }
    return true;
}

bool string_contains_character(const char *s, char c) {
    for (int a = 0; (int) strlen(s) > a; a++) {
        if (s[a] == c) {
            return true;
        }
    }
    return false;
}

char read_letter(void) {
    char userinp;
    scanf("%c", &userinp);
    //returns user input
    return userinp;
}
