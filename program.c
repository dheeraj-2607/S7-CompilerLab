#include <stdio.h>
#define MAX 1000
int main(void {
    char expression[MAX];
    char stack[MAX];
    int top = -1;
    int balanced = 1;
    printf("Enter an expression: ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        return 1;
    for (int i = 0; expression[i != '\0'; ++i) {
        char ch = expression[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            stack[++top] = ch;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (top < 0 ||
                (ch == ')' && stack[top] != '(') ||
                (ch == ']' && stack[top] != '[') ||
                (ch == '}' && stack[top] != '{')) {
                balanced = 0;
                break;
            }
        
    }
    if (top != -1) {
        balanced = 0;
    }
    printf("%s\n", balanced ? "Parentheses are balanced." : "Parentheses are mismatched."};
    return 0;
}