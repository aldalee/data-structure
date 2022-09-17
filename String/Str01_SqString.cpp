/**
 * Created by lhy on 2021/3/24 15:50
 * Description:
 */
#include <iostream>
#define maxSize 100
using namespace std;

//����˳��洢
struct Str_{
    char str[maxSize+1];        // '\0'��Ϊ�������ı�־
    int length;
};
//�䳤˳��洢(��̬����洢��ʾ) ������
struct Str{
    char *ch;
    int length;
};

/**
 * ��ֵ����
 * @param str   ��
 * @param ch    ��ֵ��������
 * @return
 */
int strAssign(Str &str, char *ch){
    if (str.ch)
        free(str.ch);       // �ͷ�ԭ���ռ�
    int length = 0;
    char *c = ch;
    while (*c){         // ��ch���ĳ���
        ++length;
        ++c;            // cָ��һƬ�����Ĵ洢�ռ�
    }
    if (length == 0){       //chΪ�մ���ֱ�ӷ��ؿմ�
        str.ch = nullptr;
        str.length = 0;
        return 1;
    } else{
        str.ch = (char*)malloc(sizeof(char) * (length+1));
        if (str.ch == nullptr)      // �ڴ���
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
 *  ȡ���ĳ���
 * @param str
 * @return
 */
int strLength(Str str){
    return str.length;
}
/**
 * ���ıȽ� ���� ASCII �Ƚ�
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
 * ������
 * @param str   ���ӵĽ��
 * @param str1  ���ӵĴ�1
 * @param str2  ���ӵĴ�2
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
 *  ���Ӵ�
 * @param subStr ��õ��Ӵ�
 * @param str   ԭ��
 * @param pos ������ʼλ��
 * @param length ȡ���ĳ���
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
 * ��մ�
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
 * ���next����
 * @param substr    ģʽ��
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
 * KMP�㷨
 * @param str       ����
 * @param substr    ģʽ��
 * @param next      next[]
 * @return          ƥ��λ��
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
    cout << operation<<"ִ�н����";
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
    printString(str1,"����ֵ");

//    cout << "��str1�ĳ��� = " << strLength(str1) << endl;

    strAssign(str2,ch2);

//    cout << "���Ƚϣ�" <<strCompare(str1,str2) << endl;

    concat(str,str1,str2);
    printString(str,"����str1��str2");

    getSubString(substr,str2,3,3);
    printString(substr,"��ȡstr2�Ӵ�");

    getNext(substr,next);
    int index = KMP(str,substr,next);
    cout << "KMP:"<< index << endl;

//    clearString(substr);
//    printString(substr,"���substr");

    return 0;
}



