#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_RHS 10
#define MAX_LEN 100

struct prod {
    char lhs[10];
    char rhs[MAX_RHS][10];
    int n;
} pro[MAX_RULES];

int n_rules = 0;

char input[MAX_LEN];

// Recursive function to try to derive 'str' starting from 'temp'
// Returns 1 if match, else 0
int derive(char *temp, int pos) {
    // If temp fully processed
    if (pos == strlen(temp)) {
        // If length matches input length
        if (strcmp(temp, input) == 0) {
            return 1;
        }
        return 0;
    }

    if (!isupper(temp[pos])) {
        // Terminal char: must match input at same position
        if (pos >= strlen(input) || temp[pos] != input[pos])
            return 0;
        // Move to next char
        return derive(temp, pos + 1);
    } else {
        // Non-terminal: try all productions for this non-terminal
        for (int i = 0; i < n_rules; i++) {
            if (pro[i].lhs[0] == temp[pos]) {
                for (int j = 0; j < pro[i].n; j++) {
                    char new_temp[MAX_LEN];
                    // Build new string replacing temp[pos] with rhs[j]
                    // temp[0..pos-1] + rhs[j] + temp[pos+1..end]
                    strncpy(new_temp, temp, pos);
                    new_temp[pos] = '\0';
                    strcat(new_temp, pro[i].rhs[j]);
                    strcat(new_temp, temp + pos + 1);

                    // Recursive call
                    if (derive(new_temp, pos)) {
                        return 1; // success
                    }
                }
                // No match found for any rhs of this non-terminal
                return 0;
            }
        }
        // Non-terminal not found in productions => fail
        return 0;
    }
}

int main() {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        perror("Cannot open input.txt");
        return 1;
    }

    // Initialize
    for (int i = 0; i < MAX_RULES; i++) {
        pro[i].n = 0;
        pro[i].lhs[0] = '\0';
    }

    // Read grammar file: format per line: LHS RHS
    // Multiple lines with same LHS means multiple productions
    char lhs[10], rhs[10];
    n_rules = 0;
    while (fscanf(f, "%s %s", lhs, rhs) == 2) {
        // Check if lhs already exists
        int found = 0;
        for (int i = 0; i < n_rules; i++) {
            if (strcmp(pro[i].lhs, lhs) == 0) {
                strcpy(pro[i].rhs[pro[i].n], rhs);
                pro[i].n++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(pro[n_rules].lhs, lhs);
            strcpy(pro[n_rules].rhs[0], rhs);
            pro[n_rules].n = 1;
            n_rules++;
        }
    }
    fclose(f);

    printf("Grammar:\n");
    for (int i = 0; i < n_rules; i++) {
        for (int j = 0; j < pro[i].n; j++) {
            printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);
        }
    }

    // Main input loop
    while (1) {
        printf("\nEnter string to parse (0 to exit): ");
        scanf("%s", input);
        if (strcmp(input, "0") == 0) break;

        if (derive(pro[0].rhs[0], 0)) {
            printf("The string \"%s\" CAN be parsed ✅\n", input);
        } else {
            printf("The string \"%s\" CANNOT be parsed ❌\n", input);
        }
    }

    return 0;
}
