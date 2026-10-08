%{
    #include <stdio.h>
    #include <ctype.h>

    int error = 0;

    int yylex(void);
    int yyerror(const char *message);
    int power(int base, int exponent);
%}
%token NUMBER
%%
S: S E '\n' {
        if (!error) {
            printf("Result = %d\n", $2);
        }
        error = 0;
    }
 | /* empty */
;
E: E '+' T { $$ = $1 + $3; }
 | E '-' T { $$ = $1 - $3; }
 | T       { $$ = $1; }
;
T: T '*' P { $$ = $1 * $3; }
 | T '/' P {
        if ($3 == 0) {
            printf("Error: division by zero\n");
            error = 1;
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
   }
 | P       { $$ = $1; }
;
P: U '^' P {
        if ($3 < 0) {
            printf("Error: negative exponent is not supported\n");
            error = 1;
            $$ = 0;
        } else {
            $$ = power($1, $3);
        }
   }
 | U       { $$ = $1; }
;
U: '-' U  { $$ = -$2; }
 | F      { $$ = $1; }
;
F: NUMBER { $$ = $1; }
 | '(' E ')' { $$ = $2; }
;
%%
int main(void){
    printf("Enter an expression: ");
    return yyparse();
}

int yylex(void){
    int ch = getchar();

    if (ch != EOF && isdigit((unsigned char) ch)) {
        ungetc(ch, stdin);
        scanf("%d", &yylval);
        return NUMBER;
    }

    return ch;
}

int yyerror(const char *message){
    (void) message;
    printf("Invalid expression!\n");
    error = 1;
    return 0;
}

int power(int base, int exponent){
    int result = 1;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }

    return result;
}