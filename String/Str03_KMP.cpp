/**
 * Created by lhy on 2021/3/25 14:51
 * Description:
 */
#include <iostream>
using namespace std;
struct Str{
    char *ch;
    int length;
};
/**
 * 获得next数组
 * @param substr    模式串
 * @param next      next[]
 */
void getNext(Str substr,int next[]){
    int j = 1, t = 0;
    next[1] = 0;
    while (j < substr.length){
        if (t == 0 || substr.ch[j] == substr.ch[t]){
            next[j+1] = t+1;
            ++t;
            ++j;
        } else
            t = next[t];
    }
}
/**
 * KMP算法
 * @param str       主串
 * @param substr    模式串
 * @param next      next[]
 * @return          匹配位置
 */
int KMP(Str str,Str substr,int next[]){
    int i = 1,j = 1;
    while (i<=str.length && j<=substr.length){
        if (j==0 || str.ch[i] == substr.ch[j]){
            ++i;
            ++j;
        } else
            j = next[j];
    }
    if (j>substr.length)
        return i - substr.length;
    else
        return 0;
}



int main(){

    return 0;
}

