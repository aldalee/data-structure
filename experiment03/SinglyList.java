package DataStructure.lab.experiment03;

public class SinglyList<T> extends Object {
    public Node<T> head;    //头指针，指向单链表的头结点
    public SinglyList(){
        this.head = new Node<T>();
    }
    //构造单链表，由value数组提供元素
    public SinglyList(T[] values){
        this();
        Node<T> rear=this.head;
        for (int i = 0; i < values.length; i++) {
            rear.next = new Node<T>(values[i],null);
            rear = rear.next;
        }
    }
    public String toString(){
        String string = "[";
        for(Node<T> p =this.head.next;p != null;p=p.next){
            string += p.data.toString();
            if (p.next != null)
                string += ",";
        }
        return string + "]";
    }
    /*
    递归实现单链表查找
     */
    public Node<T> search(Node<T> p,T value){
        //Node<T> p = head;
        //p=p.next;
        if (p == null || p.data.equals(value))   //边界条件
            return p;
        else
            return search(p.next,value);         //递推通式
    }
    public boolean isEmpty() {
        return this.head.next == null;
    }
    public Node<T> insert(int i, T x) {
        if (x == null)
            throw new NullPointerException("x==null");
        Node<T> front=this.head;
        for (int j = 0;front.next != null && j < i; j++) {
            front = front.next;
        }
        front.next = new Node<T>(x,front.next);
        return front.next;
    }
    public Node<T> insert(T x){
        return insert(Integer.MAX_VALUE,x);
    }
    public T get(int i) {
        Node<T> p =this.head.next;
        for (int j = 0;p != null && j < i; j++) {
            p = p.next;
        }
        return (i >= 0 && p != null) ? p.data:null;
    }
    public T remove(int i) {
        Node<T> front = this.head;
        for (int j = 0;front.next != null && j < i; j++) {
            front = front.next;
        }
        if (i >= 0 && front.next != null){
            T old = front.next.data;
            front.next = front.next.next;
            return old;
        }
        return null;
    }
}
