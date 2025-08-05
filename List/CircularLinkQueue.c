#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//定义循环链式队列结构
typedef struct QueueNode{
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct{
    QueueNode *front;
    QueueNode *rear;
} CircularLinkedQueue;


//初始化队列
void InitQueue(CircularLinkedQueue *q){
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->next = node;
    q->front = q->rear = node;
}

//入队
void EnQueue(CircularLinkedQueue *q, int v){
    //队列已满
    if (q->rear->next == q->front){ 
        QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
        newNode->next = q->rear->next;
        q->rear->next = newNode;
    }
    q->rear->data = v;
    q->rear = q->rear->next;
}

//出队
void DeQueue(CircularLinkedQueue *q){
    //队列为空
    if (q->front == q->rear) 
        return; 
    q->front = q->front->next;
}

int main() {
    CircularLinkedQueue Q;
    InitQueue(&Q);

    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    DeQueue(&Q);
    EnQueue(&Q, 3);

    //打印队列元素
    while (Q.front != Q.rear) {
        printf("%d ", Q.front->data);  
        Q.front = Q.front->next;     
    }

    return 0;
}