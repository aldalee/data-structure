package DataStructure.lab.experiment02;

public class Solution{
    public static ListNode mergeTwoLists(ListNode list1, ListNode list2){
        ListNode head = null;
        if (list1 == null)
            return list2;
        if (list2 == null)
            return list1;
        if (list1.data < list2.data){
            head = list2;
            list2 = list2.next;
        }else {
            head = list1;
            list1 = list1.next;
        }
        //设置一个变量temp指向head节点，用于之后连接其它节点
        ListNode temp = head;
        while (list1 != null && list2 != null){
           if (list1.data < list2.data){
               temp.next = list2;
               list2 = list2.next;
           }else {
               temp.next = list1;
               list1 = list1.next;
           }
           temp = temp.next;
        }
        if (list1 == null)
            temp.next = list2;
        if (list2 == null)
            temp.next = list1;
        return head;
    }
    //链表长度
    public int size(ListNode list){
        int size = 0;
        while (list != null){
            size++;
            list = list.next;

        }
        return size;
    }
}