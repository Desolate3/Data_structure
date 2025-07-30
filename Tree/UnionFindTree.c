#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//合并操作-小树合并大树
void Union(int *S, int root1, int root2){
    if(root1 == root2)
        return; //如果两个元素相同，则不需要合并
    if(S[root1] > S[root2]){
        S[root2] = S[root2] + S[root1];
        S[root1] = root2;
    }
    else{
        S[root1] = S[root1] + S[root2];
        S[root2] = root1;
    }
}

//查找操作-查找元素所在的集合
int Find(int S[], int x){
    // if(S[x] < 0){
    //     return x;
    // }
    // else{
    //     while(S[x] >= 0){
    //         x = S[x];
    //     }
    //     return x;
    // }

    int root = x;
    while(S[root] >= 0){
        root = S[root];
    }
    while(x != root){
        int temp = S[x];
        S[x] = root; //路径压缩
        x = temp;
    }
    return root;
}

int main(){
    int UFsets[] = {-9, -4, -2, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 10};
    Union(UFsets, 1, 2);
    printf("%d\n", Find(UFsets, 8));
    return 0;
}