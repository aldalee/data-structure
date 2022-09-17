/**
 * Created by lhy on 2021/3/17 22:30
 * Description:
 */
#include <iostream>
#include <cmath>
#include <cstring>

#define maxSize 100
#define MIN 0.0000001
using namespace std;
struct SqStack{
    int data[maxSize];
    int top;
};

void initStack(SqStack &sqStack){
    sqStack.top = -1;
}

bool isEmpty(SqStack sqStack){
    return sqStack.top == -1;
}

bool push(SqStack &st,int x){
    if (st.top == maxSize-1)
        return false;
    st.data[++st.top] = x;
    return true;
}

bool pop(SqStack &st,int &x){
    if (isEmpty(st))
        return false;
    x = st.data[st.top--];
    return true;
}

char getPriority(char op){
    if (op == '+' || op == '-')
        return 0;
    else
        return 1;
}
/**
 * ��׺���ʽת��׺���ʽ
 * @param infix ��׺���ʽ
 * @param s2 �洢��׺���ʽ��ջ
 * @param top2
 */
void infixToPostFix(char infix[],char s2[],int &top2){
    char s1[maxSize];   //����ջ
    int top1 = -1;
    top2 = -1;
    int i = 0;
    while (infix[i] != '\0'){
        if (infix[i] >= '0' && infix[i] <= '9'){
            s2[++top2] = infix[i];
            ++i;
        } else if (infix[i] == '('){
            s1[++top1] = '(';
            ++i;
        } else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/'){
            if (top1 == -1 || s1[top1] == '(' || getPriority(infix[i]) > getPriority(s1[top1])){
                s1[++top1] = infix[i];
                ++i;
            } else
                s2[++top2] = s1[top1--];
        } else if (infix[i] == ')'){
            while (s1[top1] != '(')
                s2[++top2] = s1[top1--];
            --top1;
            ++i;
        }
    }
    while (top1 != -1)
        s2[++top2] = s1[top1--];
}

/**
 * ��׺���ʽתǰ׺���ʽ
 * @param infix
 * @param s2
 * @param top2
 */
void infixToPreFix(char infix[],int len,char s2[],int &top2){
    char s1[maxSize];
    int top1 = -1;
    int i = len - 1;
    while (i >= 0){
        if (infix[i] >= '0' && infix[i] <= '9'){
            s2[++top2] = infix[i];
            --i;
        } else if (infix[i] == ')'){
            s1[++top1] = ')';
            --i;
        } else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/'){
            if (top1 == -1 || s1[top1] == ')' || getPriority(infix[i]) >= getPriority(s1[top1])){
                s1[++top1] = infix[i];
                --i;
            } else
                s2[++top2] = s1[top1--];
        } else if (infix[i] != '('){
            while (s1[top1] != ')')
                s2[++top2] = s1[top1--];
            --top1;
            --i;
        }
    }
    while (top1 != -1)
        s2[++top2] = s1[top1--];
}

void printExpConversion(char exp[],char s2[]){
    for (int i = 0; i < strlen(exp); ++i) {
        cout<< s2[i]<<" ";
    }
    cout<<endl;
}



int calSub(float opand1,char op, float opand2, float &result){
    if (op == '+')
        result = opand1 + opand2;
    if (op == '-')
        result = opand1 - opand2;
    if (op == '*')
        result = opand1 * opand2;
    if (op == '/'){
        if (fabs(opand2) < MIN)
            return 0;
        else
            result = opand1 / opand2;
    }
    return 1;
}
int calStackTopTwo(float s1[],int &top1, char s2[],int &top2){
    float opnd1,opnd2,result;
    char op;
    int flag;
    opnd2 = s1[top1--];
    opnd1 = s1[top1--];
    op = s2[top2--];
    flag = calSub(opnd1,op,opnd2,result);
    if (flag == 0)
        cout<<"ERROR"<<endl;
    s1[++top1] = result;
    return flag;
}
/**
 * ��׺���ʽ��ֵ
 * @param exp ��׺���ʽ
 * @return ���
 */
float calInfix(char exp[]){
    float s1[maxSize];
    int top1 = -1;
    char s2[maxSize];
    int top2 = -1;
    int i = 0;
    while (exp[i] != '\0'){
        if (exp[i]>='0' && exp[i]<='9'){
            s1[++top1] = exp[i] - '0';
            ++i;
        } else if (exp[i] == '('){
            s2[++top2] = '(';
            ++i;
        } else if (exp[i]=='+' || exp[i]=='-' || exp[i]=='*' || exp[i]=='/'){
            if (top2 == -1 || s2[top2] == '(' || getPriority(exp[i]) > getPriority(s2[top2])){
                s2[++top2] = exp[i];
                ++i;
            } else{
                int flag = calStackTopTwo(s1,top1,s2,top2);
                if (flag == 0)
                    return 0;
            }
        } else if (exp[i] == ')'){
            while (s2[top2] != '('){
                int flag = calStackTopTwo(s1,top1,s2,top2);
                if (flag == 0)
                    return 0;
            }
            --top2;
            ++i;
        }
    }
    while (top2 != -1){
        int flag = calStackTopTwo(s1,top1,s2,top2);
        if (flag == 0)
            return 0;
    }
    return s1[top1];
}

/**
 * ��׺���ʽ��ֵ
 * @param exp ��׺���ʽ
 * @return ���
 */
float calPostFix(char exp[]){
    float s[maxSize];
    int top = -1;
    for (int i = 0;exp[i] != '\0';++i){
        if (exp[i] >= '0' && exp[i] <= '9')
            s[++top] = exp[i] - '0';
        else{
            float opnd1,opnd2,result;
            char op;
            int flag;
            opnd2 = s[top--];
            opnd1 = s[top--];
            op = exp[i];
            flag = calSub(opnd1,op,opnd2,result);
            if (flag == 0){
                cout << "ERROR";
                return 0;
            }
            s[++top] = result;
        }
    }
    return s[top];
}
/**
 * ǰ׺���ʽ��ֵ
 * @param exp ǰ׺���ʽ
 * @param length ���ʽ�ĳ���
 * @return ���
 */
float calPreFix(char exp[]){
    float s[maxSize];
    int top = -1;
    int length = strlen(exp);
    for (int i = length-1; i >= 0; --i) {
        if (exp[i] >= '0' && exp[i] <= '9')
            s[++top] = exp[i] - '0';
        else {
            float opnd1,opnd2,result;
            char op;
            int flag;
            opnd1 = s[top--];
            opnd2 = s[top--];   // �˴�˳�����Ҫ
            op = exp[i];
            flag = calSub(opnd1,op,opnd2,result);
            if (flag == 0){
                cout<<"ERROR";
                return 0;
            }
            s[++top] = result;
        }
    }
    return s[top];
}
/**
 * ��ջ����ʽ����
 * ��μ���ջ�����������ĳһ����ִ������ȵ� �ɳ��⣡��
 * @return
 */


bool isMatched(char left,char right){
    return (left == '(' && right == ')') || (left == '[' && right == ']') || (left == '{' && right == '}');
}
/**
 * ����ƥ��
 * @param exp
 * @return
 */
bool isParenthesesBalanced(char exp[]){
    char s[maxSize];
    int top = -1;
    for (int i = 0; exp[i] != '\0' ; ++i) {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
            s[++top] = exp[i];
        if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}'){
            if (top == -1)
                return false;
            char left = s[top--];
            if (!isMatched(left,exp[i]))
                return false;
        }
    }
    return top <= -1;
}

/**
 * ����ݹ麯��
 *           2          m = 0
 * F(m)=
 *       4 * F(m/3)     m != 0
 * @param m
 * @return
 */

int CF(int m){
    if (m == 0)
        return 2;
    else
        return 4 * CF(m/3);
}
int cF(int m){
    int cum = 2;
    int s[maxSize],top = -1;
    while (m != 0){
        s[++top] = m;
        m /= 3;
    }
    while (top != -1)
        cum = s[top--];
    return cum;
}

float sqrt_Stack(float A, float p, float e){
    float s[maxSize];
    int top = -1;
    float cum = p;
    while (fabs(p*p-A) >= e){
        s[++top] = p;
        p = (p + A/p) / 2;
    }
    while (top != -1)
        cum *= s[top--];
    return p;
}

float sqrt_A1(float A, float p, float e){
    if (fabs(p*p-A) < e)
        return p;
    else
        return sqrt_A1(A,(p+A/p)/2,e);
}
float sqrt_A2(float A, float p, float e){
    while (fabs(p*p-A) >= e)
        p = (p + A/p) / 2;
    return p;
}
/**
 * �ܽ�ʹ��ջ����ݹ麯������·
 * @return
 */
int function(){
    // ����һ��ջ����ʼ��
   int s[maxSize];
   int top = -1;
   // ����cumʹ�õ��ڵݹ麯���ķ���ֵ
   int cum = 0;
    return 1;
 }



int main(){
    float result = 0;
    char s2[maxSize]="";
    int top2 = -1;

    char infix[] = "3*2+5-4/2";
    int len = strlen(infix);
    infixToPreFix(infix,len,s2,top2);
    cout <<infix<<" תǰ׺���ʽ����ջ���������: "<<top2<<"   ���ʽΪ��";
    printExpConversion(infix,s2);

//    char infix[] = "1+2*(3-4)+5";
    infixToPostFix(infix,s2,top2);
    cout <<infix<<" ת��׺���ʽ����ջ���������: "<<top2<<"   ���ʽΪ��";
    printExpConversion(infix,s2);

    char exp[] = "3+4*5*(2+3)";
    result = calInfix(exp);
    cout<<"��׺���ʽ "<<exp<<" ��ֵ�����"<<result<<endl;

//    char expPost[] = "34523+**+";
    char expPost[] = "345*23+*+";
    result = calPostFix(expPost);
    cout<<"��׺���ʽ "<<expPost<<" ��ֵ�����"<<result<<endl;

//    char expPre[] = "+3*4*5+23";
    char expPre[] = "-+*325/42";
    result = calPreFix(expPre);
    cout<<"ǰ׺���ʽ "<<expPre<<" ��ֵ�����"<<result<<endl;

    char brackets[] = "[()]{[]}}";
    cout <<brackets<<" �Ƿ�ƥ�䣺"<< boolalpha << isParenthesesBalanced(brackets)<<endl;

    cout << "���㺯�� F(12) = "<<cF(12)<<endl;
    cout << "�ݹ���� F(12) = "<<CF(12)<<endl;
    float A = 7,p = 3,e = 0.000001;
    cout << "����ջ�����" << A << "= " << sqrt_Stack(A,p,e)<<endl;
    cout << "�ݹ�����" << A << "= " << sqrt_A1(A,p,e)<<endl;
    cout << "�ǵݹ�����" << A << "= " << sqrt_A2(A,p,e)<<endl;
    return 0;
}
