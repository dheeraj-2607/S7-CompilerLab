#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *fp1, *fp2;
    int ch, ch1, ch2;

    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    while ((ch = fgetc(fp1)) != EOF){
        switch (ch){
            case ' ':
            case '\t':
            case '\n':
            case '\r':
            break;
            case '/':
                ch1 = fgetc(fp1);
            if (ch1 == '/'){
                while ((ch = fgetc(fp1)) != '\n' && ch != EOF);
            }
            else if (ch1 == '*'){
                while ((ch1 = fgetc(fp1)) != EOF){
                    if (ch1 == '*'){
                        ch2 = fgetc(fp1);
                        if (ch2 == '/')
                            break;
                        else
                            ungetc(ch2, fp1);
                    }
                }
            }
            else{
                fputc('/', fp2);
                if (ch1 != EOF)
                    ungetc(ch1, fp1);
            }
            break;
            default:
            fputc(ch, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    printf("\nOutput file created successfully.\n");
    return 0;
}