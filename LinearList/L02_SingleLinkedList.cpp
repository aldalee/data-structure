/**
 * Created by lhy on 2021/3/13 20:05
 * Description:
 */
#include <iostream>
#define MaxSize 100
using namespace std;

struct LNode{
    int data;
    LNode *next;
};
/*尾插法建表*/
void createLinkListR(LNode *&head,int arr[],int n){
    head = (LNode*)malloc(sizeof(LNode));
    head->next = nullptr;
    LNode *p = nullptr,*r = head;
    for (int i = 0; i < n; ++i) {
        p = (LNode*)malloc(sizeof(LNode));
        p->next = nullptr;
        p->data = arr[i];
        r->next = p;
        r = r->next;
    }
}
/*头插法建表*/
void createLinkListH(LNode *&head,int arr[],int n){
    head = (LNode*)malloc(sizeof(LNode));
    head->next = nullptr;
    LNode *p = nullptr;
    for (int i = 0; i < n; ++i) {
        p = (LNode*)malloc(sizeof(LNode));
        p->next = nullptr;
        p->data = arr[i];
        p->next = head->next;   //相当于在头结点和头结点的下一个结点之间插入一个结点
        head->next = p;
    }
}

void printList(LNode *L,const string& name){
    LNode *p = nullptr;
    p = L->next;
    cout <<"["<<name<<" SList]: ";
    if (p == nullptr)
        cout <<"empty!"<<endl;
    while (p != nullptr){
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
/*逆置 p->next 到 p 之间的结点
 * p指针是不变化的
 * */
void reverseLNode(LNode *p,LNode *q){
    LNode *t = nullptr;
    while (p->next != q){
        t = p->next;
        p->next = t->next;  //删除操作
        t->next = q->next;  //头插法
        q->next = t;
    }
}
void reverseLNode(LNode *L){
    LNode *p = L->next,*q;
    L->next = nullptr;
    while (p != nullptr){
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}
LNode* insertH(LNode *L,LNode *p,LNode *head){
    head = p;
    p = p->next;
    head->next = L->next;
    L->next = head;
    return p;
}

// 归并为升序的链表
void merge(LNode *A,LNode *B,LNode *&C){
    LNode *p = A->next;
    LNode *q = B->next;
    LNode *r;
    C = A;
    C->next = nullptr;
    free(B);
    r = C;
    while (p != nullptr && q != nullptr){
        if (p->data < q->data){
            r->next = p;
            p = p->next;
        } else{
            r->next = q;
            q = q->next;
        }
        r = r->next;
    }
    if (p != nullptr)
        r->next = p;
    if (q != nullptr)
        r->next = q;
}

void mergeR(LNode *A,LNode *B,LNode *&C){
    LNode *p = A->next;
    LNode *q = B->next;
    LNode *h = nullptr;
    C = A;
    C->next = nullptr;
    free(B);
    while (p != nullptr && q != nullptr){
        if (p->data < q->data)
            p = insertH(C,p,h);
        else
            q = insertH(C,q,h);
    }
    while (p != nullptr)
        p = insertH(C,p,h);
    while (q != nullptr)
        q = insertH(C,q,h);
}

LNode* getNodePointer(LNode *head, int i, int j){
    LNode *p = head;
    for (int k = i; k < j; ++k) {
        p = p->next;
    }
    cout << "get data:"<<p->data<<endl;
    return p;
}

LNode* getMaxElem(LNode *head,int &max){
    LNode *p,*q;
    max = head->next->data;
    q = p = head->next;
    while (p != nullptr){
        if (max < p->data){
            max = p->data;
            q = p;
        }
        p = p->next;
    }
    return q;
}

LNode* getMinElem(LNode *head,int &min){
    LNode *p,*q;
    min = head->next->data;
    q = p = head->next;
    while (p != nullptr){
        if (min > p->data){
            min = p->data;
            q = p;
        }
        p = p->next;
    }
    return q;
}

int findAndDelete(LNode *C,int x){
    LNode *p,*q;
    p = C;
    /*查找部分*/
    while (p->next != nullptr){
        if (p->next->data == x)
            break;
        p = p->next;
    }
    if (p->next == nullptr)
        return 0;
    else{
        /*删除部分*/
        q = p->next;
        p->next = p->next->next;
        free(q);
        return 1;
    }

}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    LNode *L1;
    createLinkListR(L1,arr,12);
    printList(L1,"L1");
    LNode *L2;
    createLinkListH(L2,arr,12);
    printList(L2,"L2");

    int arrA[] = {1,5,7,9};
    int arrB[] = {2,4,6,8};
    LNode *A1,*A2,*B1,*B2,*C1,*C2;
    createLinkListR(A1,arrA,4);
    createLinkListR(B1,arrB,4);
    merge(A1,B1,C1);
    printList(C1,"mergeC");

    createLinkListR(A2,arrA,4);
    createLinkListR(B2,arrB,4);
    mergeR(A2,B2,C2);
    printList(C2,"mergeC_R");

    LNode *p,*q;
    // 让 p 指向 L1 的 3结点，q 指向 L1 的 8结点
    p = getNodePointer(L1,0,3);
    q = getNodePointer(p,3,8);
    reverseLNode(p,q);
    printList(L1,"reverseL1");

    int max = 0 ,min = 0;
    cout <<" index = "<<getMaxElem(L1,max)<< "L1 max = "<<max<<endl;
    cout <<" index = "<<getMinElem(L1,min)<< "L1 min = "<<min;
    return 0;
}
