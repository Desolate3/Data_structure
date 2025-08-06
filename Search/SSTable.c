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
    //多分配一个空间给哨兵
    ST->elem = (ElemType *)malloc((length + 1) * sizeof(ElemType)); 
    if (!ST->elem)
        return;
    ST->TableLen = length;
}

//顺序查找（带哨兵）
int Search_Seq(SSTable ST, ElemType key){
    //设置哨兵
    ST.elem[0] = key;
    
    //从表尾开始向前查找
    int i = ST.TableLen;
    
    while (ST.elem[i] != key){
        i--;
    }
    return i;
}

//折半查找
int Binary_Search(SSTable L, ElemType key){
    int low = 1;
    int high = L.TableLen;
    int mid;
    
    while (low <= high){
        mid = (low + high) / 2;
        if (L.elem[mid] == key)
            return mid;
        else if (L.elem[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

// 打印查找表
void PrintTable(SSTable ST){
    for (int i = 1; i <= ST.TableLen; i++){
        printf("%d ", ST.elem[i]);
    }
    printf("\n");
}

int main(){
    SSTable ST;
    int length = 10; 
    int key = 25;        
    int position;   
    

    InitSSTable(&ST, length);
    

    int A[] = {4, 6, 9, 12, 17, 25, 34, 38, 50, 100};
    for (int i = 1; i <= length; i++){
        ST.elem[i] = A[i-1]; 
    }
    
    PrintTable(ST);

    position = Search_Seq(ST, key);
    
    if (position != 0)
        printf("顺序查找结果：关键字在表中的位置是：%d\n", position);
    else
        printf("查找失败");
    
    
    position = Binary_Search(ST, key);
    if (position != -1) 
        printf("折半查找结果：关键字在表中的位置是：%d\n", position);
    else
        printf("查找失败");
    

    return 0;
}