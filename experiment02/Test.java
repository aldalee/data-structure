package DataStructure.lab.experiment02;

/**基于已经降序的单链表进行归并操作
 */
public class Test {
    public static void main(String[] args) {
        Solution s = new Solution();
        //构造单链表1
        ListNode node11 = new ListNode(19);
        ListNode node12 = new ListNode(8);
        ListNode node13 = new ListNode(5);
        ListNode node14 = new ListNode(4);
        ListNode node15 = new ListNode(3);
        node11.setNext(node12);
        node12.setNext(node13);
        node13.setNext(node14);
        node14.setNext(node15);
        System.out.print("链表1："+"3 5 19 4 8");
        System.out.println("\n链表1长度="+s.size(node11));
        //构造单链表2
        ListNode node21 = new ListNode(10);
        ListNode node22 = new ListNode(7);
        ListNode node23 = new ListNode(5);
        ListNode node24 = new ListNode(3);
        ListNode node25 = new ListNode(2);
        node21.setNext(node22);
        node22.setNext(node23);
        node23.setNext(node24);
        node24.setNext(node25);
        System.out.print("\n链表2："+"5 10 2 7 3");
        System.out.println("\n链表2长度="+s.size(node21));
        //归并
        ListNode result = s.mergeTwoLists(node11,node21);
        System.out.print("\n合并后的链表：");
        //遍历，输出归并的单链表
        while (result != null){
            System.out.print(result.getData()+" ");
            result = result.getNext();
        }

        int size = s.size(node11);
        System.out.println("\n合并后的链表长度="+size);
    }
}
