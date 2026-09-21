#include<stdio.h>
#include<stdlib.h>
#define MAX 100
char stack[MAX];
int top = -1;
int pop() {
    if (top == -1)
        return 0;
    return stack[top--];
}

void push(char val) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = val;
}
void main(int argc,char *argv[]){
    char ch;
    int flag = 0;
    int count = 0;
    FILE *fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("File not found\n");
        return;
    }
    printf("I'm Dheeraj A G.This is my output for 'for loop' syntax check\n");
    printf("\n");
    while((ch = fgetc(fp)) != EOF){
        if(ch == 'f'){
            push(ch);
            ch = fgetc(fp);
            if(ch == 'o'){
                push(ch);
                ch = fgetc(fp);
                if(ch == 'r'){
                    push(ch);
                    ch = fgetc(fp);
                    if (ch == '('){
                        push(ch);
                        while ((ch = fgetc(fp)) != ')' && ch != '\n'){
                            if(ch == ';'){
                                push(ch);
                                count++;
                            }
                               
                        }
                         if(count != 2){
                            flag = 3;
                      } 
                        if(ch == ')'){
                            push(ch);
                        }
                        else{
                            flag = 2;
                        }   
                    }
                    else if(ch != '('){
                        printf("for loop is present \n'(' is not used immediate after 'for'\n");
                        exit(1);
                    } 
                    
                }
                printf("for loop is present in the file\n");
                flag = 1;
            }  
            else if(ch != 'o'){
                 pop();
            }
        }
    }
    if(flag == 1){
        if(stack[top]!=')'){
            printf("')' is missing at the end\n");
        }
        else if(stack[top] == ')'){
            flag = 4;
        }
        if(count !=2){
            printf("; is missing or not properly used\n");
            exit(1);
        }
        else if(flag == 4){
            printf("for loop is correctly implemented\n");
        }
        if(flag == 0) {
        printf("for loop is not present or incorrectly used\n");
        }
    }
    else{
        printf("for loop is not present\n");
    }    
    fclose(fp);
}