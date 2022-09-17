/**
 * Created by lhy on 2021/3/18 17:02
 * Description:
 */
#include <iostream>
using namespace std;
// 队结点类型定义
struct QNode{
    int data;
    QNode *next;
};
// 链队类型定义
struct LiQueue{
    QNode *front;
    QNode *rear;
};

void initQueue(LiQueue *&lqu){
    lqu = (LiQueue*)malloc(sizeof(LiQueue));
    lqu->front = lqu->rear = nullptr;
}

bool isQueueEmpty(LiQueue *lqu){
    return lqu->front == nullptr || lqu->rear == nullptr;
}
/**
 * 入队操作
 * @param lqu
 * @param x
 */
void enQueue(LiQueue *lqu,int x){
    QNode *p = (QNode*)malloc(sizeof(QNode));
    p->data = x;
    p->next = nullptr;
    if (isQueueEmpty(lqu))
        lqu->front = lqu->rear = p;
    else{
        lqu->rear->next = p;
        lqu->rear = p;
    }
}
/**
 * 出队操作
 * @param lqu
 * @param x
 * @return
 */
bool deQueue(LiQueue *lqu,int &x){
    QNode *p;
    if (isQueueEmpty(lqu))
        return false;
    else
        p = lqu->front;
    if (lqu->front == lqu->rear)           // 队列中只有一个结点时，出队特殊处理
        lqu->front = lqu->rear = nullptr;
    else
        lqu->front = p->next;
    x = p->data;
    free(p);
    return true;
}

int main(){
    return 0;
}
