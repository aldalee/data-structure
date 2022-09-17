package DataStructure.lab.experiment01;

public class LinkedList<T> {
    private Node dummyHead; //虚拟节点
    private int size;   //存储链表中元素个数
    public LinkedList(){
        dummyHead = new Node();
        size = 0;
    }
    //获取链表中的元素个数
    public int getSize(){
      return size;
    }
    //返回链表是否为空
    public boolean isEmpty(){
        return this.size == 0;
    }
    //在链表头添加新的元素
    public void addFirst(T data){
        add(0,data);
    }
   /*
   public void addFirst(T t){
        Node node = new Node(e);
        node.next = head;
       head = node;
    //head = new Node(t,head);    //等价于上面的三条代码
    //size ++;
    }
    */
    //在链表的index(0-based)位置添加新的元素data
    public void add(int index,T data){
        if (index < 0 || index > size)
            throw new IllegalArgumentException("Add failed. Illegal index.");
            Node prev = dummyHead;
            for (int i = 0; i < index; i++) {
                prev = prev.next;
            }
            /*
            Node node = new Node(data);
            node.next = prev.next;
            prev.next = node;
             */
            prev.next = new Node(data,prev.next);   //等价于上面的三条代码
            size ++;
    }
    //在链表末尾添加新的元素data
    public void addlast(T data){
        add(size,data);
    }
    // 获得链表的第index(0-based)个位置的元素
    public T get(int index){
        if (index < 0 || index >= size)
            throw new IllegalArgumentException("Get failed. Illegal index.");
        Node cur = dummyHead.next;
        for (int i = 0; i < index; i++) {
            cur = cur.next;
        }
        return (T)cur.data;
    }
    // 获取链表的第一个元素
    public T getFirst(){
        return get(0);
    }
    // 获取链表的最后一个元素
    public T getLast(){
        return get(size - 1);
    }
    // 修改链表的第index(0-based)个位置的元素为e
    public void set(int index ,T data){
        if (index <0 || index >=size)
            throw new IllegalArgumentException("Set failed. Illegal index.");
        Node cur = dummyHead.next;
        for (int i = 0; i < index; i++) {
            cur = cur.next;
        }
        cur.data = data;
    }
    // 查找链表中是否有元素e
    public boolean contains(T data){
        Node cur = dummyHead.next;
        while (cur != null){
            if (cur.data.equals(data))
                return true;
            cur = cur.next;
        }
        return false;
    }
    // 从链表中删除index(0-based)位置的元素, 返回删除的元素
    public T remove(int index){
        if (index <0 || index >=size)
            throw new IllegalArgumentException("Remove failed. Illegal index.");
        Node prev = dummyHead;
        for (int i = 0; i < index; i++) {
            prev = prev.next;
        }
        Node retNode = prev.next;
        prev.next = retNode.next;
        retNode.next = null;
        size --;
        return (T)retNode.data;
    }
    // 从链表中删除第一个元素, 返回删除的元素
    public T removeFirst(){
        return remove(0);
    }
    // 从链表中删除最后一个元素, 返回删除的元素
    public T removeLast(){
        return remove(size - 1);
    }
    // 从链表中删除元素e
    public void removeElement(T data){
        Node prev = dummyHead;
        while (prev.next != null){
            if (prev.next.data.equals(data))
                break;
            prev = prev.next;
        }
        if (prev.next != null){
            Node delNode = prev.next;
            prev.next = delNode.next;
            delNode.next = null;
            size --;
        }
    }
    @Override
    public String toString() {
        StringBuffer res = new StringBuffer();
        Node cur = dummyHead.next;
        while (cur != null){
            res.append(cur +"->");
            cur = cur.next;
        }
        res.append("NULL");
        return res.toString();
    }
}
