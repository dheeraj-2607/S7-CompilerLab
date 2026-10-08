%{
    #include<stdio.h>
    int line = 1;
    int slno = 1;
%}
DIGIT [0-9]
ALPHA [a-zA-Z]
WS [ \t]
%%
{WS}+ {}
"\n" {line++;}
"void"|"main"|"if"|"else" {printf("\n%d\t%s\tkeyword\t%d",slno,yytext,line);slno++;}
{ALPHA}({ALPHA}|{DIGIT})* {printf("\n%d\t%s\tidentifier\t%d",slno,yytext,line);slno++;}
"+"|"-"|"*"|"/" {printf("\n%d\t%s\tarithmetic_op\t%d",slno,yytext,line);slno++;}
"<"|"<="|">"|">=" {printf("\n%d\t%s\trelop\t%d",slno,yytext,line);slno++;}
{DIGIT}+"."{DIGIT} {printf("\n%d\t%s\tfloat\t%d",slno,yytext,line);slno++;}
{DIGIT}+ {printf("\n%d\t%s\tnumber\t%d",slno,yytext,line);slno++;}
";" {printf("\n%d\t%s\tsemicolon\t%d",slno,yytext,line);slno++;}
"#"|"->"|"$" {printf("\n%d\t%s\tspecial\t%d",slno,yytext,line);slno++;}
. {printf("\n%d\t%s\tunrecognized\t%d",slno,yytext,line);slno++;}
%%
void main(int argc,char* argv[]){
    yyin=fopen(argv[1],"r");
    printf("slno\tlexeme\ttoken\tlineno");
    yylex();
    printf("\n");
}
int yywrap(){
    return 1;
}