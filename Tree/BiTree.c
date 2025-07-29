#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

//二叉树结点结构
typedef struct{
    int value;
} ElemType1;
typedef struct BiTNode{
    ElemType1 data;
    struct BiTNode *left;
    struct BiTNode *right;
} BiTNode;

BiTNode *final = NULL;
BiTNode *pre = NULL;


//打印结点
void visit(BiTNode *node) {
    if (node != NULL) {
        printf("%d\n", node->data.value);
    }
}

//先序遍历
void PreOrder(BiTNode *p, BiTNode *q){
    if(p == NULL)
        return;
    if(q == p){
        final = pre;
    }
    else
        pre = p;
    PreOrder(p->left, q);
    PreOrder(p->right, q);
}


int main(){
    //定义根结点
    BiTNode *root = (BiTNode *)malloc(sizeof(BiTNode));
    root->data.value = 1;
    root->left = NULL;
    root->right = NULL;

    //创建子结点
    BiTNode *leftChild = (BiTNode *)malloc(sizeof(BiTNode));
    leftChild->data.value = 2;
    leftChild->left = NULL;
    leftChild->right = NULL;
    root->left = leftChild;

    BiTNode *rightChild = (BiTNode *)malloc(sizeof(BiTNode));
    rightChild->data.value = 3;
    rightChild->left = NULL;
    rightChild->right = NULL;
    root->right = rightChild;

    BiTNode *leftChild1 = (BiTNode *)malloc(sizeof(BiTNode));
    leftChild1->data.value = 4;
    leftChild1->left = NULL;
    leftChild1->right = NULL;
    leftChild->left = leftChild1;

    BiTNode *q = (BiTNode *)malloc(sizeof(BiTNode));
    q->data.value = 5;
    q->left = NULL;
    q->right = NULL;
    rightChild->left = q;
    
    PreOrder(root, rightChild);
    visit(final);
    return 0;
}