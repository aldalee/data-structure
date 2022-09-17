/**
 * Created by lhy on 2021/3/26 16:08
 * Description:
 */
#include <iostream>
#include <cstring>
#include "tools.h"
#define maxSize 100
#define MIN 0.00000001
using namespace std;
/*���Ľṹ�嶨��*/
struct Branch{
    int cIdx;
    Branch *next;
};
struct TNode{
    int data;
    Branch *first;
};
/*�������Ľṹ�嶨��*/
struct BTNode{
    char data;
    BTNode *lChild;
    BTNode *rChild;
};
/*�����������ṹ�嶨��*/
struct TBTNode{
    int data;
    int lTag;   // lTag=0:lChildָ������  lTag=1��lChildָ��ǰ��
    int rTag;   // rTag=0:rChildָ���Һ���  rTag=1��rChildָ����
    TBTNode *lChild;
    TBTNode *rChild;
};

void visit(TNode *pNode);
void visit(BTNode *pNode);
void visit(TBTNode *pNode);
BTNode *initBT(char arr[],int first);
int search(char arr[],char key,int L,int R);
void getSubLevel(char subLevel[], char level[], char in[], int n, int L, int R);
int calSub(float opand1,char op, float opand2, float &result);
char getPriority(char op);
/**
 * ������������� �ݹ�ʵ��
 * @param p
 */
void preOrder(BTNode *p){
    if (p != nullptr){
        visit(p);
        preOrder(p->lChild);
        preOrder(p->rChild);
    }
}
/**
 * ������������� �ݹ�ʵ��
 * @param p
 */
void inOrder(BTNode *p){
    if (p != nullptr){
        inOrder(p->lChild);
        visit(p);
        inOrder(p->rChild);
    }
}
/**
 * ������������� �ݹ�ʵ��
 * @param p
 */
void postOrder(BTNode *p){
    if (p != nullptr){
        postOrder(p->lChild);
        postOrder(p->rChild);
        visit(p);
    }
}

/**
 * ������������� �ǵݹ�ʵ��
 * @param bt
 */
void preOrderNonRecursion(BTNode *bt){
    if (bt != nullptr){
        BTNode *stack[maxSize];
        int top = -1;
        BTNode *p = nullptr;
        stack[++top] = bt;
        while (top != -1){
            p = stack[top--];
            visit(p);
            if (p->rChild != nullptr)
                stack[++top] = p->rChild;
            if (p->lChild != nullptr)
                stack[++top] = p->lChild;
        }
    }
}
/**
 * ������������� �ǵݹ�ʵ��
 * @param bt
 */
void postOrderNonRecursion(BTNode *bt){
    if (bt != nullptr){
        BTNode *stack1[maxSize];
        int top1 = -1;
        BTNode *stack2[maxSize];
        int top2 = -1;
        BTNode *p = nullptr;
        stack1[++top1] = bt;
        while (top1 != -1){
            p = stack1[top1--];
            stack2[++top2] = p;
            if (p->lChild != nullptr)
                stack1[++top1] = p->lChild;
            if (p->rChild != nullptr)
                stack1[++top1] = p->rChild;
        }
        while (top2 != -1){
            p = stack2[top2--];
            visit(p);
        }
    }
}
/**
 * ������������� �ǵݹ�ʵ��
 * @param bt
 */
void inOrderNonRecursion(BTNode *bt){
    if (bt != nullptr){
        BTNode *stack[maxSize];
        int top = -1;
        BTNode *p = nullptr;
        p = bt;
        while (top != -1 || p != nullptr){
            while (p != nullptr){
                stack[++top] = p;
                p = p->lChild;
            }
            if (top != -1){
                p = stack[top--];
                visit(p);
                p = p->rChild;
            }
        }
    }
}
/**
 * �������Ĳ�α���
 * @param bt
 */
void level(BTNode *bt){
    if (bt != nullptr){
        int front,rear;
        BTNode *que[maxSize];
        front = rear = 0;
        BTNode *p;
        rear = (rear+1) % maxSize;
        que[rear] = bt;
        while (front != rear){
            front = (front+1) % maxSize;
            p = que[front];
            visit(p);
            if (p->lChild != nullptr){
                rear = (rear+1) % maxSize;
                que[rear] = p->lChild;
            }
            if (p->rChild != nullptr){
                rear = (rear+1) % maxSize;
                que[rear] = p->rChild;
            }
        }
    }
}

/**
 * ������������
 * @param p
 * @param pre
 */
void createThread(TBTNode *p,TBTNode *&pre){
    if (p->lChild == nullptr){
        p->lChild = pre;
        p->lTag = 1;
    }
    if (pre != nullptr && pre->rChild == nullptr){
        pre->rChild = p;
        pre->rTag = 1;
    }
    pre = p;
}
/**
 * ��������Զ�����������
 * @param p
 * @param pre
 */
void inThread(TBTNode *p,TBTNode *&pre){
    if (p != nullptr){
        inThread(p->lChild,pre);
        createThread(p,pre);
        inThread(p->rChild,pre);
    }
}

void createInThread(TBTNode *root){
    TBTNode *pre = nullptr;
    if (root != nullptr){
        inThread(root,pre);
        pre->rChild = nullptr;
        pre->rTag = 1;
    }
}

/**
 * ǰ������Զ�����������
 * @param p
 * @param pre
 */
void preThread(TBTNode *p,TBTNode *&pre){
    if (p != nullptr){
        createThread(p,pre);
        if (p->lTag == 0)
            preThread(p->lChild,pre);
        if (p->rTag == 0)
            preThread(p->rChild,pre);
    }
}

/**
 * ��������Զ�����������
 * @param p
 * @param pre
 */
void postThread(TBTNode *p,TBTNode *&pre){
    if (p != nullptr){
        postThread(p->lChild,pre);
        postThread(p->rChild,pre);
        createThread(p,pre);
    }
}

/**
 * �� p Ϊ�������������������У����������µĵ�һ������㷨
 * @param p
 * @return
 */
TBTNode *first(TBTNode *p){
    while (p->lTag == 0)
        p = p->lChild;
    return p;
}
/**
 * �����������������У����p�������µĺ�̽���㷨
 * @param p
 * @return
 */
TBTNode *next(TBTNode *p){
    if (p->rTag == 0)
        return first(p->rChild);
    else
        return p->rChild;
}
/**
 * �����������������У����p�������µ�ǰ������㷨
 * @param p
 * @return
 */
TBTNode *prior(TBTNode *p){
    if (p->lTag == 0)
        return first(p->lChild);
    else
        return p->lChild;
}
/**
 * �� p Ϊ�������������������У����������µ����һ������㷨
 * @param p
 * @return
 */
TBTNode *last(TBTNode *p){
    while (p->rTag == 0)
        p = p->rChild;
    return p;
}

/**
 * �������������� �������
 * @param tbt
 */
void inOrder(TBTNode *tbt){
    for(TBTNode *p = first(tbt); p != nullptr; p = next(p))
        visit(p);
}
/**
 * ǰ���������������� ǰ�����
 * @param tbt
 */
void preOrder(TBTNode *tbt){
    if (tbt != nullptr){
        TBTNode *p = tbt;
        while (p != nullptr){
            while (p->lTag == 0){
                visit(p);
                p = p->lChild;
            }
            visit(p);
            p = p->rChild;
        }
    }
}
/**
 * ������������������ �������
 * @param tbt
 */
void postOrder(TBTNode *tbt){

}

/**
 * �����������
 * @param p
 * @param tree
 */
void preOrder(TNode *p,TNode tree[]){
    if (p != nullptr){
        visit(p);
        Branch *q = p->first;
        while (q != nullptr){
            preOrder(&tree[q->cIdx], tree);
            q = q->next;
        }
    }
}
/**
 * ���ĺ������
 * @param p
 * @param tree
 */
void postOrder(TNode *p,TNode tree[]){
    if (p != nullptr){
        Branch *q = p->first;
        while (q != nullptr){
            postOrder(&tree[q->cIdx], tree);
            q = q->next;
        }
        visit(p);
    }
}
/**
 * ���Ĳ�α���
 * @param tn
 * @param tree
 */
void level(TNode *tn,TNode tree[]){
    int front,rear;
    TNode *que[maxSize];
    front = rear = 0;
    TNode *p;
    if (tn != nullptr){
        rear = (rear+1) % maxSize;
        que[rear] = tn;
        while (front != rear){
            front = (front+1) % maxSize;
            p = que[front];
            visit(p);
            Branch *q = p->first;
            while (q != nullptr){
                rear = (rear+1) % maxSize;
                que[rear] = &tree[q->cIdx];
                q = q->next;
            }
        }
    }
}
/**
 * ���� ���� �� ���� �������� ����������
 * @param pre   �����������
 * @param in    �����������
 * @param L1    ����������б仯��Χ
 * @param R1
 * @param L2    ����������б仯��Χ
 * @param R2
 * @return      ���������ڵ�
 */
BTNode *createBTbyPreAndIn(char pre[],char in[],int L1,int R1,int L2,int R2){
    if (L1 > R1)
        return nullptr;
    BTNode *s = initBT(pre,L1);
    int i;
    for (i = L2; i < R2; ++i) {
        if (in[i] == pre[L1])
            break;
    }
    s->lChild = createBTbyPreAndIn(pre,in,L1+1,L1+i-L2,L2,i-1);
    s->rChild = createBTbyPreAndIn(pre,in,L1+i-L2+1,R1,i+1,R2);
    return s;
}
/**
 * ���� ���� �� ���� �������� ����������
 * @param pre   �����������
 * @param in    �����������
 * @param L1    ����������б仯��Χ
 * @param R1
 * @param L2    ����������б仯��Χ
 * @param R2
 * @return      ���������ڵ�
 */
BTNode *createBTbyPostAndIn(char post[],char in[],int L1,int R1,int L2,int R2){
    if (L1 > R1)
        return nullptr;
    BTNode *s = initBT(post,R1);
    int i;
    for (i = L2; i < R2; ++i) {
        if (in[i] == post[R1])
            break;
    }
    s->lChild = createBTbyPostAndIn(post,in,L1,L1+i-L2-1,L2,i-1);
    s->rChild = createBTbyPostAndIn(post,in,L1+i-L2,R1-1,i+1,R2);
    return s;
}
/**
 * �� ��� �� ���� �������� ����������
 * @param level     ��α�������
 * @param in        �����������
 * @param n         ���鳤��
 * @param L
 * @param R
 * @return
 */
BTNode *createBTbyLevAndIn(char level[],char in[],int n,int L,int R){
    if (L > R)
        return nullptr;
    BTNode *s = initBT(level,0);
    int i = search(in,level[0],L,R);
    int LN = i-L;
    char LLevel[LN];
    int RN = R-i;
    char RLevel[RN];
    getSubLevel(LLevel,level,in,n,L,i-1);
    getSubLevel(RLevel,level,in,n,i+1,R);
    s->lChild = createBTbyLevAndIn(LLevel,in,LN,L,i-1);
    s->rChild = createBTbyLevAndIn(RLevel,in,RN,i+1,R);
    return s;
}
/**
 *  ���ö��������б��ʽ��ֵ
 *  ���ô˺�����ʱ��BT�ṹ��data�޸�����
 * @param root
 * @return
 */
float cal(BTNode *root){
    if (root->lChild == nullptr && root->rChild == nullptr)
        return root->data - '0';
    else{
        float opand1 = cal(root->rChild);
        float opand2 = cal(root->rChild);
        float result;
        calSub(opand1,root->data,opand2,result);
        return result;
    }
}
/*�ú���δ����2021/3/28  ����ջ���� ������*/
void createExpBT(){

}
bool isCh(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')';
}
/*�ú���δ����2021/3/28*/
void initExpBT(char exp[]){
    char expStack[maxSize];
    int expTop = -1;
    char opStack[maxSize];
    int opTop = -1;
    int i = 0;
    char theta ;
    while (exp[i] != '\0'){
        if (!isCh(exp[i])){
            createExpBT();
            expStack[++expTop] = theta;
            ++i;
        } else{
            switch (opStack[opTop],exp[i]){
                case '<':
                    opStack[++opTop] = exp[i++];
                    break;
                case '=':
                    opTop--;
                    i++;
                    break;
                case '>':
                    theta = opStack[opTop--];
                    int a = expStack[expTop--];
                    int b = expStack[expTop--];
                    createExpBT();
                    expStack[++expTop] = theta;
                    break;
            }
        }
    }
}
void visit(TNode *pNode) {
    cout << pNode->data<<" ";
}
void visit(BTNode *pNode) {
    cout << pNode->data<<" ";
}
void visit(TBTNode *pNode){

}
BTNode *initBT(char arr[],int first){
    BTNode *s = (BTNode*)malloc(sizeof(BTNode));
    s->lChild = s->rChild = nullptr;
    s->data = arr[first];
    return s;
}
int search(char arr[],char key,int L,int R){
    for (int idx = L; idx <= R ; ++idx) {
        if (arr[idx] == key)
            return idx;
    }
    return -1;
}
void getSubLevel(char subLevel[], char level[], char in[], int n, int L, int R) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (search(in,level[i],L,R) != -1)
            subLevel[k++] = level[i];
    }
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
char getPriority(char op){
    if (op == '+' || op == '-')
        return '<';
    else if (op == '*' || op == '/')
        return '>';
    else
        return '=';
}
void printTree_impl(BTNode* n, bool left, string const& indent){
    if (n->rChild)
        printTree_impl(n->rChild, false, indent + (left ? "|     " : "      "));
    cout << indent;
    cout << (left ? '\\' : '/');
    cout << "-----";
    cout << n->data << endl;
    if (n->lChild)
        printTree_impl(n->lChild, true, indent + (left ? "      " : "|     "));
}
void printTree(BTNode* root){
    if (root->rChild)
        printTree_impl(root->rChild, false, "");
    cout << root->data << endl;
    if (root->lChild)
        printTree_impl(root->lChild, true, "");
}

int main(){
    BTNode *bt,*bt2,*bt3;
    char pre[] = "ABDECMFGH";
    char in[] = "DBEAMCGFH";
    char post[] = "DEBMGHFCA";
    char lev[] = "ABCDEMFGH";
    char exp[] = "3+4*5*(2+3)";
    int L1,R1,L2,R2,L,R;
    L1 = L2 = L = 0;
    R1 = R2 = R = -1;
    R1 += strlen(pre);
    R2 += strlen(in);
    R += strlen(lev);
    bt = createBTbyPreAndIn(pre,in,L1,R1,L2,R2);
    bt2 = createBTbyPostAndIn(post,in,L1,R1,L2,R2);
    bt3 = createBTbyLevAndIn(lev,in,strlen(lev),L,R);
    printTree(bt);
    printTree(bt2);
    printTree(bt3);

    cout <<"�����������:";
    preOrderNonRecursion(bt);
    cout <<"\n�����������:";
    inOrderNonRecursion(bt);
    cout <<"\n�����������:";
    postOrderNonRecursion(bt);
    cout <<"\n��α�������:";
    level(bt);
    return 0;
}