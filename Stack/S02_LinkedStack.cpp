/**
 * Created by lhy on 2021/3/17 22:42
 * Description:
 */
#include <iostream>
using namespace std;
struct LinkedStack{
    int data;
    LinkedStack *next;
};

void initStack(LinkedStack *&lst){
    lst = new LinkedStack;
    lst->next = nullptr;
}

bool isEmpty(LinkedStack *lst){
    return lst->next == nullptr;
}

void push(LinkedStack *head,int x){
    auto *top = (LinkedStack*)malloc(sizeof(LinkedStack));
    top->next = nullptr;
    top->data = x;
    top->next = head->next;
    head->next = top;
}

bool pop(LinkedStack *head,int &x){
    LinkedStack *top;
    if (isEmpty(head))
        return false;
    top = head->next;
    x = top->data;
    head->next = top->next;
    free(top);
    return true;
}

int main(){

    return 0;
}

