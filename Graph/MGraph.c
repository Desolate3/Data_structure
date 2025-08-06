#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100
#define INFINITY 65535 // 表示无穷大

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
int Path[MAXSIZE][MAXSIZE]; //存储路径矩阵

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

// 新添加的拓扑排序相关数据结构
int indegree[MAXSIZE]; // 存储每个顶点的入度
int print[MAXSIZE];    // 存储拓扑排序结果

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
bool Pop(SqStack *s, ElemType *e){ // 修改了Pop函数，使其能返回栈顶元素
    if(s->top == -1){
        printf("栈空，无法出栈");
        return false;
    }
    *e = s->data[s->top];
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
bool DeQueue(SqQueue *q, ElemType *e){ // 修改了DeQueue函数，使其能返回队头元素
    if(q->front == q->rear){
        printf("队列为空，无法出队");
        return false;
    }
    *e = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return true;
}

//访问顶点函数
void visit(VertexType v) {
    printf("%c ", v);
}

// 初始化图函数 - 修改为有向图
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
    
    // 初始化邻接矩阵（全部设为INFINITY，表示无边）
    for (int i = 0; i < G->vernum; i++) {
        for (int j = 0; j < G->vernum; j++) {
            G->Edge[i][j] = INFINITY;
        }
        G->Edge[i][i] = 0; // 对角线设为0
    }
    
    // 初始化入度数组
    for (int i = 0; i < G->vernum; i++) {
        indegree[i] = 0;
    }
    
    // 设置边（有向图）
    // A->C
    G->Edge[0][2] = 1;
    indegree[2]++;
    
    // B->A
    G->Edge[1][0] = 1;
    indegree[0]++;
    
    // B->C
    G->Edge[1][2] = 1;
    indegree[2]++;
    
    // B->D
    G->Edge[1][3] = 1;
    indegree[3]++;
    
    // C->D
    G->Edge[2][3] = 1;
    indegree[3]++;
    
    // D->E
    G->Edge[3][4] = 1;
    indegree[4]++;

    // 初始化访问标志数组
    for (int i = 0; i < MAXSIZE; i++) {
        visited[i] = false;
    }

    // 初始化路径和最短路径长度数组
    for (int i = 0; i < MAXSIZE; i++) {
        path[i] = -1;
        dist[i] = INFINITY;
    }
    
    // 初始化路径矩阵
    for (int i = 0; i < MAXSIZE; i++) {
        for (int j = 0; j < MAXSIZE; j++) {
            Path[i][j] = -1;
        }
    }
}

// 拓扑排序
bool TopologicalSort(MGraph G) {
    SqStack S;
    InitStack(&S);
    int count = 0;
    
    // 将所有入度为0的顶点入栈
    for (int i = 0; i < G.vernum; i++) {
        if (indegree[i] == 0) {
            Push(&S, i);
        }
    }
    
    while (S.top != -1) {
        int v;
        Pop(&S, &v);
        print[count++] = v; // 记录拓扑序列
        
        //遍历v的所有邻接点
        for (int w = 0; w < G.vernum; w++) {
            if (G.Edge[v][w] != INFINITY) { 
                if (--indegree[w] == 0) {   
                    Push(&S, w);
                }
            }
        }
    }
    
    if (count < G.vernum) {
        return false;
    } else {
        return true; 
    }
}

//图的广度优先遍历
void BFS(MGraph *G, int v){
    SqQueue q;
    InitQueue(&q);
    visit(G->Vex[v]);
    visited[v] = true;
    EnQueue(&q, v);
    
    while (q.front != q.rear){
        int u;
        DeQueue(&q, &u);
        
        for (int i = 0; i < G->vernum; i++){
            if (G->Edge[u][i] != INFINITY && !visited[i]){
                visit(G->Vex[i]);
                visited[i] = true;
                EnQueue(&q, i);
            }
        }
        v = q.data[q.front];
    }
}

//图的深度优先遍历
void DFS(MGraph *G, int v){
    visit(G->Vex[v]);
    visited[v] = true;
    
    for (int i = 0; i < G->vernum; i++){
        if (G->Edge[v][i] != INFINITY && !visited[i]){
            DFS(G, i);
        }
    }
}

//广度优先遍历求顶点v到各个顶点的最短路径
void BFS_min_distance(MGraph *G, int v){
    SqQueue q;
    InitQueue(&q);
    
    for (int i = 0; i < G->vernum; i++) {
        dist[i] = INFINITY;
        path[i] = -1;
    }
    
    dist[v] = 0;
    visited[v] = true;
    EnQueue(&q, v);
    
    while (q.front != q.rear){
        int u;
        DeQueue(&q, &u);
        
        for (int i = 0; i < G->vernum; i++){
            if (G->Edge[u][i] != INFINITY && !visited[i]){
                dist[i] = dist[u] + 1;
                path[i] = u;
                visited[i] = true;
                EnQueue(&q, i);
            }
        }
        v = q.data[q.front];
    }
}

//打印路径和最短路径长度
void printPathAndDist(MGraph *G, int path[], int dist[]){
    printf("前驱顶点: ");
    for(int i = 0; i < G->vernum; i++){
        printf("%d ", path[i]);
    }
    printf("\n最短距离: ");
    for(int i = 0; i < G->vernum; i++){
        printf("%d ", dist[i]);
    }
    printf("\n");
}

void Floyd(MGraph *G) {
    //初始化路径矩阵
    for(int i = 0; i < G->vernum; i++) {
        for(int j = 0; j < G->vernum; j++) {
            Path[i][j] = -1;
            if (G->Edge[i][j] < INFINITY && i != j) {
                Path[i][j] = i;
            }
        }
    }
    
    for(int k = 0; k < G->vernum; k++) {
        for(int i = 0; i < G->vernum; i++) {
            for(int j = 0; j < G->vernum; j++) {
                if(G->Edge[i][k] + G->Edge[k][j] < G->Edge[i][j]) {
                    G->Edge[i][j] = G->Edge[i][k] + G->Edge[k][j];
                    Path[i][j] = Path[k][j];
                }
            }
        }
    }
    
    printf("Floyd算法计算后的最短路径矩阵:\n");
    for(int i = 0; i < G->vernum; i++) {
        for(int j = 0; j < G->vernum; j++) {
            if (G->Edge[i][j] == INFINITY) {
                printf("INF ");
            } else {
                printf("%3d ", G->Edge[i][j]);
            }
        }
        printf("\n");
    }
}

int main(){
    MGraph G;
    InitGraph(&G);

    printf("广度优先遍历的顶点序列：");
    BFS(&G, 1); 
    printf("\n");

    for (int i = 0; i < MAXSIZE; i++){
        visited[i] = false;
    }

    printf("深度优先遍历的顶点序列：");
    DFS(&G, 1);
    printf("\n");

    for (int i = 0; i < MAXSIZE; i++){
        visited[i] = false;
    }

    printf("各个顶点的前缀和从顶点1到各个顶点的最短长度：\n");
    BFS_min_distance(&G, 1);
    printPathAndDist(&G, path, dist);
    printf("\n");

    Floyd(&G);
    
    printf("\n");

    for (int i = 0; i < MAXSIZE; i++) {
        visited[i] = false;
    }
    
    printf("拓扑排序结果：");
    if (TopologicalSort(G)) {
        for (int i = 0; i < G.vernum; i++) {
            printf("%c ", G.Vex[print[i]]);
        }
        printf("\n");
    } else {
        printf("图中存在环，无法进行拓扑排序!\n");
    }
    
    return 0;
}