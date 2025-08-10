#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 

//链表节点结构
typedef struct HashNode{
    int key;
    int value;
    struct HashNode* next;
}HashNode;

//散列表结构
typedef struct{
    HashNode** buckets; //桶数组
    int size; 
}HashTable;

//创建散列表
HashTable* createHashTable(int size){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (HashNode**)calloc(size, sizeof(HashNode*));
    return table;
}

//散列函数（简单取模法）
int hashFunction(int key, int size){
    return key % size;
}

//查找
HashNode* search(HashTable* table, int key){
    int index = hashFunction(key, table->size);
    HashNode* current = table->buckets[index];
    
    while (current != NULL){
        if (current->key == key){
            return current;
        }
        current = current->next;
    }
    
    return NULL; 
}

//插入
void insert(HashTable* table, int key, int value){
    int index = hashFunction(key, table->size);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    
    //如果桶为空，直接插入
    if (table->buckets[index] == NULL)
        table->buckets[index] = newNode;
    else
        //插入到链表头部
        newNode->next = table->buckets[index];
        table->buckets[index] = newNode;
}

//删除
int delete(HashTable* table, int key){
    int index = hashFunction(key, table->size);
    HashNode* current = table->buckets[index];
    HashNode* prev = NULL;
    
    while (current != NULL){
        if (current->key == key){
            if (prev == NULL)
                // 删除的是链表头节点
                table->buckets[index] = current->next;
            else
                prev->next = current->next;
            free(current);
            return 1; 
        }
        prev = current;
        current = current->next;
    }
    
    return 0; 
}

//打印散列表
void printHashTable(HashTable* table){
    for (int i = 0; i < table->size; i++){
        printf("Bucket[%d]: ", i);
        HashNode* current = table->buckets[i];
        while (current != NULL){
            printf("(%d, %d) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

int main(){
    HashTable* table = createHashTable(TABLE_SIZE);
    
    //插入
    insert(table, 1, 100);
    insert(table, 2, 200);
    insert(table, 11, 1100); 
    insert(table, 12, 1200); 
    
    //打印
    printf("初始散列表:\n");
    printHashTable(table);
    
    //查找
    int searchKey = 11;
    HashNode* result = search(table, searchKey);
    if (result != NULL) {
        printf("键的值为 %d\n", result->value);
    } else {
        printf("未找到键\n");
    }
    
    //删除
    int deleteKey = 2;
    if (delete(table, deleteKey)) {
        printf("删除键 %d 成功\n", deleteKey);
    } else {
        printf("删除键 %d 失败\n", deleteKey);
    }
    
    //打印删除后的散列表
    printf("删除后的散列表:\n");
    printHashTable(table);

    
    return 0;
}