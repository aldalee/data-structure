package DataStructure.lab.experiment04;
//有问题
import java.util.Scanner;
public class TestSeqQueue {
    public static void main(String[] args) {
        SeqQueue<String> boys = new SeqQueue();
        SeqQueue<String> girls = new SeqQueue();
        System.out.println("------舞会即将开始------");
        Scanner sc = new Scanner(System.in);
        System.out.print("请输入舞会的轮数：");
        int round = sc.nextInt();
        String[] boyQueue = {"boy1","boy2","boy3","boy4","boy5"};
        String[] girlQueue = {"girl1","girl2","girl3"};
        for (int i = 0; i < boyQueue.length; i++) {
            boys.add(boyQueue[i]);
        }
        for (int i = 0; i < girlQueue.length; i++) {
            girls.add(girlQueue[i]);
        }
        int j = 0;
        int min = minLength(boys,girls);
        while (j<round){
            System.out.println("------第"+(j+1)+"轮------");
            for(int i=0;i<min;i++) {
                String boy=boys.poll();
                String girl=girls.poll();
                System.out.println("boy:"+boy+"<-->girls:"+girl);
                boys.add(boy);
                girls.add(girl);
            }
            System.out.println("第"+(j+2)+"轮第一个出场的未配对者的姓名是："+nextSeqQueue(boys,girls).peek());
            j++;
        }
        System.out.println("--------舞会结束--------");
    }
    private static int minLength(SeqQueue<String> a ,SeqQueue<String> b){
        int aLength = a.rear-a.front;
        int bLength = b.rear-b.front;
        if(aLength<bLength) {
            return aLength;
        }else {
            return bLength;
        }
    }
    private static SeqQueue nextSeqQueue(SeqQueue<String> a,SeqQueue<String> b) {
        if(a.element.length>b.element.length) {
            return a;
        }
        else {
            return b;
        }
    }
}
