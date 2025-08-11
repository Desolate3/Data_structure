#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

//定义查找表结构
typedef struct{
    ElemType *elem;
    int TableLen; 
}SSTable;

//初始化顺序表
void InitSSTable(SSTable *ST, int length){
    ST->elem = (ElemType *)malloc((length + 1) * sizeof(ElemType));
    if (!ST->elem){
        printf("内存分配失败！\n");
        exit(1);
    }
    ST->TableLen = length;
}

//直接插入排序
void InsertSort(SSTable *ST){
    int i;
    int j;
    for (i = 2; i <= ST->TableLen; i++){
        if (ST->elem[i] < ST->elem[i - 1]){
            ST->elem[0] = ST->elem[i];
            for (j = i - 1; ST->elem[0] < ST->elem[j]; j--){
                ST->elem[j + 1] = ST->elem[j]; //后移元素
            }
            //插入到正确位置
            ST->elem[j + 1] = ST->elem[0];     
        }
    }
}

//折半插入排序
void BinaryInsertSort(SSTable *ST){
    int i, j, low, high, mid;
    for (i = 2; i <= ST->TableLen; i++){
        ST->elem[0] = ST->elem[i];          
        low = 1;
        high = i - 1;    

        while (low <= high){
            mid = (low + high) / 2;
            if (ST->elem[mid] > ST->elem[0])
                //在左半部分查找
                high = mid - 1;              
            else
                //在右半部分查找
                low = mid + 1;              
        }
        //high + 1 为插入位置
        for (j = i - 1; j >= high + 1; j--) {
            ST->elem[j + 1] = ST->elem[j];   //统一向后移动
        }
        ST->elem[high + 1] = ST->elem[0];
    }
}

//顺序查找（带哨兵）
int Search_Seq(SSTable ST, ElemType key) {
    ST.elem[0] = key;                      
    int i = ST.TableLen;
    while (ST.elem[i] != key) {
        i--;
    }
    return i; 
}

//折半查找
int Binary_Search(SSTable ST, ElemType key){
    int low = 1;
    int high = ST.TableLen;
    int mid;

    while (low <= high){
        mid = (low + high) / 2;
        if (ST.elem[mid] == key)
            return mid;
        else if (ST.elem[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

//打印查找表
void PrintTable(SSTable ST) {
    for (int i = 1; i <= ST.TableLen; i++) {
        printf("%d ", ST.elem[i]);
    }
    printf("\n");
}


int main(){
    SSTable ST;
    int length = 10;
    ElemType key = 25;
    int position;

    // 初始化表
    InitSSTable(&ST, length);

    // 原始数据（无序）
    int A[] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};

    // 赋值（从下标1开始）
    for (int i = 1; i <= length; i++) {
        ST.elem[i] = A[i - 1];
    }

    printf("原始序列: ");
    PrintTable(ST);

    //直接插入排序
    InsertSort(&ST);
    printf("直接插入排序: ");
    PrintTable(ST);

    //重新初始化数据
    for (int i = 1; i <= length; i++) {
        ST.elem[i] = A[i - 1];
    }

    //折半插入排序
    BinaryInsertSort(&ST);
    printf("折半插入排序: ");
    PrintTable(ST);

    printf("\n");
    
    // 排序后进行查找测试
    position = Search_Seq(ST, key);
    if (position != 0)
        printf("顺序查找结果：关键字在位置 %d\n", position);
    else
        printf("顺序查找失败\n");

    position = Binary_Search(ST, key);
    if (position != -1)
        printf("折半查找结果：关键字在位置 %d\n", position);
    else
        printf("折半查找失败\n");

    return 0;
}