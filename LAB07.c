#include <stdio.h>
#include <string.h>

char input[100];
int l;
int flag = 0;

void q2(int i) {
    // Final state: if input ends here, accept
    if (input[i] == '\0') {
        flag = 1;
    }
}

void q1(int i) {
    if (i < l && input[i] == '1') {
        q2(i + 1);  // move to next character and final state
    }
}

void q0(int i) {
    if (i < l) {
        if (input[i] == '0') {
            q0(i + 1);  // loop back (non-final)
            q1(i + 1);  // transition to q1 if next is '1'
        } else if (input[i] == '1') {
            q0(i + 1);  // loop on '1'
        }
    }
}

int main() {
    printf("\nEnter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // remove newline
    l = strlen(input);

    q0(0);

    if (flag == 1)
        printf("\nThe string is accepted.\n");
    else
        printf("\nThe string is not accepted.\n");

    return 0;
}
