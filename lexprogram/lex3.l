%{
#include <stdio.h>
FILE *fp1, *fp2;
int flag = 0;
%}

WS [ \t]

%%
{WS}+ { }
"//" { flag = 1; }
"/*" { flag = 2; }
"\n" { if (flag == 1) flag = 0; }
"*/" { if (flag == 2) flag = 0; }
. { if (flag == 0) fprintf(fp2, "%s", yytext); }

%%

void main(int argc, char *argv[]) {
    fp1 = fopen(argv[1], "r");
    yyin = fp1;
    fp2 = fopen(argv[2], "w");
    yylex();
    fclose(fp1);
    fclose(fp2);
    printf("Output file created successfully.\n");
}

int yywrap() {
    return 1;
}