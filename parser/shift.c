#include <stdio.h>
#include <string.h>

int main(void)
{
    char inp[21];
    char stack[50] = "";
    const char *left[] = {"E", "E", "E", "E"};
    const char *right[] = {"E+E", "E*E", "(E)", "i"};
    size_t posi = 0;
    int reduced;

    printf("I am Dheeraj A G. Here is my shift reduce parser output\n");
    printf("\nProductions are: \n");
    printf("E → E+E ∣ E∗E ∣ (E) ∣ i\n");
    printf("\nEnter the inp string: ");

    if (scanf("%19s", inp) != 1)
        return 1;

    strcat(inp, "$ ");
    inp[strlen(inp) - 1] = '\0';

    printf("Stack\tinp\tAction\n");

    while (posi < strlen(inp) - 1) {
        size_t stklen;
        char shifted[2] = {inp[posi++], '\0'};

        strcat(stack, shifted);
        printf("%s\t%s\tShift %s\n", stack,
               inp + posi, shifted);

        do {
            reduced = 0;
            stklen = strlen(stack);

            for (int rule = 0; rule < 4; rule++) {
                size_t rilen = strlen(right[rule]);

                if (stklen >= rilen &&
                    strcmp(stack + stklen - rilen, right[rule]) == 0) {
                    stack[stklen - rilen] = '\0';
                    strcat(stack, left[rule]);
                    printf("%s\t%s\tReduce %s->%s\n", stack,
                           inp + posi, left[rule], right[rule]);
                    reduced = 1;
                    break;
                }
            }
        } while (reduced);
    }

    do {
        reduced = 0;
        size_t stklen = strlen(stack);

        for (int rule = 0; rule < 4; rule++) {
            size_t rilen = strlen(right[rule]);

            if (stklen >= rilen &&
                strcmp(stack + stklen - rilen, right[rule]) == 0) {
                stack[stklen - rilen] = '\0';
                strcat(stack, left[rule]);
                printf("%s\t%s\tReduce %s->%s\n", stack,
                       inp + posi, left[rule], right[rule]);
                reduced = 1;
                break;
            }
        }
    } while (reduced);

    if (strcmp(stack, "E") == 0)
        printf("\nAccepted\n");
    else
        printf("\nNot Accepted\n");

    return 0;
}
