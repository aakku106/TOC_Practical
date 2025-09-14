#include <stdio.h>
#include <string.h>

enum states
{
    q0, // Initial state
    q1, // Seen '0'
    qf, // Seen '01' => accepting state
    qd  // Dead state
};

enum states delta(enum states s, char ch);

int main()
{
    char input[100];
    enum states curr_state = q0;
    int i = 0;

    printf("Enter a binary string: ");
    fgets(input, sizeof(input), stdin);

    // Remove trailing newline if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }

    while (input[i] != '\0')
    {
        curr_state = delta(curr_state, input[i]);
        i++;
    }

    if (curr_state == qf || curr_state == qf)
    {
        printf("The string \"%s\" is accepted.\n", input);
    }
    else
    {
        printf("The string \"%s\" is not accepted.\n", input);
    }

    return 0;
}

// Transition Function
enum states delta(enum states s, char ch)
{
    switch (s)
    {
    case q0:
        return (ch == '0') ? q1 : qd;
    case q1:
        return (ch == '1') ? qf : qd;
    case qf:
        return (ch == '0' || ch == '1') ? qf : qd;
    case qd:
        return qd;
    default:
        return qd;
    }
}
