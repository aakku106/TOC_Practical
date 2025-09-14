#include <stdio.h>
#include <string.h>

#define MAX 100

enum states
{
    q0,
    q1,
    qf
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

int main()
{
    char input[100];
    enum states curr_state = q0;
    s.top = -1;

    // Initial epsilon transition
    curr_state = delta(curr_state, 'e', 'e');

    printf("\nEnter a binary string: ");
    fgets(input, sizeof(input), stdin);

    // Remove trailing newline if any
    input[strcspn(input, "\n")] = '\0';

    int i = 0;
    char ch = input[i];
    char st_top = get_stack_top();

    while (ch != '\0')
    {
        curr_state = delta(curr_state, ch, st_top);
        i++;
        ch = input[i];
        st_top = get_stack_top();
    }

    // Final epsilon transition (to qf) if stack has only '$'
    curr_state = delta(curr_state, '\0', get_stack_top());

    if (curr_state == qf)
        printf("\n✅ The string \"%s\" is accepted.\n", input);
    else
        printf("\n❌ The string \"%s\" is not accepted.\n", input);

    return 0;
}

// Transition function
enum states delta(enum states state, char ch, char st_top)
{
    enum states curr_state = state;

    switch (state)
    {
    case q0:
        if (ch == 'e' && st_top == 'e') // epsilon transition
        {
            curr_state = q1;
            push('$'); // stack bottom marker
        }
        break;

    case q1:
        if ((ch == '0' || ch == '1') && (st_top == '$' || st_top == ch))
        {
            // Push same char
            curr_state = q1;
            push(ch);
        }
        else if ((ch == '1' && st_top == '0') || (ch == '0' && st_top == '1'))
        {
            // Pop matching pair
            curr_state = q1;
            pop();
        }
        else if (ch == '\0' && st_top == '$')
        {
            curr_state = qf;
            pop();
        }
        break;
    }

    return curr_state;
}

// Stack operations
char get_stack_top()
{
    if (s.top == -1)
        return 'e'; // empty stack treated as epsilon
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
        printf("\nStack Overflow.");
    }
}

void pop()
{
    if (s.top >= 0)
    {
        s.symbols[s.top--] = '\0';
    }
    else
    {
        printf("\nStack Underflow.");
    }
}
