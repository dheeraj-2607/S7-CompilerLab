#include <stdio.h>
#include <string.h>

int main(){
    int n, m, i, j, current, fi, final[10], f, choice;
    char input[10], str[20], ch;
    int trans[10][10];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter input symbols:");
    for(i = 0; i < m; i++){
        scanf(" %c", &input[i]);
    }

    printf("\nEnter transition table:\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            printf("delta(%d, %c) = ", i, input[j]);
            scanf("%d", &trans[i][j]);
        }
    }

    printf("Enter number of final states: ");
    scanf("%d", &fi);

    printf("Enter final states:3");
    for(i = 0; i < fi; i++){
        scanf("%d", &final[i]);
    }

    do{
        printf("Enter input string: ");
        scanf("%s", str);

        current = 0;

        for(i = 0; i < strlen(str); i++){
            ch = str[i];

            for(j = 0; j < m; j++){
                if(ch == input[j]){
                    current = trans[current][j];
                    break;
                }
            }

            if(j == m){
                printf("Invalid input symbol\n");
                return 0;
            }
        }

        f = 0;

        for(i = 0; i < fi; i++){
            if(current == final[i])
            {
                f = 1;
                break;
            }
        }

        if(f)
            printf("Accepted\n");
        else
            printf("Rejected\n");

        printf("Enter your choice (0 - end, 1 - continue): ");
        scanf("%d", &choice);

    } while(choice == 1);

    return 0;
}