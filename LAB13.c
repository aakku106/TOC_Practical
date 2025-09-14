#include <stdio.h>
#include <string.h>
#define MAX 100

enum states
{
    q0
};

void push(char ch);
void pop();
char get_stack_top();
enum states delta(enum states, char, char);

struct stack
{
    char symbols[MAX];
    int top;
};
struct stack s;

// Stack operations
char get_stack_top()
{
    if (s.top == -1)
        return 'e'; // empty stack = epsilon
    return s.symbols[s.top];
}

void push(char ch)
{
    if (s.top < MAX - 1)
    {
        s.symbols[++s.top] = ch;
    }
    else
    {
        printf("\n Stack Full.");
    }
}

void pop()
{
    if (s.top > -1)
    {
        s.symbols[s.top--] = '\0';
    }
    else
    {
        printf("\n Stack Empty.");
    }
}

// Transition function
enum states delta(enum states state, char ch, char st_top)
{
    enum states curr_state = state;

    switch (state)
    {
    case q0:
        if (ch == 'e' && st_top == 'e')
        {
            curr_state = q0;
            push('$'); // bottom marker
        }
        else if ((ch == '0' && (st_top == '$' || st_top == '0')) ||
                 (ch == '1' && (st_top == '$' || st_top == '1')))
        {
            curr_state = q0;
            push(ch); // push same symbol
        }
        else if ((ch == '1' && st_top == '0') || (ch == '0' && st_top == '1'))
        {
            curr_state = q0;
            pop(); // pop matching opposite symbol
        }
        break;
    }

    return curr_state;
}

int main()
{
    char input[100];
    enum states curr_state = q0;
    s.top = -1;

    // Initial epsilon transition
    curr_state = delta(curr_state, 'e', 'e');

    printf("\nEnter a binary string: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline if present
    input[strcspn(input, "\n")] = '\0';

    int i = 0;
    char ch = input[i];
    char st_top = get_stack_top();

    while (ch != '\0')
    {
        curr_state = delta(curr_state, ch, st_top);
        ch = input[++i];
        st_top = get_stack_top();
    }

    // Final acceptance: only stack bottom should remain
    if (s.top == 0 && s.symbols[0] == '$')
        printf("\n✅ The string \"%s\" is accepted.\n", input);
    else
        printf("\n❌ The string \"%s\" is not accepted.\n", input);

    return 0;
}
