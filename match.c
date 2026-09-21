#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char ch;
    int line;
} StackItem;

StackItem stack[MAX];
int top = -1;

StackItem pop(void) {
    StackItem empty = {'\0', 0};
    if (top == -1) {
        return empty;
    }
    return stack[top--];
}

void push(char val, int lineNo) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top].ch = val;
    stack[top].line = lineNo;
}

int main(int argc, char *argv[]) {
    FILE *file;
    char ch;
    int line = 1;
    int error = 0;

    if (argc != 2) {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }
    printf("I am Dheeraj A G. Here is my output for parenthesis matching\n");
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line++;
            continue;
        }

        if (ch == '(' || ch == '{' || ch == '[') {
            push(ch, line);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1) {
                printf("Right %c missing : Identified at line number %d\n", ch, line);
                error = 1;
            } else {
                StackItem item = pop();
                if ((ch == ')' && item.ch != '(') || (ch == '}' && item.ch != '{') || (ch == ']' && item.ch != '[')) {
                    printf("Parentheses mismatch between %c and %c : Identified at line number %d\n", item.ch, ch, line);
                    error = 1;
                }
            }
        }
    }

    while (top != -1) {
        StackItem item = pop();
        printf("Left %c missing : Identified at line number %d\n", item.ch, item.line);
        error = 1;
    }

    if (!error) {
        printf("Parentheses are balanced.\n");
    }

    fclose(file);
    return 0;
}
