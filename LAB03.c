#include <stdio.h>
#include <string.h>

enum states { q0, q1, qf };

enum states delta(enum states, char);

int main() {
    char input[100];
    enum states curr_state = q0;
    int i = 0;

    printf("Enter a binary string: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    while (input[i] != '\0') {
        curr_state = delta(curr_state, input[i]);
        i++;
    }

    if (curr_state == qf)
        printf("The string \"%s\" is accepted.\n", input);
    else
        printf("The string \"%s\" is not accepted.\n", input);

    return 0;
}

// Transition Function
enum states delta(enum states s, char ch) {
    switch (s) {
        case q0:
            if (ch == '0')
                return q1;
            else
                return q0;
        case q1:
            if (ch == '1')
                return qf;
            else
                return q1;
        case qf:
            if (ch == '0')
                return q1;
            else
                return q0;
        default:
            return q0;
    }
}
