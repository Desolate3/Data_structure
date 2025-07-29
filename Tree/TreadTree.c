#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

//线索二叉树结点结构
typedef struct{
    int value;
} ElemType;
typedef struct TreadTNode{
    ElemType data;
    struct TreadTNode *left;
    struct TreadTNode *right;
    int ltag;
    int rtag;
} TreadTNode;

TreadTNode *pre = NULL; //前驱结点

//打印结点
void visit(TreadTNode *node) {
    if (node != NULL) {
        printf("%d\n", node->data.value);
    }
}

//中序遍历构造线索二叉树
void InOrder(TreadTNode *root){
    if(root == NULL)
        return;
    
    if(root->ltag == 0){
        InOrder(root->left); //递归遍历左子树
    }

    if(root != NULL && root->left == NULL){
        root->ltag = 1;
        root->left = pre; //将当前结点的前驱结点链接到左子树
    }
    if(pre != NULL && pre->right == NULL){
        pre->rtag = 1;
        pre->right = root; //将前驱结点的后继结点链接到右子树
    }
    pre = root; //更新前驱结点
    
    if(root->rtag == 0){
        InOrder(root->right); //递归遍历右子树
    }
}

//获取指定结点的中序后继结点
TreadTNode *NextNode(TreadTNode *p){
    if(p->rtag == 1){
        return p->right; //如果是线索，则返回后继结点
    }
    else{
        p = p->right; //否则，返回右子树的最左结点
        while(p != NULL && p->ltag == 0){
            p = p->left;
        }
        return p;
    }
}

//获取指定结点的中序前驱结点
TreadTNode *PreNode(TreadTNode *p){
    if(p->ltag == 1){
        return p->left; //如果是线索，则返回前驱结点
    }
    else{
        p = p->left; //否则，返回左子树的最右结点
        while(p != NULL && p->rtag == 0){
            p = p->right;
        }
        return p;
    }
}

int main(){
    //定义根结点
    TreadTNode *root = (TreadTNode *)malloc(sizeof(TreadTNode));
    root->data.value = 1;
    root->left = NULL;
    root->right = NULL;
    root->ltag = 0; 
    root->rtag = 0; 

    //创建子结点
    TreadTNode *leftChild = (TreadTNode *)malloc(sizeof(TreadTNode));
    leftChild->data.value = 2;
    leftChild->left = NULL;
    leftChild->right = NULL;
    root->left = leftChild;
    leftChild->ltag = 0;
    leftChild->rtag = 0;

    TreadTNode *rightChild = (TreadTNode *)malloc(sizeof(TreadTNode));
    rightChild->data.value = 3;
    rightChild->left = NULL;
    rightChild->right = NULL;
    root->right = rightChild;
    rightChild->ltag = 0;
    rightChild->rtag = 0;

    TreadTNode *leftChild1 = (TreadTNode *)malloc(sizeof(TreadTNode));
    leftChild1->data.value = 4;
    leftChild1->left = NULL;
    leftChild1->right = NULL;
    leftChild->left = leftChild1;
    leftChild1->ltag = 0;
    leftChild1->rtag = 0;

    TreadTNode *leftChild12 = (TreadTNode *)malloc(sizeof(TreadTNode));
    leftChild12->data.value = 5;
    leftChild12->left = NULL;
    leftChild12->right = NULL;
    leftChild1->right = leftChild12;
    leftChild12->ltag = 0;
    leftChild12->rtag = 0;

    InOrder(root);
    visit(PreNode(leftChild)); //访问前驱结点
    visit(NextNode(leftChild)); //访问后继结点

    return 0;
}

