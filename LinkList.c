#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode{
    int data;
    struct LNode *next;
} LNode, *LinkList;


//在第i个位置插入元素e
LinkList InsertList(LinkList p, int i, int e){
    if (i < 0) {
        printf("插入位置不合法\n");
        return NULL;
    }

    //新建插入结点指针并更改数据域
    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->data = e;

    if(i == 0){
        newNode->next = (LNode *)p;
        return (LinkList)newNode;
    }

    LNode *current = (LNode *)p;
    for (int j = 0; j < i - 1 && current != NULL; j++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("插入位置不合法\n");
        free(newNode);
        return NULL;
    }

    newNode->next = current->next;
    current->next = newNode;
    return p;
}

//删除第i个位置的元素
LinkList DeleteList(LinkList p, int i){
    if (i < 0 || p == NULL) {
        printf("删除位置不合法\n");
        return NULL;
    }
    
    if(i == 0){
        LNode *p = (LNode *)p;
        LNode *pre = p;
        p = p->next;
        free(pre);

        return p;
    }

    LNode *current = (LNode *)p;
    for (int j = 0; j < i - 1; j++) {
        current = current->next;
    }

    if (current == NULL || current->next == NULL) {
        printf("删除位置不合法\n");
        return NULL;
    }

    LNode *q = current->next;
    current->next = q->next;
    free(q);
    return p;
}


void PrintList(LinkList p){
    LNode* q = (LNode*)p;
    while(q != NULL){
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
}

int main(){
    LinkList L = NULL;

    L = InsertList(L, 0, 2);
    L = InsertList(L, 1, 10);
    L = InsertList(L, 2, 20);
    L = InsertList(L, 3, 30);
    PrintList(L);
    L = DeleteList(L, 2);
    return 0;
}

