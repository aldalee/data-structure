package DataStructure.lab.experiment01;

public class Node<T> {
    public T data;
    public Node next;
    public Node(T data,Node next){
        this.data = data;
        this.next = next;
    }
    public Node(T data){
        this(data,null);
    }
    public Node(){
        this(null,null);
    }

    @Override
    public String toString() {
        return data.toString();
    }
}
