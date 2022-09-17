/**
 * Created by lhy on 2021/3/22 20:27
 * Description:
 */
#include <iostream>
#define maxSize
using namespace std;
struct stack{
    int data[maxSize];
    int top[2] = {-1,maxSize};
};


bool isEmpty(stack s){
    return s.top[0] == -1 && s.top[1] == maxSize;
}
bool isFull(stack s){
    return s.top[0]+1 == s.top[1];
}
void pushS1(stack &s,int &x){
    if (!isEmpty(s))
        s.data[++s.top[0]] = x;
}
void pushS2(stack &s,int &x){
    if (!isEmpty(s))
        s.data[--s.top[1]] = x;
}
