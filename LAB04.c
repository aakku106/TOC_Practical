#include <stdio.h>
#include <string.h>

enum states
{
    q0,  // Start state
    q1,  // Saw 0
    q2,  // Saw 00
    qf   // Saw 001 -> Accepting state
};

enum states delta(enum states, char);

int main()
{
    enum states curr_state = q0;
    char string[100], ch;
    int i = 0;

    printf("Enter a binary string: ");
    fgets(string, sizeof(string), stdin);

    // Remove newline character
    size_t len = strlen(string);
    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }

    ch = string[i];
    while (ch != '\0')
    {
        curr_state = delta(curr_state, ch);
        ch = string[++i];
    }

    if (curr_state == qf)
        printf("The string \"%s\" is accepted (contains '001').\n", string);
    else
        printf("The string \"%s\" is not accepted (does not contain '001').\n", string);

    return 0;
}

// DFA transition function
enum states delta(enum states s, char ch)
{
    switch (s)
    {
    case q0:
        return (ch == '0') ? q1 : q0;
    case q1:
        return (ch == '0') ? q2 : q0;
    case q2:
        return (ch == '1') ? qf : q2;
    case qf:
        return qf; // Once accepted, remain accepted
    default:
        return q0;
    }
}
