/**
 * Created by lhy on 2021/3/13 18:54
 * Description:
 */
#include <iostream>
#define MaxSize 100
using namespace std;

struct SqList{
    int data[MaxSize];
    int length;
};

void initList(SqList *L){
    L->length = 0;
}

int createList(SqList *L,const int arr[],int n){
    if (n > MaxSize)
        return 0;
    L->length = n;
    for (int i = 0; i < L->length; ++i) {
        L->data[i] = arr[i];
    }
    return 1;
}

void printList(SqList L){
    cout << "[SqList]: ";
    if (L.length == 0)
        cout << "empty!";
    for (int i = 0; i < L.length; ++i) {
        cout << L.data[i]<<" ";
    }
    cout << endl;
}

int getElem(SqList L,int p,int &e){
    if (p<0 || p>L.length-1)
        return 0;
    e = L.data[p];
    return 1;
}

int findElem(SqList L,int e){
    for (int i = 0; i < L.length; ++i) {
        if (e == L.data[i])
            return i;
    }
    return -1;
}

int insertElem(SqList *L,int p,int e){
    if (p<0 || p>L->length || L->length==MaxSize)
        return 0;
    for (int i = L->length - 1; i >= p; --i) {
        L->data[i+1] = L->data[i];
    }
    L->data[p] = e;
    L->length++;
    return 1;
}

int deleteElem(SqList &L,int p,int &e){
    if (p<0 || p>L.length-1)
        return 0;
    e = L.data[p];
    for (int i = p; i < L.length - 1; ++i) {
        L.data[i] = L.data[i+1];
    }
    L.length--;
    return 1;
}
/* 天勤 P40
 * 将顺序表中所有元素逆置
 */
void reverseList(SqList &L){
    int left = 0;
    int right = L.length-1;
    int temp = 0;
    for (int i = left, j = right; i < j; i++,j--) {
        temp = L.data[j];
        L.data[j] = L.data[i];
        L.data[i] = temp;
    }
}
/*
 * 从一给定的顺序表L中删除下标i~j（i<=j,包括i、j）的所有元素
 */
int deleteManyElem(SqList &L,int i,int j,int deleteArr[]){
    if (i<0 || j<0 || i>j || i >L.length-1 || j > L.length-1)
        return 0;
    int deltaD = j-i+1;
    int index = 0;
    for (int k = i; k <= j; ++k) {
        deleteArr[index++] = L.data[k];
        L.data[k] = L.data[k+deltaD];
    }
    L.length -= deltaD;
    return 1;
}

string compareAB(SqList &A,SqList &B){
    int delta = 0;
    int length = A.length >= B.length ? B.length : A.length;
    for (int i = 0; i < length; ++i) {
        if (A.data[i] == B.data[i])
            delta++;
    }
    if (A.length==delta && B.length==delta)
        return "A=B";
    else if (A.data[delta] < B.data[delta] || A.length==delta)
        return "A<B";
    else
        return "A>B";
}

int getMaxElem(SqList L,int &max){
    max = L.data[0];
    int maxIndex = 0;
    for (int i = 0; i < L.length; ++i) {
        if (max < L.data[i]){
            max = L.data[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

int getMinElem(SqList L,int &min){
    min = L.data[0];
    int minIndex = 0;
    for (int i = 0; i < L.length; ++i) {
        if (min > L.data[i]){
            min = L.data[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void partition(SqList &L,int comp){
    int i = 0,j = L.length - 1;
    int temp = L.data[i];
    while (i < j){
        while (i < j && L.data[j] >= comp)
            --j;
        if (i < j)
            L.data[i++] = L.data[j];
        while (i < j && L.data[i] < comp)
            ++i;
        if (i < j)
            L.data[j--] = L.data[i];
    }
    L.data[i] = temp;
}

void partitionByIndex(SqList &L,int k){
    int i = 0,j = L.length - 1;
    int temp = L.data[0];
    L.data[0] = L.data[k];
    L.data[k] = temp;
    temp = L.data[i];
    while (i < j){
        while (i < j && L.data[j] >= temp)
            j--;
        if (i < j)
            L.data[i++] = L.data[j];
        while (i < j && L.data[i] < temp)
            i++;
        if (i < j)
            L.data[j--] = L.data[i];
    }
    L.data[i] = temp;
}
//二路归并，默认两个顺序表是有序的
void mergeSqList(SqList L1,SqList L2,SqList &mergeSqList){
    int i = 0,j = 0;
    int r = 0;
    while (i < L1.length && j < L2.length){
        if (L1.data[i] < L2.data[j])
            mergeSqList.data[r++] = L1.data[i++];
        else
            mergeSqList.data[r++] = L2.data[j++];
    }
    while (i < L1.length)
        mergeSqList.data[r++] = L1.data[i++];
    while (j < L2.length)
        mergeSqList.data[r++] = L2.data[j++];
}

int main(){
    int n = 6;

    int arrA[] = {0,2,7,9,45,56};
    int arrB[] = {1,5,8,40,44,60,70};
    SqList *A = (SqList*)malloc(sizeof(SqList));
    SqList *B = (SqList*)malloc(sizeof(SqList));
    createList(A,arrA,6);
    createList(B,arrB,7);
    cout << compareAB(*A,*B) << endl;

    SqList *C = (SqList*)malloc(sizeof(SqList));
    int *arrC = new int[13];
    createList(C,arrC,13);
    mergeSqList(*A,*B,*C);
    printList(*C);

    int arr[] = {6,100,-7,-3,5,6};
    SqList *sqList = (SqList*)malloc(sizeof(SqList));
    initList(sqList);
    createList(sqList,arr,n);
    printList(*sqList);

    partition(*sqList,3);
    printList(*sqList);
    partitionByIndex(*sqList,2);
    printList(*sqList);

    int max = 0 ,min = 0;
    cout <<" index = "<<getMaxElem(*sqList,max)<< " sqList max = "<<max<<endl;
    cout <<" index = "<<getMinElem(*sqList,min)<< " sqList min = "<<min<<endl;



    int delArr[3] = {};
    deleteManyElem(*sqList,2,4,delArr);
    printList(*sqList);
    for (int i : delArr) {
        cout << i<<" ";
    }
    cout << endl;

    int getE = 0;
    getElem(*sqList,3,getE);
    cout << "getElem:"<<getE<<endl;

    int findE = findElem(*sqList,22);
    cout << "findElem:"<<findE << endl;

    insertElem(sqList,4,100);
    cout << "insertElem ";
    printList(*sqList);

    int deleteE = 0;
    deleteElem(*sqList,33,deleteE);
    printList(*sqList);
    cout << "deleteElem:" << deleteE << endl;

    reverseList(*sqList);
    cout <<"reverseList ";
    printList(*sqList);

    return 0;
}

