#include <stdio.h>
#include <string.h>
#define MAX 100

enum states
{
    q0,
    q1,
    q2,
    qf,
    qr
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
    char input[20];
    enum states curr_state = q0;
    s.top = -1;

    // Initial transition (epsilon move)
    curr_state = delta(curr_state, '\0', '\0'); // Initial push of '$'

    printf("\nEnter a binary string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // remove trailing newline

    int i = 0;
    char ch = input[i];
    char st_top = get_stack_top();

    while (i < strlen(input))
    {
        curr_state = delta(curr_state, ch, st_top);
        i++;
        ch = input[i];
        st_top = get_stack_top();
    }

    // Final transition after input ends
    curr_state = delta(curr_state, '\0', get_stack_top());

    if (curr_state == qf)
        printf("\nThe string \"%s\" is accepted.\n", input);
    else
        printf("\nThe string \"%s\" is not accepted.\n", input);

    return 0;
}

enum states delta(enum states s, char ch, char st_top)
{
    enum states curr_state = qr;

    switch (s)
    {
    case q0:
        if (ch == '\0' && st_top == '\0')
        {
            curr_state = q1;
            push('$');
        }
        break;

    case q1:
        if (ch == '0' && (st_top == '0' || st_top == '$'))
        {
            curr_state = q1;
            push(ch);
        }
        else if (ch == '1' && st_top == '0')
        {
            curr_state = q2;
            pop();
        }
        else
        {
            curr_state = qr;
        }
        break;

    case q2:
        if (ch == '1' && st_top == '0')
        {
            curr_state = q2;
            pop();
        }
        else if (ch == '\0' && st_top == '$')
        {
            curr_state = qf;
            pop();
        }
        else
        {
            curr_state = qr;
        }
        break;
    }

    return curr_state;
}

char get_stack_top()
{
    if (s.top == -1)
        return '\0'; // Stack empty
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
        printf("\nStack Full.");
    }
}

void pop()
{
    if (s.top > -1)
    {
        s.symbols[s.top--] = ' ';
    }
    else
    {
        printf("\nStack Empty.");
    }
}
