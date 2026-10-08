#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    FILE *fp;
    char line[500];
    char *p;
    int found = 0;
    int forno = 0;

    printf("Hi I'm Dheeraj A G.Here is my output for loop syntax checking.\n\n");
    if (argc < 2){
        printf(" Input file not specified.\n");
        printf(" %s <input_file>\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");

    if (fp == NULL){
        printf("Cannot open file '%s'.\n", argv[1]);
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL){
        p = line;

        while ((p = strstr(p, "for")) != NULL){
            if ((p == line || !isalnum(*(p - 1))) &&
                !isalnum(*(p + 3)) && *(p + 3) != '_'){
                int semicolon = 0;
                int open = 0;
                int close = 0;
                int error = 0;
                int i;

                found = 1;
                forno++;

                printf("for loop %d:", forno);

                p = p + 3;

                while (isspace(*p))
                    p++;

                /* Check '(' */
                if (*p != '('){
                    printf(" '(' is missing after 'for'.\n");
                    error = 1;

                    p++;
                    printf("\n");
                    continue;
                }

                open = 1;
                p++;

                for (i = 0; p[i] != '\0'; i++){
                    if (p[i] == ';')
                        semicolon++;

                    if (p[i] == '(')
                        open++;

                    if (p[i] == ')'){
                        open--;

                        if (open == 0){
                            close = 1;
                            break;
                        }
                    }
                }
                if (!close){
                    printf(" ')' is missing.\n");
                    error = 1;
                }
                if (semicolon != 2){
                    printf("  Expected 2 semicolons inside "
                           "'for' brackets, found %d.\n",
                           semicolon);
                    error = 1;
                }

                if (!error){
                    printf("  For loop syntax is OK.\n");
                }

                printf("\n");
            }

            p = p + 3;
        }
    }

    fclose(fp);
    if (!found)
        printf("'for' loop is not present.\n");

    return 0;
}
