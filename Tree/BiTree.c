#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

//二叉树结点结构
typedef struct{
    int value;
} ElemType1;
typedef struct{
    ElemType1 data;
    struct BiTNode *left;
    struct BiTNode *right;
} BiTNode;



//访问结点
void visit(BiTNode *node) {
    if (node != NULL) {
        printf("%d ", node->data.value);
    }
}

//先序遍历
void PreOrder(BiTNode *T){
    if(T == NULL)
        return;
    visit(T);
    PreOrder(T->left);
    PreOrder(T->right);
}


int main(){
    //定义根结点
    BiTNode *root = (BiTNode *)malloc(sizeof(BiTNode));
    root->data.value = 1;
    root->left = NULL;
    root->right = NULL;

    //创建左子结点
    BiTNode *leftChild = (BiTNode *)malloc(sizeof(BiTNode));
    leftChild->data.value = 2;
    leftChild->left = NULL;
    leftChild->right = NULL;
    root->left = leftChild;

    return 0;
}