#include <stdio.h>
#include <string.h>

char input[100];
int len;
int flag = 0; // Indicates whether substring "001" is found

// Final state
void state_s(int i) {
    flag = 1; // "001" matched
}

// r: looking for '1' after "00"
void state_r(int i) {
    if (i < len) {
        if (input[i] == '1') {
            state_s(i + 1); // Move to accepting state
        }
    }
}

// q: looking for second '0' after first '0'
void state_q(int i) {
    if (i < len) {
        if (input[i] == '0') {
            state_r(i + 1);
        }
    }
}

// p: start state, explores all positions
void state_p(int i) {
    if (i < len) {
        if (input[i] == '0') {
            state_p(i + 1); // Continue from next input
            state_q(i + 1); // Try to match the second '0'
        } else if (input[i] == '1') {
            state_p(i + 1); // Continue searching
        }
    }
}

int main() {
    printf("Enter a binary string: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline if present
    size_t ln = strlen(input);
    if (ln > 0 && input[ln - 1] == '\n') {
        input[ln - 1] = '\0';
    }

    len = strlen(input);
    flag = 0;
    state_p(0);

    if (flag == 1)
        printf("The string \"%s\" is accepted (contains '001').\n", input);
    else
        printf("The string \"%s\" is not accepted (does not contain '001').\n", input);

    return 0;
}
