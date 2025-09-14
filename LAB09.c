#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    int i = 0, j = 0, k, l;
    int row = 0, col = 0, s, x;
    char a[10][10]; // Stores each line from file
    char ch;
    char result[50]; // Stores the processed output sequence
    char search;
    
    fp = fopen("syntax.txt", "r");
    if (!fp)
    {
        perror("File open failed");
        return 1;
    }

    // Read the file into the 2D array a[row][col]
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            a[i][j] = '\0'; // Null-terminate each line
            row = i;
            col = j; // Last column before newline
            j = 0;
            i++;
        }
        else
        {
            a[i][j++] = ch;
        }
    }
    fclose(fp); // Always close file

    // Display read data
    printf("\nContents of syntax.txt:\n");
    for (k = 0; k <= row; k++)
    {
        printf("%s\n", a[k]);
    }

    i = 0; // Reset result array index
    int res_index = 0;

    // Process the input lines
    for (k = 0; k <= row; k++)
    {
        result[res_index++] = a[k][1]; // Store root node (assuming it's at index 1)

        if (a[k][3] == 't') // Check if left child is a reference
        {
            search = a[k][4];
            for (l = 0; l < res_index; l++)
            {
                if (result[l] == search)
                {
                    result[res_index++] = result[l];
                    break;
                }
            }
            result[res_index++] = a[k][5]; // Right child
            s = 5;
        }
        else
        {
            result[res_index++] = a[k][3]; // Left child
            result[res_index++] = a[k][4]; // Right child
            s = 4;
        }

        s++;
        // Check if right child is a reference
        if (a[k][s] == 't')
        {
            s++;
            search = a[k][s];
            for (l = 0; l < res_index; l++)
            {
                if (result[l] == search)
                {
                    result[res_index++] = result[l];
                    break;
                }
            }
        }
        else
        {
            result[res_index++] = a[k][s];
        }
    }

    // Display final transformation
    printf("\n\nSyntax Tree Transformations:\n");
    for (x = res_index - 1; x >= 3; x -= 4)
    {
        printf("\ntt%c: root->%c", result[x - 3], result[x - 1]);

        if (result[x - 2] >= '1' && result[x - 2] <= '9')
            printf(" lc->t%c", result[x - 2]);
        else
            printf(" lc->%c", result[x - 2]);

        if (result[x] >= '1' && result[x] <= '9')
            printf(" re->t%c", result[x]);
        else
            printf(" re->%c", result[x]);
    }

    printf("\n");
    return 0;
}
