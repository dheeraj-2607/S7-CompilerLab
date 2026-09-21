%{
    #include <stdio.h>
    #include <stdlib.h>

    int result = 0;
    char operation = '+';
    int have_number = 0;
    int error = 0;

    void reset_calculator(void) {
        result = 0;
        operation = '+';
        have_number = 0;
        error = 0;
    }
%}
DIGIT [0-9]
%%
"+"|"-"|"*"|"/" {operation = yytext[0];}
{DIGIT}+ {
    int value = atoi(yytext);

    if (!have_number) {
        result = value;
        have_number = 1;
    } else if (operation == '+') {
        result += value;
    } else if (operation == '-') {
        result -= value;
    } else if (operation == '*') {
        result *= value;
    } else if (operation == '/') {
        if (value == 0) {
            printf("Error: division by zero\n");
            error = 1;
        } else {
            result /= value;
        }
    }
}
[ \t]+ {}
"\n" {
    if (!error && have_number) {
        printf("Result = %d\n", result);
    } else if (!have_number && !error) {
        printf("Error: enter an expression\n");
    }
    reset_calculator();
}
. {printf("Error: invalid character '%s'\n", yytext); error = 1;}
%%
int main(void){
    printf("Enter an expression (use +, -, * or /):\n");
    yylex();
    return 0;
}
int yywrap(void){
    return 1;
}