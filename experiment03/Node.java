package DataStructure.lab.experiment03;

public class Node<T> {      //T指定结点的元素类型
    public T data;          //数据域，存储数据元素
    public Node<T> next;    //地址域，引用后继结点
    public Node(T data,Node<T> next){
        this.data=data;
        this.next=next;
    }
    public Node(){
        this(null,null);
    }
    //返回结点数据域的描述字符串
    public String toString(){
        return this.data.toString();
    }
}
