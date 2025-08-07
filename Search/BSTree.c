#include <stdio.h>
#include <stdlib.h>

//定义二叉排序树
typedef struct BSTNode{
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode;

//查找
BSTNode *BST_Search(BSTNode *T, int key){
    while (T != NULL && key != T->key){
        if (key < T->key)
            T = T->lchild;  
        else
            T = T->rchild;  
    }
    return T;  
}

//插入操作
int BST_Insert(BSTNode **T, int k){
    if (*T == NULL){
        *T = (BSTNode *)malloc(sizeof(BSTNode));
        (*T)->key = k;
        (*T)->lchild = (*T)->rchild = NULL;
        return 1; 
    } 
    else if (k == (*T)->key){
        //已存在相同关键字
        return 0;  
    } 
    else if (k < (*T)->key){
        return BST_Insert(&(*T)->lchild, k); 
    } 
    else{
        return BST_Insert(&(*T)->rchild, k);  
    }
}

//创建二叉排序树
void Create_BST(BSTNode **T, int str[], int n) {
    *T = NULL; 
    for (int i = 0; i < n; i++) {
        BST_Insert(T, str[i]);
    }
}

//查找最小结点
BSTNode *FindMin(BSTNode *T){
    while (T != NULL && T->lchild != NULL){
        T = T->lchild;
    }
    return T;
}

//删除操作
int BST_Delete(BSTNode **T, int key){
    if (*T == NULL){
        return 0; 
    }
    if (key < (*T)->key)
        return BST_Delete(&(*T)->lchild, key);  
    else if (key > (*T)->key)
        return BST_Delete(&(*T)->rchild, key);  
    else{
        // 找到要删除的结点
        BSTNode *temp;
        
        //叶子结点或只有一个子结点
        if ((*T)->lchild == NULL){
            temp = *T;
            *T = (*T)->rchild;
            free(temp);
        } 
        else if ((*T)->rchild == NULL){
            temp = *T;
            *T = (*T)->lchild;
            free(temp);
        } 
        else{
            //有两个子结点
            //找到右子树的最小结点
            temp = FindMin((*T)->rchild);
            //后继结点的值替换当前结点
            (*T)->key = temp->key;  
            BST_Delete(&(*T)->rchild, temp->key);  
        }
        return 1; 
    }
}

//中序遍历
void InOrderTraverse(BSTNode *T){
    if (T != NULL){
        InOrderTraverse(T->lchild);
        printf("%d ", T->key);
        InOrderTraverse(T->rchild);
    }
}

int main(){
    BSTNode *T = NULL;
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Create_BST(&T, arr, n);

    InOrderTraverse(T);
    printf("\n");
    
    int searchKey = 40;
    BSTNode *result = BST_Search(T, searchKey);
    
    //插入操作
    int insertKey = 35;
    if (BST_Insert(&T, insertKey))
        printf("插入成功\n");
    else
        printf("插入失败\n");
    
    
    printf("插入后的中序遍历结果: ");
    InOrderTraverse(T);
    printf("\n");
    
    //删除操作
    int deleteKey = 30;
    if (BST_Delete(&T, deleteKey))
        printf("删除成功\n");
    else
        printf("删除失败\n");
    
    
    printf("删除后的中序遍历结果: ");
    InOrderTraverse(T);
    printf("\n");
    
    return 0;
}