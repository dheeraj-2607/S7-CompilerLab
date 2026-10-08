%{
    #include <stdio.h>
    #include <ctype.h>

    int yylex(void);
    int yyerror(const char *message);
%}
%token NUMBER
%%
S: E '\n' { printf("Result = %d\n", $1); }
;
E: E '+' T { $$ = $1 + $3; }
 | T       { $$ = $1; }
;
T: T '*' F { $$ = $1 * $3; }
 | F       { $$ = $1; }
;
F: NUMBER  { $$ = $1; }
;
%%
int main(void)
{
    printf("Enter an expression: ");
    return yyparse();
}

int yylex(void)
{
    int ch = getchar();

    if (ch != EOF && isdigit((unsigned char) ch)) {
        ungetc(ch, stdin);
        scanf("%d", &yylval);
        return NUMBER;
    }

    return ch;
}

int yyerror(const char *message)
{
    (void) message;
    printf("Invalid expression!\n");
    return 0;
}