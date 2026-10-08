#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    int ch, ch1, line = 1, si = 0, i, flag = 0;
    char lexeme[50];
    char keyword[20][50] = {
        "void", "int", "char", "float", "double",
        "if", "else", "for", "while", "return",
        "break", "continue", "printf", "scanf",
        "fopen", "fclose", "fgetc", "ungetc"
    };

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w");
    fprintf(fp2, "SLNO\tLEXEME\tLINE NO\n");

    while ((ch = fgetc(fp1)) != EOF)
    {
        if (ch == ' ' || ch == '\t');
        else if (ch == '\n')
        {
            line++;
        }
        else if (ch == ';')
        {
            si++;
            fprintf(fp2, "\n%d\t%c\tsemi_colon\t%d", si, ch, line);
        }
        else if (ch == '(' || ch == '{' || ch == '[')
        {
            si++;
            fprintf(fp2, "\n%d\t%c\topen_bracket\t%d", si, ch, line);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            si++;
            fprintf(fp2, "\n%d\t%c\tclose_bracket\t%d", si, ch, line);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
        {
            si++;
            fprintf(fp2, "\n%d\t%c\tarithmetic_operator\t%d", si, ch, line);
        }
        else if (ch == '&' || ch == ',' || ch == '.' || ch == '#')
        {
            si++;
            fprintf(fp2, "\n%d\t%c\tspecial_operator\t%d", si, ch, line);
        }
        else if (ch == '<' || ch == '>' || ch == '!')
        {
            i = 0;
            lexeme[i++] = ch;
            ch1 = fgetc(fp1);
            if (ch1 == '=')
            {
                lexeme[i++] = ch1;
                lexeme[i] = '\0';
            }
            else
            {
                lexeme[i] = '\0';
                ungetc(ch1, fp1);
            }
            si++;
            fprintf(fp2, "\n%d\t%s\trelational_operator\t%d", si, lexeme, line);
        }
        else if (ch == '=')
        {
            i = 0;
            ch1 = fgetc(fp1);
            if (ch1 == '=')
            {
                lexeme[i++] = ch1;
                lexeme[i] = '\0';
                si++;
                fprintf(fp2, "\n%d\t%s\trelational_operator\t%d", si, lexeme, line);
            }
            else
            {
                lexeme[i] = '\0';
                ungetc(ch1, fp1);
                si++;
                fprintf(fp2, "\n%d\t%s\tassignment_operator\t%d", si, lexeme, line);
            }
        }
        else if (isdigit(ch))
        {
            flag = 0;
            i = 0;
            ch1 = ch;
            do
            {
                lexeme[i++] = ch1;
                if (ch1 == '.')
                {
                    flag = 1;
                }
                ch1 = fgetc(fp1);
            } while (isdigit(ch1) || ch1 == '.');
            lexeme[i] = '\0';
            ungetc(ch1, fp1);
            if (flag == 1)
            {
                si++;
                fprintf(fp2, "\n%d\t%s\tfloat_number\t%d", si, lexeme, line);
            }
            else
            {
                si++;
                fprintf(fp2, "\n%d\t%s\tnumber\t%d", si, lexeme, line);
            }
        }
        else if (isalpha(ch))
        {
            flag = 0;
            i = 0;
            ch1 = ch;
            do
            {
                lexeme[i++] = ch1;
                ch1 = fgetc(fp1);
            } while (isdigit(ch1) || isalpha(ch1));
            lexeme[i] = '\0';
            ungetc(ch1, fp1);
            for (int j = 0; j < 19; j++)
            {
                if (strcmp(lexeme, keyword[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                si++;
                fprintf(fp2, "\n%d\t%s\tkeyword\t%d", si, lexeme, line);
            }
            else
            {
                si++;
                fprintf(fp2, "\n%d\t%s\tidentifier\t%d", si, lexeme, line);
            }
        }
        else
            fprintf(fp2,"error");
    }

    fclose(fp1);
    fclose(fp2);
    printf("\nOutput file created successfully.\n");
}