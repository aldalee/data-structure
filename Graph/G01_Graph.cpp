/**
 * Created by lhy on 2021/4/9 9:46
 * Description:
 */
#include <iostream>
#include "memory.h"
#include <vector>
#define maxSize 100
#define INF 100000000
#define length(arr) sizeof(arr) / sizeof(arr[0])
using namespace std;

struct MGraph {                  // 图的邻接矩阵
    int edges[maxSize][maxSize];
    int n, e;
    char vex[maxSize];    // 存放顶点信息
};
struct ArcNode {                 // 边结点
    int adjVex;                 // 该边所指向的结点的位置
    ArcNode *nextArc;           // 指向下一条边的指针
    int info;                   // 该边的相关信息，如权值
};
struct VNode {
    char data;                  // 顶点信息
    int inDegree;                  // 统计顶点当前的入度
    ArcNode *firstArc;          // 指向第一条边的指针
};
struct ALGraph {
    VNode adjList[maxSize];     // 邻接表
    int n, e;                    // 顶点数和边数
};
struct Edge {                    // 边的存储结构
    int start, end;              // 起始 结束
    int weight;                 // 权值
};

void Visit(ALGraph *G, int i);

int locateVex(ALGraph *G, char vex);

int locateVex(MGraph *G, char vex);

void initVisit();

void quickSort(Edge edge[], int low, int high);

void selectSort(Edge edge[], int e);


/**
* 基于邻接矩阵的存储结构构造无向图
* @param G
* @param n     顶点数
* @param e     边数
* @param vex   顶点集合
* @param edges 边集合+权值
* @return
*/
bool createUnDiGraph(MGraph *G, int n, int e, const char vex[], char edges[][3]) {
    G->n = n;
    G->e = e;
    for (int i = 0; i < n; ++i) {
        G->vex[i] = vex[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                G->edges[i][j] = 0;
            else
                G->edges[i][j] = INF;
        }
    }
    int i, j;
    for (int k = 0; k < e; ++k) {
        i = locateVex(G, edges[k][0]);
        j = locateVex(G, edges[k][1]);
        G->edges[i][j] = edges[k][2];
        G->edges[j][i] = edges[k][2];
    }
    return true;
}

/**
 * 基于邻接表的存储结构构造无向图
 * @param G
 * @param n     顶点数
 * @param e     边数
 * @param vex   顶点集合
 * @param edges 边集合+权值
 * @return
 */
bool createUnDiGraph(ALGraph *G, int n, int e, const char vex[], char edges[][3]) {
    G->n = n;
    G->e = e;
    for (int i = 0; i < n; ++i) {
        G->adjList[i].data = vex[i];
        G->adjList[i].firstArc = nullptr;
    }
    for (int k = 0; k < e; ++k) {
        int i = locateVex(G, edges[k][0]);
        int j = locateVex(G, edges[k][1]);
        auto *p1 = new ArcNode;
        p1->adjVex = j;
        p1->nextArc = G->adjList[i].firstArc;
        G->adjList[i].firstArc = p1;
        p1->info = edges[k][2];
        auto *p2 = new ArcNode;
        p2->adjVex = i;
        p2->nextArc = G->adjList[j].firstArc;
        G->adjList[j].firstArc = p2;
    }
    return true;
}
/**
* 基于邻接矩阵的存储结构构造有向图
* @param G
* @param n     顶点数
* @param e     边数
* @param vex   顶点集合
* @param edges 边集合+权值
* @return
*/
bool createDiGraph(MGraph *G, int n, int e, const char vex[], char edges[][3]) {
    G->n = n;
    G->e = e;
    for (int i = 0; i < n; ++i) {
        G->vex[i] = vex[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                G->edges[i][j] = 0;
            else
                G->edges[i][j] = INF;
        }
    }
    int i, j;
    for (int k = 0; k < e; ++k) {
        i = locateVex(G, edges[k][0]);
        j = locateVex(G, edges[k][1]);
        G->edges[i][j] = edges[k][2];
    }
    return true;
}
/**
 * 基于邻接表的存储结构构造有向图
 * @param G
 * @param n     顶点数
 * @param e     边数
 * @param vex   顶点集合
 * @param edges 边集合
 * @return
 */
bool createDiGraph(ALGraph *G, int n, int e, const char vex[], char edges[][3]) {
    G->n = n;
    G->e = e;
    int inDegree = 0;      // 记录当前顶点的入度
    for (int i = 0; i < n; ++i) {
        G->adjList[i].data = vex[i];
        G->adjList[i].firstArc = nullptr;
        for (int j = 0; j < e; ++j) {
            if (vex[i] == edges[j][1])
                inDegree++;
        }
        G->adjList[i].inDegree = inDegree;
        inDegree = 0;
    }
    int i, j;
    for (int k = 0; k < e; ++k) {
        i = locateVex(G, edges[k][0]);
        j = locateVex(G, edges[k][1]);
        auto *p = new ArcNode;
        p->adjVex = j;
        p->nextArc = G->adjList[i].firstArc;
        G->adjList[i].firstArc = p;
        p->info = edges[k][2];
    }
    return true;
}

void printAdjacencyMatrix(MGraph *G) {
    cout << "i\\j";
    for (int i = 0; i < G->n; ++i) {
        cout << "\t" << G->vex[i];
    }
    cout << endl;
    for (int i = 0; i < G->n; ++i) {
        cout << G->vex[i] << "\t";
        for (int j = 0; j < G->n; ++j) {
            if (G->edges[i][j] == INF)
                cout << "∞" << "\t";
            else
                cout << G->edges[i][j] << "\t";
        }
        cout << endl;
    }
}

/**
 * 打印图的邻接表
 * @param G
 */
void printAdjacencyList(ALGraph *G) {
    cout << "index" << "\t" << "vex" << endl;
    for (int i = 0; i < G->n; i++) {
        cout << "  " << i << "\t " << G->adjList[i].data << "\t";
        ArcNode *p = G->adjList[i].firstArc;
        while (p) {
            cout << p->adjVex << "\t";
            p = p->nextArc;
        }
        cout << endl;
    }
}

/**
 * 获取G中边<start, end>的权值；若start和end不是连通的，则返回无穷大
 * @param G 邻接表图
 * @param start
 * @param end
 * @return
 */
int getWeight(ALGraph *G, int start, int end) {
    ArcNode *p;
    if (start == end)
        return 0;
    p = G->adjList[start].firstArc;
    while (p) {
        if (end == p->adjVex)
            return p->info;
        p = p->nextArc;
    }
    return INF;
}


static int vexSet[maxSize];                  // 定义并查集数组
int getRoot(int p) {
    while (p != vexSet[p])
        p = vexSet[p];
    return p;
}
int Kruskal(Edge edge[], int n, int e) {
    int start, end;
    int sum = 0;
    for (int i = 0; i < n; ++i)
        vexSet[i] = i;
    selectSort(edge, e);
    for (int i = 0; i < e; ++i) {
        start = getRoot(edge[i].start);
        end = getRoot(edge[i].end);
        if (start != end) {
            vexSet[start] = end;
            sum += edge[i].weight;
        }
    }
    return sum;
}

void selectSort(Edge edge[], int e) {
    int k;
    Edge temp{};
    for (int i = 0; i < e; ++i) {
        k = i;
        for (int j = i + 1; j < e; ++j) {
            if (edge[k].weight > edge[j].weight)
                k = j;
        }
        temp = edge[i];
        edge[i] = edge[k];
        edge[k] = temp;
    }
}

/** 有问题，以后再调
 * 对edge[]数组中的 e 条边按照权值weight进行升序
 * @param edge
 * @param low 0
 * @param high e
 */
void quickSort(Edge edge[], int low, int high) {
    Edge temp{};
    int i = low, j = high;
    if (low < high) {
        temp = edge[low];
        while (i < j) {
            while (j > i && edge[j].weight >= temp.weight)
                --j;
            if (i < j)
                edge[i++] = edge[j];
            while (i < j && edge[i].weight < temp.weight)
                ++i;
            if (i < j)
                edge[j--] = edge[i];
        }
        edge[i] = temp;
        quickSort(edge, low, i - 1);
        quickSort(edge, i + 1, high);
    }
}

/**
 * 以邻接表为存储结构的图深度优先遍历算法
 * @param v 遍历的起始点
 * @param G 邻接表图
 */
static int visit[maxSize];

void DFS(ALGraph *G, int v) {
    visit[v] = 1;       // 置已访问标记
    Visit(G, v);
    ArcNode *q = G->adjList[v].firstArc;
    while (q != nullptr) {
        if (visit[q->adjVex] == 0)
            DFS(G, q->adjVex);
        q = q->nextArc;
    }
}

/**
 * 以邻接表为存储结构的图广度优先遍历算法
 * @param G 邻接表图
 * @param v 遍历的起始点
 */
void BFS(ALGraph *G, int v) {
    initVisit();
    ArcNode *p;
    int que[maxSize];                               // 定义队列
    int front = 0, rear = 0;
    int j;
    Visit(G, v);                                       // 任意访问顶点v的函数
    visit[v] = 1;
    rear = (rear + 1) % maxSize;                      // 当前顶点v进队
    que[rear] = v;
    while (front != rear) {                          // 队空的时候遍历完成
        front = (front + 1) % maxSize;                // 顶点出队
        j = que[front];
        p = G->adjList[j].firstArc;                 // p指向出队顶点 j 的第一条边
        while (p != nullptr) {                       // 将 p 的所有邻接点中未被访问的入队
            if (visit[p->adjVex] == 0) {          //当前邻接顶点未被访问，则入队
                Visit(G, p->adjVex);
                visit[p->adjVex] = 1;
                rear = (rear + 1) % maxSize;          // 该顶点入队
                que[rear] = p->adjVex;
            }
            p = p->nextArc;
        }
    }
    initVisit();
}

/**
 * 以无向图的邻接矩阵为存储结构的 Prim最小生成树算法
 * @param G 邻接矩阵
 * @param v0 开始结点
 * @param sum 生成树的权值
 * @return
 */
int Prim(MGraph *G, int v0) {
    int lowCost[maxSize];
    int vSet[maxSize];
    int i, j, v, k = 0;
    int min;
    for (i = 0; i < G->n; ++i) {
        lowCost[i] = G->edges[v0][i];
        vSet[i] = 0;
    }
    vSet[v0] = 1;   // 将v0并入树中
    int sum = 0;
    for (i = 0; i < G->n - 1; ++i) {
        min = INF;
        for (j = 0; j < G->n; ++j) {    // 选出候选边中的最小值
            if (vSet[j] == 0 && lowCost[j] < min) {
                min = lowCost[j];
                k = j;
            }
        }
        vSet[k] = 1;
        v = k;
        sum += min;
        for (j = 0; j < G->n; ++j) {    // 以刚并入的顶点v为媒介更新侯选边
            if (vSet[j] == 0 && G->edges[v][j] < lowCost[j])
                lowCost[j] = G->edges[v][j];
        }
    }
    return sum;
}

/**
 * Dijkstra算法 求图中某一顶点到其余各顶点的最短路径
 * @param graph 以邻接矩阵存储的图
 * @param v     源点
 * @param dist 存放 v 点到其余顶点的最短路径长度
 * @param path 存放 v 点到其余各顶点的最短路径
 */
void Dijkstra(MGraph *graph,int v, int dist[],int path[]){
    if (v >= graph->n){
        cout << "Error input "<< v << endl;
        return;
    }
    int set[maxSize];
    int min, u = 0;
    for (int i = 0; i < graph->n; ++i) {
        dist[i] = graph->edges[v][i];
        set[i] = 0;
        if (graph->edges[v][i] < INF)
            path[i] = v;
        else
            path[i] = -1;
    }
    set[v] = 1;
    path[v] = -1;
    for (int i = 0; i < graph->n-1; ++i) {
        min = INF;
        /*每次从剩余顶点中选出一个顶点，通过这个顶点的路径在通往所有剩余顶点的路径中最短的*/
        for (int j = 0; j < graph->n; ++j) {
            if (set[j] == 0 && dist[j] < min){
                u = j;
                min = dist[j];
            }
        }
        set[u] = 1;     // 将选出的点并入最短路径中
        /*以刚并入的顶点为中间点，对通往剩余顶点的路径进行检测*/
        for (int j = 0; j < graph->n; ++j) {
            /*判断顶点u的加入是否会出现通往顶点j的更短的路径，出现则更新原来的路径及长度，否则什么都不做*/
            if (set[j] == 0 && dist[u] + graph->edges[u][j] < dist[j]){
                dist[j] = dist[u] + graph->edges[u][j];
                path[j] = u;
            }
        }
    }
}

/**
 * 打印从源点到任何一个顶点最短路径上所经过的所有顶点
 * @param path 以双亲存储结构存储的树
 * @param v path[]中的某一个值
 * @param vex 图的顶点数组
 */
void printfPath(const int path[],int v, char vex[]){
    int stack[maxSize],top=-1;
    /*以叶子结点到根节点的顺序将其入栈*/
    while (path[v] != -1){
        stack[++top] = v;
        v = path[v];
    }
    stack[++top] = v;
    cout << vex[stack[top--]];
    while (top != -1){
        cout <<"->"<< vex[stack[top--]];
    }
}
/**
 * 打印从指定源点到全部顶点最短路径上所经过的所有顶点，以及path[]和dist[]
 * @param graph
 * @param vex
 * @param i     指定源点
 * @param path
 * @param dist
 */
void printfAllPath(MGraph *graph, char vex[],int i,int path[],int dist[]){
    if (i >= graph->n){
        cout << "Error input "<< i << endl;
        return;
    }
    cout << "dist: ";
    for (int j = 0; j < graph->n; ++j) {
        if (dist[j] != INF)
            cout << dist[j] << " ";
        else
            cout << "∞ ";
    }
    cout << "\npath: ";
    for (int j = 0; j < graph->n; ++j) {
        cout << path[j] << " ";
    }
    cout <<endl;
    for (int j = 0; j < graph->n ; ++j) {
        if (dist[j] != INF){
            printf("顶点%c到顶点%c的最短路径为：",vex[i],vex[j]);
            printfPath(path,j,vex);
            printf("\t路径长度为：%d\n",dist[j]);
        } else{
            printf("顶点%c到顶点%c的最短路径为:\t",vex[i],vex[j]);
            printf("\t路径长度为：∞\n");
        }
    }
}
/**
 * Floyd算法  求图中任意一顶点到其余各顶点的最短路径
 * @param graph
 * @param path
 * @param A
 */
void Floyd(MGraph *graph,int path[][maxSize],int A[][maxSize]){
    /*对path[] A[][]初始化*/
    for (int i = 0; i < graph->n; ++i) {
        for (int j = 0; j < graph->n; ++j) {
            A[i][j] = graph->edges[i][j];
            path[i][j] = -1;
        }
    }
    /*以v为中间点对所有的顶点对(i,j)进行检测和修改*/
    for (int v = 0; v < graph->n; ++v) {
        for (int i = 0; i < graph->n; ++i) {
            for (int j = 0; j < graph->n; ++j) {
                if (A[i][j] > A[i][v] + A[v][j]){
                    A[i][j] = A[i][v] + A[v][j];
                    path[i][j] = v;
                }
            }
        }
    }
}

/**
 * 任意两点间<u,v>最短路径上的顶点序列或边序列
 * @param u
 * @param v
 * @param vex
 * @param path
 * @param A
 */
void printfPath(int u,int v,char vex[],int path[][maxSize],int A[][maxSize]){
    if (A[u][v] == INF)
        cout << "\t" <<endl;
    else{
        if (path[u][v] == -1)
//            cout <<"<"<<vex[u]<<","<<vex[v]<<">  ";
            cout << vex[u]<<"->";
        else{
            int mid = path[u][v];
            printfPath(u,mid,vex,path,A);
            printfPath(mid,v,vex,path,A);
        }
    }
}
void printfAllPath(MGraph *graph,char vex[],int path[][maxSize],int A[][maxSize]){
    cout << "path[][]"<<endl;
    for (int i = 0; i < graph->n; ++i) {
        for (int j = 0; j < graph->n; ++j) {
            cout << path[i][j]<<"\t";
        }
        cout << endl;
    }
    cout << "A[][]"<<endl;
    for (int i = 0; i < graph->n; ++i) {
        for (int j = 0; j < graph->n; ++j) {
            if (A[i][j] == INF)
                cout << "∞\t";
            else
                cout << A[i][j]<<"\t";
        }
        cout << endl;
    }
    for (int i = 0; i < graph->n; ++i) {
        for (int j = 0; j < graph->n; ++j) {
            if (A[i][j] != INF){
                printf("顶点%c到顶点%c的最短路径为:",vex[i],vex[j]);
                printfPath(i,j,vex,path,A);cout <<vex[j];
                printf("\t路径长度为：%d\n",A[i][j]);
            } else{
                printf("顶点%c到顶点%c的最短路径为:\t",vex[i],vex[j]);
                printf("\t路径长度为：∞\n");
            }
        }
        if (i != graph->n-1)
            cout << endl;
    }
}

/**
 * 有向图的拓扑排序
 * @param graph
 * @return
 */
void topologicalSort(ALGraph *graph){
    int i, j, n = 0;
    int stack[maxSize],top = -1;
    vector<char> outputTop;
    ArcNode *p;
    /*将图中入度为0的顶点入栈*/
    for (i = 0; i < graph->n; ++i) {
        if (graph->adjList[i].inDegree == 0)
            stack[++top] = i;
    }
    while (top != -1){
        i = stack[top--];
        ++n;
        outputTop.push_back(graph->adjList[i].data);
//        cout << graph->adjList[i].data <<" ";
        p = graph->adjList[i].firstArc;
        while (p != nullptr){
            j = p->adjVex;
            --(graph->adjList[j].inDegree);
            if (graph->adjList[j].inDegree == 0)
                stack[++top] = j;
            p = p->nextArc;
        }
    }
    if (n != graph->n)
        cout << "Error！图中有回路！";
    else{
        for (char k : outputTop) {
            cout << k<<" ";
        }
    }
//    return n == graph->n;
}
void ReverseTopologicalSort(ALGraph *G, int v) {
    visit[v] = 1;       // 置已访问标记
    ArcNode *q = G->adjList[v].firstArc;
    while (q != nullptr) {
        if (visit[q->adjVex] == 0)
            ReverseTopologicalSort(G, q->adjVex);
        q = q->nextArc;
    }
    Visit(G, v);
}


void initVisit() {
    memset(visit, 0, sizeof(visit));
}

//确定顶点vex在G.adjList中的序号
int locateVex(ALGraph *G, char vex) {
    for (int i = 0; i < G->n; i++) {
        if (G->adjList[i].data == vex) {
            return i;
        }
    }
    return -1;
}

int locateVex(MGraph *G, char vex) {
    for (int i = 0; i < G->n; i++) {
        if (G->vex[i] == vex) {
            return i;
        }
    }
    return -1;
}

void Visit(ALGraph *G, int i) {
    cout << G->adjList[i].data << " ";
}

void transEdge(MGraph *mGraph, Edge *edge, char edges[][3]) {
    for (int i = 0; i < mGraph->e; ++i) {
        edge[i].start = edges[i][0] - 'A';
        edge[i].end = edges[i][1] - 'A';
        edge[i].weight = (int) edges[i][2];
    }
}


// 图构造测试用例
static char vex[] = {'A', 'B', 'C', 'D', 'E', 'F','G'};
static char vex_top[] = {'A', 'B', 'C', 'D'};
static char edges[][3]{
        {'A','B',4},
        {'A','C',6},
        {'A','D',6},
        {'B','C',1},
        {'B','E',7},
        {'C','E',6},
        {'C','F',4},
        {'D','C',2},
        {'D','F',5},
        {'F','E',1},
        {'F','G',8},
        {'E','G',6}
};
static char edges_top[][3]{
        {'A','B',},
        {'A','C',},
        {'B','D',},
        {'D','B',},
};
int main() {
    int n = length(vex);
    int e = length(edges);
    auto *udiGraph_M = new MGraph;
    auto *diGraph_M = new MGraph;
    auto *udiGraph_A = new ALGraph;
    auto *diGraph_A = new ALGraph;
    auto *diGraph_top = new ALGraph;
    createUnDiGraph(udiGraph_M,n,e,vex,edges);
    createDiGraph(diGraph_M,n,e,vex,edges);
    createUnDiGraph(udiGraph_A,n,e,vex,edges);
    createDiGraph(diGraph_A,n,e,vex,edges);

    n = length(vex_top);
    e = length(edges_top);
    createDiGraph(diGraph_top,n,e,vex_top,edges_top);


    cout << "----------------------------无向图的邻接矩阵--------------------------\n";
    printAdjacencyMatrix(udiGraph_M);
    cout << "----------------------------有向图的邻接矩阵--------------------------\n";
    printAdjacencyMatrix(diGraph_M);
    cout << "----------------------------无向图的邻接表----------------------------\n";
    printAdjacencyList(udiGraph_A);
    cout << "----------------------------有向图的邻接表----------------------------\n";
    printAdjacencyList(diGraph_A);
    cout << "----------------------无向图深度优先遍历算法------------------------\n";
    DFS(udiGraph_A, 0);
    cout << "\n----------------------无向图广度优先遍历算法-------------------------\n";
    //    initVisit();
    BFS(udiGraph_A, 0);
    cout << "\n----------------------有向图深度优先遍历算法------------------------\n";
    initVisit();
    DFS(diGraph_A, 0);  //???
    cout << "\n----------------------有向图广度优先遍历算法------------------------\n";
    initVisit();
    BFS(diGraph_A, 0);
    cout << "\n--------------------------Prim算法------------------------------\n";
    cout << "最小生成树的权值：" << Prim(udiGraph_M, 0) << endl;
    cout << "-------------------------Kruskal算法------------------------------\n";
    Edge road[udiGraph_M->e];
    transEdge(udiGraph_M, road, edges);
    cout << "最小生成树的权值：" << Kruskal(road, n, e) << endl;
    cout << "-------------------------Dijkstra算法--------------------------\n";
    int dist[diGraph_M->n];
    int path[diGraph_M->n];
    Dijkstra(diGraph_M,0,dist,path);
    printfAllPath(diGraph_M,vex,0,path,dist);

    cout << "\n-------------------------------Floyd算法--------------------------\n";
    int Path[maxSize][maxSize];
    int A[maxSize][maxSize];
    Floyd(diGraph_M,Path,A);
    printfAllPath(diGraph_M,vex,Path,A);

    cout << "\n-------------------------------拓扑排序--------------------------\n";
    cout << "拓扑排序：" ;
    topologicalSort(diGraph_A);
    cout << "\n拓扑排序：";
    topologicalSort(diGraph_top);
    cout << "\n逆拓扑排序：";
    ReverseTopologicalSort(diGraph_A,0);
    return 0;
}