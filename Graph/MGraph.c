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
int path[MAXSIZE]; //存储路径
int dist[MAXSIZE]; //存储最短路径长度

//定义队列结构
typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int front;
    int rear;
} SqQueue;

//定义栈结构
typedef struct{
    ElemType data[MAXSIZE];
    int top; 
}SqStack;



//初始化栈
void InitStack(SqStack *s){
    s->top = -1; 
}


//入栈
bool Push(SqStack *s, ElemType e){
    if(s->top >= MAXSIZE - 1){
        printf("栈已满，无法入栈");
        return false;
    }
    s->top = s->top + 1;
    s->data[s->top] = e;
    return true;
}

//出栈
bool Pop(SqStack *s){
    if(s->top == -1){
        printf("栈空，无法出栈");
        return false;
    }
    s->top = s->top - 1;
    return true;
}
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

//访问顶点函数
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

    // 初始化路径和最短路径长度数组
    for (int i = 0; i < MAXSIZE; i++) {
        path[i] = -1; // -1表示未访问
        dist[i] = MAXSIZE; // 初始化为最大值
    }
}

//图的广度优先遍历
void BFS(MGraph *G, int v){
    SqQueue q;
    InitQueue(&q);
    EnQueue(&q, v);
    visited[v] = true;
    while (q.front != q.rear){
        visit(G->Vex[v]);
        DeQueue(&q);
        
        for (int i = 0; i < G->vernum; i++){
            if (G->Edge[v][i] != 0 && visited[i] == false){
                EnQueue(&q, i);
                visited[i] = true;
            }
        }
        v = q.data[q.front];
    }
}

//图的深度优先遍历
void DFS(MGraph *G, int v){
    SqStack s;
    InitStack(&s);
    Push(&s, v);
    visited[v] = true;
    while (s.top != -1){
        visit(G->Vex[v]);
        Pop(&s);

        for (int i = 0; i < G->vernum; i++){
            if (G->Edge[v][i] != 0 && visited[i] == false){
                Push(&s, i);
                visited[i] = true;
            }
        }
        v = s.data[s.top]; 
    }
}

//广度优先遍历求顶点v到各个顶点的最短路径
void BFS_min_distance(MGraph *G, int v){
    SqQueue q;
    InitQueue(&q);
    EnQueue(&q, v);
    dist[v] = 0; 
    visited[v] = true;
    while (q.front != q.rear){
        DeQueue(&q);
        
        for (int i = 0; i < G->vernum; i++){
            if (G->Edge[v][i] != 0 && visited[i] == false){
                dist[i] = dist[v] + 1;
                path[i] = v;
                EnQueue(&q, i);
                visited[i] = true;
            }
        }
        v = q.data[q.front];
    }
}

void print(MGraph *G, int path[], int dist[]){
    for(int i = 0; i < G->vernum; i++){
        printf("%d ", path[i]);
    }
    printf("\n");
    for(int i = 0; i < G->vernum; i++){
        printf("%d ", dist[i]);
    }
}

int main(){
    MGraph G;
    InitGraph(&G);

    printf("广度优先遍历的顶点序列：");
    BFS(&G, 1); 
    printf("\n");

    for (int i = 0; i < MAXSIZE; i++){
        visited[i] = false; // 重置访问标志数组
    }

    printf("深度优先遍历的顶点序列：");
    DFS(&G, 1);
    printf("\n");

    for (int i = 0; i < MAXSIZE; i++){
        visited[i] = false; // 重置访问标志数组
    }

    printf("各个顶点的前缀和从顶点1到各个顶点的最短长度：\n");
    BFS_min_distance(&G, 1);
    print(&G, path, dist);
    printf("\n");
    return 0;
}