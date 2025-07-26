#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10

typedef char ElemType;

typedef struct{
    ElemType data[MAXSIZE];
    int top; 
}SqStack;

//初始化栈
void InitStack(SqStack *s){
    s->top = -1; 
}

bool IsEmpty(SqStack *s){
    if (s->top == -1)
        return true;
    return false;
}

//入栈
bool Push(SqStack *s, ElemType e){
    if(s->top >= MAXSIZE - 1){
        printf("栈已满，无法入栈");
        return false;
    }
    s->top = s->top + 1;
    s->data[s->top] = e;
    return true;
}

//出栈
bool Pop(SqStack *s){
    if(s->top == -1){
        printf("栈空，无法出栈");
        return false;
    }
    s->top = s->top - 1;
    return true;
}

//获取栈顶元素
bool GetTop(SqStack *s, ElemType *e){
    if(s->top == -1){
        printf("栈空，无法获取栈顶元素");
        return false;
    }
    
    *e = s->data[s->top];
    // printf("栈顶元素为：%c\n", *e);
    return true;
}

//获取栈顶元素
void printStack(SqStack *s){
    if(s->top == -1){
        printf("栈空，不打印\n");
        return;
    }
    int temp = 0;
    while (temp < s->top + 1) {
        printf("%c ", s->data[temp]);
        temp++;
    }
    printf("\n");
}

bool bracketCheck(char str[], int length){
    SqStack S;
    InitStack(&S);

    for (int i = 0; i < length; i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[')
            Push(&S, str[i]);
        else if (IsEmpty(&S))
            return false;

        char topElem;
        GetTop(&S, &topElem);
        if ((str[i] == ')' && topElem == '(') || (str[i] == '}' && topElem == '{') || (str[i] == ']' && topElem == '['))
            Pop(&S);
        else if((str[i] == ')' && topElem != '(') || (str[i] == '}' && topElem != '{') || (str[i] == ']' && topElem != '['))
            return false;
        printStack(&S);
    }

    return IsEmpty(&S);
}


int main(){
    char str[] = "{[{(())}]}";
    int length = sizeof(str) / sizeof(str[0]) - 1;
    if (bracketCheck(str, length))
        printf("括号匹配\n");
    else
        printf("括号不匹配\n");
    return 0;
}