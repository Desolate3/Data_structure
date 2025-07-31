#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef char VertexType;
typedef int EdgeType;

// //图的邻接表表示
// typedef struct ArcNode {
//     int adjvex; //邻接点位置
//     struct ArcNode *nextarc; //指向下一个邻接点
// } ArcNode;

// typedef struct VNode {
//     VertexType data; //顶点信息
//     ArcNode *firstarc; //指向第一个邻接点
// } VNode;

// typedef struct ALGraph {
//     VNode adjlist[MAXSIZE]; //邻接表数组
//     int vernum, arcnum; //顶点数和边数
// } ALGraph;

//图的邻接矩阵表示
typedef struct MGraph {
    VertexType Vex[MAXSIZE]; //顶点数组
    EdgeType Edge[MAXSIZE][MAXSIZE]; //邻接矩阵
    int vernum, arcnum; //顶点数和边数
} MGraph;

bool visited[MAXSIZE]; //访问标志数组

//定义队列结构
typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int front;
    int rear;
} SqQueue;

//初始化队列
void InitQueue(SqQueue *q) {
    q->front = 0;
    q->rear = 0;
}

//入队
bool EnQueue(SqQueue *q, ElemType e) {
    if ((q->rear + 1) % MAXSIZE == q->front) {
        printf("队列已满，无法入队");
        return false;
    }
    q->data[q->rear] = e;
    q->rear = (q->rear + 1) % MAXSIZE;
    return true;
}

//出队
bool DeQueue(SqQueue *q){
    if(q->front == q->rear){
        printf("队列为空，无法出队");
        return false;
    }
    q->front = (q->front + 1) % MAXSIZE;
    return true;
}

void visit(VertexType v) {
    printf("%c ", v);
}

// 初始化图函数
void InitGraph(MGraph *G) {
    // 初始化顶点数和边数
    G->vernum = 5;
    G->arcnum = 6;
    
    // 初始化顶点数组
    G->Vex[0] = 'A';
    G->Vex[1] = 'B';
    G->Vex[2] = 'C';
    G->Vex[3] = 'D';
    G->Vex[4] = 'E';
    
    // 初始化邻接矩阵（全部设为0，表示无边）
    for (int i = 0; i < G->vernum; i++) {
        for (int j = 0; j < G->vernum; j++) {
            G->Edge[i][j] = 0;
        }
    }
    
    // 设置边（无向图，对称矩阵）
    // // 边 A-B
    // G->Edge[0][1] = 1;
    // G->Edge[1][0] = 1;
    
    // 边 A-C
    G->Edge[0][2] = 1;
    G->Edge[2][0] = 1;
    
    // 边 B-C
    G->Edge[1][2] = 1;
    G->Edge[2][1] = 1;
    
    // 边 B-D
    G->Edge[1][3] = 1;
    G->Edge[3][1] = 1;
    
    // 边 B-E
    G->Edge[1][4] = 1;
    G->Edge[4][1] = 1;
    
    // 边 C-D
    G->Edge[2][3] = 1;
    G->Edge[3][2] = 1;
    
    // 边 D-E
    G->Edge[3][4] = 1;
    G->Edge[4][3] = 1;
    
    // 初始化访问标志数组
    for (int i = 0; i < MAXSIZE; i++) {
        visited[i] = false;
    }
}

//图的广度优先遍历
void BFS(MGraph *G, int v){
    SqQueue q;
    InitQueue(&q);
    EnQueue(&q, v);
    visited[v] = true;
    while (q.front != q.rear) {
        visit(G->Vex[v]);
        DeQueue(&q);
        
        
        for (int i = 0; i < G->vernum; i++) {
            if (G->Edge[v][i] != 0 && visited[i] == false) {
                EnQueue(&q, i);
                visited[i] = true;
            }
        }
        v = q.data[q.front];
    }
}

int main(){
    MGraph G;
    InitGraph(&G);
    BFS(&G, 0); 
    return 0;
}