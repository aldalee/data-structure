package DataStructure.lab.experiment01;
/*
带有虚拟头结点的链表的测试类
 */
public class TestLinkedListDemo01 {
    public static void main(String[] args) {
        LinkedList<Integer> linkedList = new LinkedList<>();
        for (int i = 0; i < 5; i++) {
            //linkedList.addFirst(i);
            linkedList.addlast(i);
        }
        System.out.println(linkedList.getFirst());
        System.out.println(linkedList);
        linkedList.toString();

    }
}
