/**
 * Created by lhy on 2021/3/16 21:55
 * Description:
 */
/*  408 真题
* 一双链表非空，由head指针指出，结点结构为{prior,data,next},
* 请设计一个将结点数据域data值最大的那个结点（最大结点只有一个）
* 移动到链表最前边的算法，要求不得申请新结点空间
*/
#include <iostream>
using namespace std;

struct DLNode{
    int data;
    DLNode *prior;
    DLNode *next;
};

/*尾插法*/
void createDListR(DLNode *&L,const int arr[],int n){
    DLNode *p,*r;
    L = (DLNode*)malloc(sizeof(DLNode));
    L->prior = nullptr;
    L->next = nullptr;
    r = L;
    for (int i = 0; i < n; ++i) {
        p = (DLNode*)malloc(sizeof(DLNode));
        p->next = nullptr;
        p->data = arr[i];
        r->next = p;
        p->prior = r;
        r = p;
    }
}

void printList(DLNode *L,const string& name){
    DLNode *p = nullptr;
    p = L->next;
    cout <<"["<<name<<" DList]: ";
    if (p == nullptr)
        cout <<"empty!"<<endl;
    while (p != nullptr){
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void maxFirst(DLNode *head){
    DLNode *p = head->next,*q = p;
    int max = p->data;
    // 找最值
    while (p != nullptr){
        if (max < p->data){
            max = p->data;
            q = p;
        }
        p = p->next;
    }
    // 删除
    DLNode *l = q->prior,*r = q->next;
    l->next = r;
    if (r != nullptr)
        r->prior = l;
    //插入
    q->prior = head;
    q->next = head->next;
    head->next = q;
    q->next->prior = q;
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8};
    DLNode *dlNode;
    createDListR(dlNode,arr,8);
    printList(dlNode,"DL: ");
    maxFirst(dlNode);
    printList(dlNode,"max DL: ");
    return 0;
}

