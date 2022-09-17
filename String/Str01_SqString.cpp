/**
 * Created by lhy on 2021/3/24 15:50
 * Description:
 */
#include <iostream>
#define maxSize 100
using namespace std;

//定长顺序存储
struct Str_{
    char str[maxSize+1];        // '\0'最为串结束的标志
    int length;
};
//变长顺序存储(动态分配存储表示) 更常用
struct Str{
    char *ch;
    int length;
};

/**
 * 赋值操作
 * @param str   串
 * @param ch    赋值串的数组
 * @return
 */
int strAssign(Str &str, char *ch){
    if (str.ch)
        free(str.ch);       // 释放原串空间
    int length = 0;
    char *c = ch;
    while (*c){         // 求ch串的长度
        ++length;
        ++c;            // c指向一片连续的存储空间
    }
    if (length == 0){       //ch为空串，直接返回空串
        str.ch = nullptr;
        str.length = 0;
        return 1;
    } else{
        str.ch = (char*)malloc(sizeof(char) * (length+1));
        if (str.ch == nullptr)      // 内存满
            return 0;
        else{
            c = ch;
            for (int i = 0; i <= length; ++i, ++c) {
                str.ch[i] = *c;
            }
            str.length = length;
            return 1;
        }
    }
}
/**
 *  取串的长度
 * @param str
 * @return
 */
int strLength(Str str){
    return str.length;
}
/**
 * 串的比较 基于 ASCII 比较
 * @param s1
 * @param s2
 * @return
 */
int strCompare(Str s1,Str s2){
    for (int i = 0; i < s1.length && i < s2.length; ++i) {
        if (s1.ch[i] != s2.ch[i])
            return s1.ch[i] - s2.ch[i];
    }
    return s1.length - s2.length;
}
/**
 * 串连接
 * @param str   连接的结果
 * @param str1  连接的串1
 * @param str2  连接的串2
 * @return
 */
int concat(Str &str, Str str1, Str str2){
    if (str.ch){
        free(str.ch);
        str.ch = nullptr;
    }
    str.ch = (char*)malloc(sizeof(char)*(str1.length+str2.length+1));
    if (!str.ch)
        return 0;
    int i,j;
    for (i = 0; i < str1.length; ++i) {
        str.ch[i] = str1.ch[i];
    }
    for (j = 0; j < str2.length; ++j) {
        str.ch[i+j] = str2.ch[j];
    }
    str.length = str1.length + str2.length;
    return 1;
}
/**
 *  求子串
 * @param subStr 求得的子串
 * @param str   原串
 * @param pos 串的起始位置
 * @param length 取串的长度
 * @return
 */
int getSubString(Str &substr,Str str,int pos,int length){
    if (pos<0 || pos>str.length || length<0 || length>str.length-pos)
        return 0;
    if (substr.ch){
        free(substr.ch);
        substr.ch = nullptr;
    }
    if (length == 0){
        substr.ch = nullptr;
        substr.length = 0;
        return 1;
    } else{
        substr.ch = (char*)malloc(sizeof(char) * (length+1));
        int i = pos,j = 0;
        while (i < pos+length){
            substr.ch[j++] = str.ch[i++];
        }
        substr.ch[j] = '\0';
        substr.length = length;
        return 1;
    }
}
/**
 * 清空串
 * @param str
 * @return
 */
int clearString(Str &str){
    if (str.ch){
        free(str.ch);
        str.ch = nullptr;
    }
    str.length = 0;
    return 1;
}
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

int printString(Str str,string operation){
    cout << operation<<"执行结果：";
    if (str.length == 0){
        cout<<"empty!"<<endl;
        return 0;
    }
    cout <<"[string] = ";
    for (int i = 0; i < str.length; ++i) {
        cout << str.ch[i];
    }
    cout<<endl;
    return 1;
}

int main(){
    Str str{},str1{},str2{},substr{};
    char *ch1 = "abcde";
    char *ch2 = "defggg";
    int next[] = {};
    strAssign(str1,ch1);
    printString(str1,"串赋值");

//    cout << "串str1的长度 = " << strLength(str1) << endl;

    strAssign(str2,ch2);

//    cout << "串比较：" <<strCompare(str1,str2) << endl;

    concat(str,str1,str2);
    printString(str,"连接str1和str2");

    getSubString(substr,str2,3,3);
    printString(substr,"获取str2子串");

    getNext(substr,next);
    int index = KMP(str,substr,next);
    cout << "KMP:"<< index << endl;

//    clearString(substr);
//    printString(substr,"清空substr");

    return 0;
}



