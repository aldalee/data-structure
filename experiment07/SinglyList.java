package DataStructure.lab.experiment07;

public class SinglyList<T> extends Object {
    public Node<T> head;
    public SinglyList()
    {
        this.head=new Node<T>();
    }
    public boolean isEmpty()
    {
        return this.head.next==null;
    }
    public String toString()
    {
        String str="(";
        for(Node<T> p=this.head.next;p!=null;p=p.next)
        {
            str+=p.data.toString();
            if(p.next!=null)
                str+=",";
        }
        return str+")";
    }
    public Node<T> insert(int i,T x)
    {
        if(x==null)
            throw new NullPointerException("x==null");
        Node<T> front=this.head;
        for(int j=0;front.next!=null&&j<i;j++)
            front=front.next;
        front.next=new Node<T>(x,front.next);
        return front.next;
    }
}
