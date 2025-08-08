#include <stdio.h>
#include <stdlib.h>

//定义平衡二叉树结点结构
typedef struct AVLNode{
    int key;
    int height;
    struct AVLNode *lchild, *rchild;
} AVLNode;

//获取结点高度
int GetHeight(AVLNode *node){
    if (node == NULL){
        return 0;
    }
    return node->height;
}

//计算平衡因子
int GetBalanceFactor(AVLNode *node){
    if (node == NULL){
        return 0;
    }
    return GetHeight(node->lchild) - GetHeight(node->rchild);
}

//更新结点高度
void UpdateHeight(AVLNode *node){
    int leftHeight = GetHeight(node->lchild);
    int rightHeight = GetHeight(node->rchild);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

//右旋
AVLNode *RightRotate(AVLNode *y){
    AVLNode *x = y->lchild;
    AVLNode *T2 = x->rchild;

    //执行旋转
    x->rchild = y;
    y->lchild = T2;

    //更新高度
    UpdateHeight(y);
    UpdateHeight(x);

    return x;
}

//左旋
AVLNode *LeftRotate(AVLNode *x){
    AVLNode *y = x->rchild;
    AVLNode *T2 = y->lchild;
 
    y->lchild = x;
    x->rchild = T2;

    UpdateHeight(x);
    UpdateHeight(y);

    return y;
}

//平衡操作
AVLNode *Balance(AVLNode *node){
    if (node == NULL){
        return node;
    }

    //更新当前结点高度
    UpdateHeight(node);

    //获取平衡因子
    int balance = GetBalanceFactor(node);

    if (balance > 1 && GetBalanceFactor(node->lchild) >= 0){
        return RightRotate(node);
    }

    if (balance < -1 && GetBalanceFactor(node->rchild) <= 0){
        return LeftRotate(node);
    }

    if (balance > 1 && GetBalanceFactor(node->lchild) < 0){
        node->lchild = LeftRotate(node->lchild);
        return RightRotate(node);
    }

    if (balance < -1 && GetBalanceFactor(node->rchild) > 0){
        node->rchild = RightRotate(node->rchild);
        return LeftRotate(node);
    }
    return node;
}

//插入
AVLNode *AVL_Insert(AVLNode *node, int key){
    if (node == NULL){
        AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
        newNode->key = key;
        newNode->height = 1;
        newNode->lchild = newNode->rchild = NULL;
        return newNode;
    }

    if (key < node->key)
        node->lchild = AVL_Insert(node->lchild, key);
    else if (key > node->key)
        node->rchild = AVL_Insert(node->rchild, key);
    else
        return node;

    return Balance(node);
}

//查找最小结点
AVLNode *FindMin(AVLNode *node){
    while (node != NULL && node->lchild != NULL){
        node = node->lchild;
    }
    return node;
}

//删除
AVLNode *AVL_Delete(AVLNode *root, int key){
    if (root == NULL){
        return root;
    }

    if (key < root->key)
        root->lchild = AVL_Delete(root->lchild, key);
    else if (key > root->key)
        root->rchild = AVL_Delete(root->rchild, key);
    else{
        // 找到要删除的结点
        if (root->lchild == NULL || root->rchild == NULL){
            // 有一个或没有子结点
            AVLNode *temp = root->lchild ? root->lchild : root->rchild;

            if (temp == NULL){
                // 没有子结点
                temp = root;
                root = NULL;
            } 
            else{
                // 有一个子结点
                *root = *temp; // 复制子结点内容
            }
        } 
        else{
            // 有两个子结点，找到后继结点
            AVLNode *temp = FindMin(root->rchild);
            root->key = temp->key;
            root->rchild = AVL_Delete(root->rchild, temp->key);
        }
    }

    if (root == NULL){
        return root;
    }

    return Balance(root);
}

//中序遍历
void InOrderTraverse(AVLNode *T){
    if (T != NULL){
        InOrderTraverse(T->lchild);
        printf("%d ", T->key);
        InOrderTraverse(T->rchild);
    }
}

int main(){
    AVLNode *T = NULL;
    int A[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(A) / sizeof(A[0]);

    for (int i = 0; i < n; i++) {
        T = AVL_Insert(T, A[i]);
    }

    printf("中序遍历结果: ");
    InOrderTraverse(T);
    printf("\n");
    
    //插入
    T = AVL_Insert(T, 15);
    printf("插入后的中序遍历: ");
    InOrderTraverse(T);
    printf("\n");
    
    //删除
    T = AVL_Delete(T, 20);
    printf("删除后的中序遍历: ");
    InOrderTraverse(T);
    printf("\n");
    
    return 0;
}