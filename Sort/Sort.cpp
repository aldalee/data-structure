/**
 * Created by lhy on 2021/4/17 19:05
 * Description:
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#define random(x) rand()%(x)
using namespace std;
void printArray(int arr[],int n);
void swap(int arr[],int i,int j);
/**
 * 插入类排序
 *
 */
 /*[1] 直接插入排序*/
 void insertSort(int arr[], int n) {
     int i,j,temp;
     for (i = 1; i < n; ++i) {
         temp = arr[i];
         j = i-1;
         while (j >= 0 && temp < arr[j]) {      // 从有序系列中找到合适位置
             arr[j+1] = arr[j];
             --j;
         }
         arr[j+1] = temp;   // 插入
     }
 }
 /*希尔排序*/
 void shellSort(int arr[],int n) {
     int i,j,temp;
     for (int gap = n/2; gap > 0; gap /= 2) {
         for (i = gap; i < n; ++i) {
             temp = arr[i];
             for (j = i; j >= gap && arr[j-gap] > temp ; j -= gap) {
                 arr[j] = arr[j-gap];
             }
             arr[j] = temp;
         }
     }
 }

/**
 * 选择类排序
 *
 */
/*[1] 选择排序*/
void selectSort(int arr[],int n){
    int k;
    for (int i = 0; i < n; ++i) {
        k = i;
        for (int j = i+1; j < n; ++j) {     // 挑选出无序序列中最小的
            if (arr[k] > arr[j])
                k = j;
        }
        swap(arr,i,k);
    }
}

/**
 * 交换类排序
 *
 */
/*[1] 冒泡排序*/
void bubbleSort(int arr[],int n){
    int flag;
    for (int i = n-1; i >= 1; --i) {
        flag = 0;
        for (int j = 1; j <= i; ++j) {
            if (arr[j-1] > arr[j]){
                swap(arr,j-1,j);
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}
/*[2] 快速排序*/
void quickSort(int arr[], int low, int high) {
    int temp;
    int i = low, j = high;
    if (low < high){
        temp = arr[low];
        while (i < j){
            while (j > i && arr[j] >= temp)
                --j;
            if (i < j){
                arr[i] = arr[j];
                ++i;
            }
            while (i < j && arr[i] < temp)
                ++i;
            if (i < j){
                arr[j] = arr[i];
                --j;
            }
        }
        arr[i] = temp;
        quickSort(arr,low,i-1);
        quickSort(arr,i+1,high);
    }
}


void swap(int arr[],int i,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void printArray(int arr[],int n){
    for (int i = 0; i < n; ++i){
        cout << arr[i]<<" ";
        if (i == n-1)
            cout << endl;
    }
 }
void initArray(int arr[],int n){
    srand((int)time(nullptr));
    for (int i=0; i < n; ++i)
        arr[i] = random(100);
}
int main(){
    int n = 30;
    int *arr = new int[n];
    initArray(arr,n);
    printArray(arr,n);
//    insertSort(arr,n);
//    selectSort(arr,n);
//    bubbleSort(arr,n);
//    shellSort(arr,n);
    quickSort(arr,0,n-1);
    printArray(arr,n);
    delete[] arr;
    return 0;
}
