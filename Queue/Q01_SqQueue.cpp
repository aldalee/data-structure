/**
 * Created by lhy on 2021/3/18 16:21
 * Description:
 */
#include <iostream>
#define maxSize 100
using namespace std;
struct SqQueue{
    int data[maxSize];
    int front;  //队首指针
    int rear;   //队尾指针
};
void initQueue(SqQueue &qu){
    qu.front = qu.rear = 0;
}
bool isQueueEmpty(SqQueue qu){
    return qu.front == qu.rear;
}
bool isQueueFull(SqQueue qu){
    return qu.front == (qu.rear+1) % maxSize;
}

bool enQueue(SqQueue &qu,int x){
    if (isQueueFull(qu))
        return false;
    qu.rear = (qu.rear+1) % maxSize;
    qu.data[qu.rear] = x;
    return true;
}
bool deQueue(SqQueue &qu,int &x){
    if (isQueueEmpty(qu))
        return false;
    qu.front = (qu.front+1) % maxSize;
    x = qu.data[qu.front];
    return true;
}


int main(){

    return 0;
}

