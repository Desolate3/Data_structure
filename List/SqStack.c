#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10

typedef int ElemType;

typedef struct{
    ElemType data[MAXSIZE];
    int top; 
}SqStack;

//初始化栈
void InitStack(SqStack *s){
    s->top = -1; 
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
    printf("栈顶元素为：%d\n", *e);
    return true;
}

int main(){
    SqStack S;
    ElemType e;
    InitStack(&S);
    Push(&S, 4);
    Push(&S, 7);
    Push(&S, 9);
    Push(&S, 2);
    Push(&S, 0);
    Pop(&S);
    GetTop(&S, &e);
    return 0;
}