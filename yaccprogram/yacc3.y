%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int yylex(void);
int yyerror(char *s);
%}

%token LETTER DIGIT

%%

L : S '\n'
    {
        printf("Valid Identifier\n");
        return 0;
    }
  ;

S : LETTER A
  | LETTER
  ;

A : LETTER A
  | DIGIT A
  | LETTER
  | DIGIT
  ;

%%

int yylex(void)
{
    char c;

    c = getchar();

    if (isalpha((unsigned char)c))
        return LETTER;

    if (isdigit((unsigned char)c))
        return DIGIT;

    if (c == '\n')
        return '\n';

    return c;
}

int yyerror(char *s)
{
    printf("Invalid Identifier\n");
    return 0;
}

int main(void)
{
    printf("Enter an identifier: ");
    yyparse();

    return 0;
}