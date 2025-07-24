#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10

typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int front;
    int rear;
} SqQueue;

//初始化队列
void InitQueue(SqQueue *q) {
    q->front = 0;
    q->rear = 0;
}

//入队
bool EnQueue(SqQueue *q, ElemType e) {
    if ((q->rear + 1) % MAXSIZE == q->front) {
        printf("队列已满，无法入队");
        return false;
    }
    q->data[q->rear] = e;
    q->rear = (q->rear + 1) % MAXSIZE;
    return true;
}

//出队
bool DeQueue(SqQueue *q){
    if(q->front == q->rear){
        printf("队列为空，无法出队");
        return false;
    }
    q->front = (q->front + 1) % MAXSIZE;
    return true;
}

//获取队头元素
bool GetQueue(SqQueue *q, ElemType *e){
    if(q->front == q->rear){
        printf("队列为空，无法出队");
        return false;
    }
    *e = q->data[q->front];
    printf("队头元素为%d", *e);
    return true;
}


int main(){
    SqQueue Q;
    ElemType e;
    InitQueue(&Q);
    EnQueue(&Q, 3);
    EnQueue(&Q, 6);
    EnQueue(&Q, 1);
    EnQueue(&Q, 9);
    EnQueue(&Q, 5);
    DeQueue(&Q);
    GetQueue(&Q, &e);
    return 0;
}