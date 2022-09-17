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

struct MGraph {                  // ͼ���ڽӾ���
    int edges[maxSize][maxSize];
    int n, e;
    char vex[maxSize];    // ��Ŷ�����Ϣ
};
struct ArcNode {                 // �߽��
    int adjVex;                 // �ñ���ָ��Ľ���λ��
    ArcNode *nextArc;           // ָ����һ���ߵ�ָ��
    int info;                   // �ñߵ������Ϣ����Ȩֵ
};
struct VNode {
    char data;                  // ������Ϣ
    int inDegree;                  // ͳ�ƶ��㵱ǰ�����
    ArcNode *firstArc;          // ָ���һ���ߵ�ָ��
};
struct ALGraph {
    VNode adjList[maxSize];     // �ڽӱ�
    int n, e;                    // �������ͱ���
};
struct Edge {                    // �ߵĴ洢�ṹ
    int start, end;              // ��ʼ ����
    int weight;                 // Ȩֵ
};

void Visit(ALGraph *G, int i);

int locateVex(ALGraph *G, char vex);

int locateVex(MGraph *G, char vex);

void initVisit();

void quickSort(Edge edge[], int low, int high);

void selectSort(Edge edge[], int e);


/**
* �����ڽӾ���Ĵ洢�ṹ��������ͼ
* @param G
* @param n     ������
* @param e     ����
* @param vex   ���㼯��
* @param edges �߼���+Ȩֵ
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
 * �����ڽӱ�Ĵ洢�ṹ��������ͼ
 * @param G
 * @param n     ������
 * @param e     ����
 * @param vex   ���㼯��
 * @param edges �߼���+Ȩֵ
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
* �����ڽӾ���Ĵ洢�ṹ��������ͼ
* @param G
* @param n     ������
* @param e     ����
* @param vex   ���㼯��
* @param edges �߼���+Ȩֵ
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
 * �����ڽӱ�Ĵ洢�ṹ��������ͼ
 * @param G
 * @param n     ������
 * @param e     ����
 * @param vex   ���㼯��
 * @param edges �߼���
 * @return
 */
bool createDiGraph(ALGraph *G, int n, int e, const char vex[], char edges[][3]) {
    G->n = n;
    G->e = e;
    int inDegree = 0;      // ��¼��ǰ��������
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
                cout << "��" << "\t";
            else
                cout << G->edges[i][j] << "\t";
        }
        cout << endl;
    }
}

/**
 * ��ӡͼ���ڽӱ�
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
 * ��ȡG�б�<start, end>��Ȩֵ����start��end������ͨ�ģ��򷵻������
 * @param G �ڽӱ�ͼ
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


static int vexSet[maxSize];                  // ���岢�鼯����
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

/** �����⣬�Ժ��ٵ�
 * ��edge[]�����е� e ���߰���Ȩֵweight��������
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
 * ���ڽӱ�Ϊ�洢�ṹ��ͼ������ȱ����㷨
 * @param v ��������ʼ��
 * @param G �ڽӱ�ͼ
 */
static int visit[maxSize];

void DFS(ALGraph *G, int v) {
    visit[v] = 1;       // ���ѷ��ʱ��
    Visit(G, v);
    ArcNode *q = G->adjList[v].firstArc;
    while (q != nullptr) {
        if (visit[q->adjVex] == 0)
            DFS(G, q->adjVex);
        q = q->nextArc;
    }
}

/**
 * ���ڽӱ�Ϊ�洢�ṹ��ͼ������ȱ����㷨
 * @param G �ڽӱ�ͼ
 * @param v ��������ʼ��
 */
void BFS(ALGraph *G, int v) {
    initVisit();
    ArcNode *p;
    int que[maxSize];                               // �������
    int front = 0, rear = 0;
    int j;
    Visit(G, v);                                       // ������ʶ���v�ĺ���
    visit[v] = 1;
    rear = (rear + 1) % maxSize;                      // ��ǰ����v����
    que[rear] = v;
    while (front != rear) {                          // �ӿյ�ʱ��������
        front = (front + 1) % maxSize;                // �������
        j = que[front];
        p = G->adjList[j].firstArc;                 // pָ����Ӷ��� j �ĵ�һ����
        while (p != nullptr) {                       // �� p �������ڽӵ���δ�����ʵ����
            if (visit[p->adjVex] == 0) {          //��ǰ�ڽӶ���δ�����ʣ������
                Visit(G, p->adjVex);
                visit[p->adjVex] = 1;
                rear = (rear + 1) % maxSize;          // �ö������
                que[rear] = p->adjVex;
            }
            p = p->nextArc;
        }
    }
    initVisit();
}

/**
 * ������ͼ���ڽӾ���Ϊ�洢�ṹ�� Prim��С�������㷨
 * @param G �ڽӾ���
 * @param v0 ��ʼ���
 * @param sum ��������Ȩֵ
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
    vSet[v0] = 1;   // ��v0��������
    int sum = 0;
    for (i = 0; i < G->n - 1; ++i) {
        min = INF;
        for (j = 0; j < G->n; ++j) {    // ѡ����ѡ���е���Сֵ
            if (vSet[j] == 0 && lowCost[j] < min) {
                min = lowCost[j];
                k = j;
            }
        }
        vSet[k] = 1;
        v = k;
        sum += min;
        for (j = 0; j < G->n; ++j) {    // �Ըղ���Ķ���vΪý����º�ѡ��
            if (vSet[j] == 0 && G->edges[v][j] < lowCost[j])
                lowCost[j] = G->edges[v][j];
        }
    }
    return sum;
}

/**
 * Dijkstra�㷨 ��ͼ��ĳһ���㵽�������������·��
 * @param graph ���ڽӾ���洢��ͼ
 * @param v     Դ��
 * @param dist ��� v �㵽���ඥ������·������
 * @param path ��� v �㵽�������������·��
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
        /*ÿ�δ�ʣ�ඥ����ѡ��һ�����㣬ͨ����������·����ͨ������ʣ�ඥ���·������̵�*/
        for (int j = 0; j < graph->n; ++j) {
            if (set[j] == 0 && dist[j] < min){
                u = j;
                min = dist[j];
            }
        }
        set[u] = 1;     // ��ѡ���ĵ㲢�����·����
        /*�Ըղ���Ķ���Ϊ�м�㣬��ͨ��ʣ�ඥ���·�����м��*/
        for (int j = 0; j < graph->n; ++j) {
            /*�ж϶���u�ļ����Ƿ�����ͨ������j�ĸ��̵�·�������������ԭ����·�������ȣ�����ʲô������*/
            if (set[j] == 0 && dist[u] + graph->edges[u][j] < dist[j]){
                dist[j] = dist[u] + graph->edges[u][j];
                path[j] = u;
            }
        }
    }
}

/**
 * ��ӡ��Դ�㵽�κ�һ���������·���������������ж���
 * @param path ��˫�״洢�ṹ�洢����
 * @param v path[]�е�ĳһ��ֵ
 * @param vex ͼ�Ķ�������
 */
void printfPath(const int path[],int v, char vex[]){
    int stack[maxSize],top=-1;
    /*��Ҷ�ӽ�㵽���ڵ��˳������ջ*/
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
 * ��ӡ��ָ��Դ�㵽ȫ���������·���������������ж��㣬�Լ�path[]��dist[]
 * @param graph
 * @param vex
 * @param i     ָ��Դ��
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
            cout << "�� ";
    }
    cout << "\npath: ";
    for (int j = 0; j < graph->n; ++j) {
        cout << path[j] << " ";
    }
    cout <<endl;
    for (int j = 0; j < graph->n ; ++j) {
        if (dist[j] != INF){
            printf("����%c������%c�����·��Ϊ��",vex[i],vex[j]);
            printfPath(path,j,vex);
            printf("\t·������Ϊ��%d\n",dist[j]);
        } else{
            printf("����%c������%c�����·��Ϊ:\t",vex[i],vex[j]);
            printf("\t·������Ϊ����\n");
        }
    }
}
/**
 * Floyd�㷨  ��ͼ������һ���㵽�������������·��
 * @param graph
 * @param path
 * @param A
 */
void Floyd(MGraph *graph,int path[][maxSize],int A[][maxSize]){
    /*��path[] A[][]��ʼ��*/
    for (int i = 0; i < graph->n; ++i) {
        for (int j = 0; j < graph->n; ++j) {
            A[i][j] = graph->edges[i][j];
            path[i][j] = -1;
        }
    }
    /*��vΪ�м������еĶ����(i,j)���м����޸�*/
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
 * ���������<u,v>���·���ϵĶ������л������
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
                cout << "��\t";
            else
                cout << A[i][j]<<"\t";
        }
        cout << endl;
    }
    for (int i = 0; i < graph->n; ++i) {
        for (int j = 0; j < graph->n; ++j) {
            if (A[i][j] != INF){
                printf("����%c������%c�����·��Ϊ:",vex[i],vex[j]);
                printfPath(i,j,vex,path,A);cout <<vex[j];
                printf("\t·������Ϊ��%d\n",A[i][j]);
            } else{
                printf("����%c������%c�����·��Ϊ:\t",vex[i],vex[j]);
                printf("\t·������Ϊ����\n");
            }
        }
        if (i != graph->n-1)
            cout << endl;
    }
}

/**
 * ����ͼ����������
 * @param graph
 * @return
 */
void topologicalSort(ALGraph *graph){
    int i, j, n = 0;
    int stack[maxSize],top = -1;
    vector<char> outputTop;
    ArcNode *p;
    /*��ͼ�����Ϊ0�Ķ�����ջ*/
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
        cout << "Error��ͼ���л�·��";
    else{
        for (char k : outputTop) {
            cout << k<<" ";
        }
    }
//    return n == graph->n;
}
void ReverseTopologicalSort(ALGraph *G, int v) {
    visit[v] = 1;       // ���ѷ��ʱ��
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

//ȷ������vex��G.adjList�е����
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


// ͼ�����������
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


    cout << "----------------------------����ͼ���ڽӾ���--------------------------\n";
    printAdjacencyMatrix(udiGraph_M);
    cout << "----------------------------����ͼ���ڽӾ���--------------------------\n";
    printAdjacencyMatrix(diGraph_M);
    cout << "----------------------------����ͼ���ڽӱ�----------------------------\n";
    printAdjacencyList(udiGraph_A);
    cout << "----------------------------����ͼ���ڽӱ�----------------------------\n";
    printAdjacencyList(diGraph_A);
    cout << "----------------------����ͼ������ȱ����㷨------------------------\n";
    DFS(udiGraph_A, 0);
    cout << "\n----------------------����ͼ������ȱ����㷨-------------------------\n";
    //    initVisit();
    BFS(udiGraph_A, 0);
    cout << "\n----------------------����ͼ������ȱ����㷨------------------------\n";
    initVisit();
    DFS(diGraph_A, 0);  //???
    cout << "\n----------------------����ͼ������ȱ����㷨------------------------\n";
    initVisit();
    BFS(diGraph_A, 0);
    cout << "\n--------------------------Prim�㷨------------------------------\n";
    cout << "��С��������Ȩֵ��" << Prim(udiGraph_M, 0) << endl;
    cout << "-------------------------Kruskal�㷨------------------------------\n";
    Edge road[udiGraph_M->e];
    transEdge(udiGraph_M, road, edges);
    cout << "��С��������Ȩֵ��" << Kruskal(road, n, e) << endl;
    cout << "-------------------------Dijkstra�㷨--------------------------\n";
    int dist[diGraph_M->n];
    int path[diGraph_M->n];
    Dijkstra(diGraph_M,0,dist,path);
    printfAllPath(diGraph_M,vex,0,path,dist);

    cout << "\n-------------------------------Floyd�㷨--------------------------\n";
    int Path[maxSize][maxSize];
    int A[maxSize][maxSize];
    Floyd(diGraph_M,Path,A);
    printfAllPath(diGraph_M,vex,Path,A);

    cout << "\n-------------------------------��������--------------------------\n";
    cout << "��������" ;
    topologicalSort(diGraph_A);
    cout << "\n��������";
    topologicalSort(diGraph_top);
    cout << "\n����������";
    ReverseTopologicalSort(diGraph_A,0);
    return 0;
}