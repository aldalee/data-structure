package DataStructure.lab.experiment07;

public class Node<T> {

    public T data;

    public Node<T> next;
    public Node() {//构造空节点
        this(null,null);
    }
    public Node(T data,Node<T>next) {//构造非空节点

        this.data =data;

        this.next = next;
    }

}
