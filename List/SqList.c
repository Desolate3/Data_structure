#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10

typedef int ElemType;

typedef struct {
    ElemType *data;
    int length;
} SqList;

void InitList(SqList *p){
    //给顺序表分配内存
    (*p).data = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);

    //初始化顺序表元素为0
    for(int i = 0; i < MAXSIZE; i++){
        (*p).data[i] = 0;
    }

    //初始化顺序表长度为0
    (*p).length = 0;
}

void InsertList(SqList *p, int i, ElemType e){

    //判断是否达到最大容量
    if((*p).length >= MAXSIZE){
        printf("已经达到最大容量");
        return;
    }

    //判断插入位置i是否合法
    if(i <= 0 || i > (*p).length + 1){
        printf("插入位置i不合法");
        return;
    }

    //i位置后面元素后移一位
    for(int j = (*p).length; j >= i; j--){
        (*p).data[j] = (*p).data[j - 1];
    }

    (*p).data[i - 1] = e;
    (*p).length++;
}

void DeleteList(SqList *p, int i){

    //判断删除位置i是否合法
    if(i <= 0 || i > (*p).length){
        printf("删除位置i不合法");
        return;
    }

    //i位置后面元素前移一位
    for(int j = i - 1; j < (*p).length - 1; j++){
        (*p).data[j] = (*p).data[j + 1];
    }

    (*p).length--;
}

//按值查找
int LocateElem(SqList *p, ElemType e){
    for(int i = 1; i <= (*p).length; i++){
        if((*p).data[i - 1] == e){
            printf("已查到%d\n", i);
            continue;
        }
    }
    return 0; 
}

void IncreaseList(SqList *p, int len){
    //重新分配新的内存
    ElemType *newData = (ElemType *)malloc(sizeof(ElemType) * (MAXSIZE + len));
    
    for(int i = 0; i < (*p).length; i++){
        newData[i] = (*p).data[i];
    }
    free((*p).data);
    (*p).data = newData;
    (*p).length += len;
}

void PrintList(SqList *p){
    for(int i = 0; i < (*p).length; i++){
        printf("%d ", (*p).data[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    // printf(argc > 1 ? "参数个数：%d\n" : "没有参数\n", argc);
    // for (int i = 0; i < argc; i++){
    //     printf("参数%d：%s\n", i, argv[i]);
    // }

    SqList L;
    InitList(&L);
    InsertList(&L, 1, 1);
    InsertList(&L, 2, 2);
    InsertList(&L, 3, 6);
    InsertList(&L, 4, 5);
    InsertList(&L, 5, 0);
    InsertList(&L, 6, 1);
    InsertList(&L, 3, 7);
    DeleteList(&L, 3);
    PrintList(&L);
    IncreaseList(&L, 3);
    LocateElem(&L, 5);


    return 0;
}