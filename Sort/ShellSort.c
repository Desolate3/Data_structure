#include <stdio.h>
#include <stdlib.h>

//希尔排序
void ShellSort(int A[], int n){
    //d表示子序列的间隔
    int d, i, j;
    
    for (d = n / 2; d >= 1; d = d / 2){    
        for (i = d + 1; i <= n; ++i){
            if (A[i] < A[i - d]){   
                //将A[i]插入有序增量子表
                //A[0]作为暂存单元使用
                A[0] = A[i];        
                for (j = i - d; j > 0 && A[0] < A[j]; j -= d){
                    A[j + d] = A[j]; //后移
                }
                A[j + d] = A[0];    
            }
        }
    }
}

// 打印数组
void PrintArray(int A[], int n){
    for (int i = 1; i <= n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(){
    int A[] = {0, 62, 83, 17, 49, 28, 94, 15, 72, 36, 57};
    int n = 10; 
    
    printf("排序前: ");
    PrintArray(A, n);
    
    ShellSort(A, n);
    
    printf("排序后: ");
    PrintArray(A, n);
    
    return 0;
}