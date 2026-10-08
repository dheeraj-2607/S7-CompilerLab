#include <stdio.h>
#include <string.h>

#define MAX 20
#define STACK_SIZE 100

char table[MAX][MAX];
char terminals[MAX];
char stack[STACK_SIZE];

int n;
int top = -1;

int pos(char ch){
    for (int i = 0; i < n; i++)
    {
        if (terminals[i] == ch)
            return i;
    }
    return -1;
}

char topTerminal(){
    for (int i = top; i >= 0; i--)
    {
        if (stack[i] != 'E')
            return stack[i];
    }

    return '$';
}

void showStack(){
    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

int valid(char handle[]){
    if (strcmp(handle, "i") == 0)
        return 1;

    if (strcmp(handle, "E+E") == 0)
        return 1;

    if (strcmp(handle, "E-E") == 0)
        return 1;

    if (strcmp(handle, "E*E") == 0)
        return 1;

    if (strcmp(handle, "E/E") == 0)
        return 1;

    if (strcmp(handle, "E^E") == 0)
        return 1;

    return 0;
}
int main(){
    char input[100];
    char handle[50];
    int ip = 0;
    int boundary, last;
    int len;
    int row, col;
    
    printf("Enter the no of terminals: ");
    scanf("%d", &n);
    
    printf("Enter the terminals: ");
    for (int i = 0; i < n; i++){
        scanf(" %c", &terminals[i]);
    }
    
    printf("\nEnter the precedence relation:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%c & %c: ", terminals[i], terminals[j]);
            scanf(" %c", &table[i][j]);
        }
    }
    
    printf("\n\nOperator Precedence Table\n\n");
    printf("\t");
    for (int i = 0; i < n; i++)
        printf("%c\t", terminals[i]);
    printf("\n");
    for (int i = 0; i < n; i++){
        printf("%c\t", terminals[i]);
        for (int j = 0; j < n; j++){
            printf("%c\t", table[i][j]);
        }
        printf("\n");
    }
    
    printf("\nEnter the input string: ");
    scanf("%s", input);
    
    if (input[strlen(input) - 1] != '$')
        strcat(input, "$");
   
    top = -1;
    stack[++top] = '$';

    printf("\n%-15s %-15s %s\n","Stack", "Input", "Action");
    while (1){
        char a = topTerminal();
        char b = input[ip];
        
        if (top == 1 && stack[0] == '$' && stack[1] == 'E' && b == '$'){
            showStack();
            printf("\t\t%-15s\tAccept\n",input + ip);
            printf("\nACCEPTED.\n");
            break;
        }
        row = pos(a);
        col = pos(b);
        
        if (row == -1 || col == -1){
            printf("\nInvalid terminal encountered.\n");
            printf("REJECTED.\n");
            break;
        }
        
        if (table[row][col] == '<' || table[row][col] == '='){
            showStack();
            printf("\t\t%-15s\tShift %c\n",input + ip,b);

            stack[++top] = b;
            ip++;
        }
        
        else if (table[row][col] == '>'){
            last = -1;
            boundary = -1;
            for (int i = top; i >= 0; i--){
                if (stack[i] != 'E'){
                    if (last != -1){
                        int r1 = pos(stack[i]);
                        int r2 = pos(stack[last]);
                        if (r1 != -1 &&
                            r2 != -1 &&
                            table[r1][r2] == '<')
                        {
                            boundary = i;
                            break;
                        }
                    }

                    last = i;
                }
            }
            len = 0;
            for (int i = boundary + 1; i <= top; i++){
                handle[len++] = stack[i];
            }
            handle[len] = '\0';
            showStack();
            printf("\t\t%-15s\tReduce %s\n",input + ip,handle);
            
            if (!valid(handle)){
                printf("\nInvalid handle: %s\n", handle);
                printf("REJECTED.\n");

                return 0;
            }
            top = boundary;
            stack[++top] = 'E';
        }
        else{
            printf("\nNo valid precedence relation between %c and %c.\n",
                   a, b);

            printf("REJECTED.\n");
            break;
        }
    }
    return 0;
}