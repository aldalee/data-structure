package DataStructure.lab.Practicum;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
import java.util.Random;
import java.util.TreeSet;

public class Sort {
    static int count_Exchange,count_Compare;    //排序算法的交换次数和比较次数记录
    public static void main(String[] args) {
        int[] arr = new int[20000];
        Random random = new Random(0);
        String path = "F:/IJ-project/cust/src/DataStructure/lab/Practicum/txt/";    //待保存文件的父目录
        String[] pathtxt = {path+"random.txt",path+"quickSort.txt",path+"shellSort.txt",path+"heapSort.txt",path+"bubbleSort.txt",path+"selectSort.txt"};       //待保存文件的文件绝对路径
        //随机生成20000个正整数
        for (int i = 0; i < arr.length; i++) {
            arr[i] = random.nextInt(arr.length);
        }
        /*
        复制数组arr,用于后面的排序
         */
        int[] arr1 = arr.clone();
        int[] arr2 = arr.clone();
        int[] arr3 = arr.clone();
        int[] arr4 = arr.clone();
        int[] arr5 = arr.clone();
        //将生成的随机数保存在random.txt文件中
        writerFile(arr,pathtxt[0]);

        /*
        <1>进行快速排序
         */
        long beginTime1 = System.currentTimeMillis();
        quickSort(arr1);
        long endTime1 = System.currentTimeMillis();
        int quickSortTime = (int) (endTime1-beginTime1);        // 计算算法所用时间
        int quickSortCountCompare = count_Compare;
        int quickSortCountExchange = count_Exchange;
        //将快速排序的结果保存在quickSort.txt文件中
        writerFile(arr1,pathtxt[1]);

        /*
        <2>进行希尔排序
         */
        count_Exchange=count_Compare=0;                     // 在进行下一个算法比较次数的统计时，要先清零
        long beginTime2 = System.currentTimeMillis();
        shellSort(arr2);
        long endTime2 = System.currentTimeMillis();
        int shellSortTime =(int) (endTime2-beginTime2);
        int shellSortCountCompare = count_Compare;
        int shellSortCountExchange = count_Exchange;
        //将希尔排序的结果保存在shellSort.txt文件中
        writerFile(arr2,pathtxt[2]);

        /*
        <3>进行堆排序
         */
        count_Exchange=count_Compare=0;
        long beginTime3 = System.currentTimeMillis();
        heapSort(arr3,false);
        long endTime3 = System.currentTimeMillis();
        int heapSortTime =(int) (endTime3-beginTime3);
        int heapSortCountCompare = count_Compare;
        int heapSortCountExchange = count_Exchange;
        //将堆排序的结果保存在heapSort.txt文件中
        writerFile(arr3,pathtxt[3]);

        /*
        <4>进行冒泡排序
         */
        count_Exchange=count_Compare=0;
        long beginTime4 = System.currentTimeMillis();
        bubbleSort(arr4);
        long endTime4 = System.currentTimeMillis();
        int bubbleSortTime = (int)(endTime4-beginTime4);
        int bubbleSortCountCompare = count_Compare;
        int bubbleSortCountExchange = count_Exchange;
        //将冒泡排序的结果保存在bubbleSort.txt文件中
        writerFile(arr4,pathtxt[4]);

        /*
        <5>进行直接选择排序
         */
        count_Exchange=count_Compare=0;
        long beginTime5 = System.currentTimeMillis();
        selectSort(arr5);
        long endTime5 = System.currentTimeMillis();
        int selectSortTime =(int) (endTime5 - beginTime5);
        int selectSortCountCompare = count_Compare;
        int selectSortCountExchange = count_Exchange;
        //将直接排序的结果保存在selectSort.txt文件中
        writerFile(arr5,pathtxt[5]);

        System.out.println("--------------------算法性能比较------------------");
        System.out.println("算法名称\t\t"+"算法时间\t\t"+"比较次数\t\t"+"交换次数\t\t");
        System.out.println("快速排序\t\t"+quickSortTime+"\t\t\t"+quickSortCountCompare+"\t\t"+quickSortCountExchange);
        System.out.println("希尔排序\t\t"+shellSortTime+"\t\t\t"+shellSortCountCompare+"\t\t"+shellSortCountExchange);
        System.out.println(" 堆排序\t\t"+heapSortTime+"\t\t\t"+heapSortCountCompare+"\t\t"+heapSortCountExchange);
        System.out.println("冒泡排序\t\t"+bubbleSortTime+"\t        "+bubbleSortCountCompare+"\t"+bubbleSortCountExchange);
        System.out.println("直接选择排序\t"+selectSortTime+"\t\t\t"+selectSortCountCompare+"\t"+selectSortCountExchange);
        System.out.println("-------优良算法排序(按照排序时间为基准)-------");
        //各种排序算法所用的时间
        int[] time = {quickSortTime,shellSortTime,heapSortTime,bubbleSortTime,selectSortTime};
        //对应的算法名称
        String[] name = {"快速排序","希尔排序","堆排序","冒泡排序","直接选择排序"};
        /*
        利用TreeSet集合，将算法名称和排序所用时间关联起来，并升序输出，直观的看出性能好的算法
         */
        TreeSet<SortTime> treeSet = new TreeSet<>();
        SortTime key[] = new SortTime[5];
        for (int i = 0; i < key.length; i++) {
            key[i] = new SortTime(time[i],name[i]); //创建对象
            treeSet.add(key[i]);    // 添加到集合
        }
        Iterator<SortTime> te = treeSet.iterator();
        while (te.hasNext()){
            SortTime sortTime = te.next();
            System.out.println(""+sortTime.sortName+":"+sortTime.sortTime);
        }

    }

    //交换方法,实现交换功能的同时，进行交换次数的记录
    public static void swap(int[] keys,int i,int j){
        count_Exchange++;
        int temp = keys[j];
        keys[j] = keys[i];
        keys[i] = temp;
    }
    //比较方法,实现比较功能的同时，进行比较次数的记录
    public static boolean compare(int max,int min){
        count_Compare++;
        return max>=min ? true : false;
    }

    //将数据保存在.txt文件中
    public static void writerFile(int[] arr,String path){
        File file = new File(path);
        try{
            if (!file.exists())
                file.createNewFile();
            BufferedWriter bw = new BufferedWriter(new FileWriter(file));
            for (int i = 0; i < arr.length; i++) {
                bw.write(String.valueOf(arr[i])+"\t\t");
                if ((i+1)%100==0)
                    bw.write("\n");
            }
            bw.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    /*
   <1>快速排序
    */
    public static void quickSort(int[] keys){
        quickSort(keys, 0, keys.length-1);
    }

    //对存于keys数组begin～end之间的子序列进行一趟快速排序，递归算法
    private static void quickSort(int[] keys, int begin, int end){
        //序列有效
        if (begin>=0 && begin<keys.length && end>=0 && end<keys.length && begin<end){
            int i=begin, j=end;                    //i、j下标分别从子序列的前后两端开始
            int vot=keys[i];                       //子序列第一个值作为基准值
            while (i!=j){
                while (i<j && compare(keys[j],vot))        //（升序）从后向前寻找较小值，不移动与基准值相等元素
//                while (i<j && vot>=keys[j])      //（降序）从后向前寻找较大值，不移动与基准值相等元素
                    j--;
                if (i<j){
                    keys[i++]=keys[j];                 //子序列后端较小元素向前移动
                    count_Exchange++;
                }

                while (i<j && compare(vot,keys[i]))           //（升序）从前向后寻找较大值，不移动与基准值相等元素
//                while (i<j && keys[i]>=vot)        //（降序）从前向后寻找较小值，不移动与基准值相等元素
                    i++;
                if (i<j){
                    keys[j--]=keys[i];    //子序列前端较大元素向后移动
                    count_Exchange++;
                }

            }
            keys[i]=vot;           //基准值到达最终位置
            //System.out.print(begin+".."+end+"\tvot="+vot+"\t");

            //System.out.println(Arrays.toString(keys));
            quickSort(keys, begin, j-1);        //前端子序列再排序，递归调用
            quickSort(keys, i+1, end);         //后端子序列再排序，递归调用
        }
    }

    /*
    <2>希尔排序
     */
    public static void shellSort(int[] keys){       //希尔排序，升序，增量减半
        for (int delta = keys.length/2; delta > 0 ; delta/=2) {     //控制增量每趟减半
            for (int i = delta; i < keys.length; i++) {         //一趟分若干组，每组直接插入排序
                int temp = keys[i],j;           //keys[i]是当前待插入元素
                for (j = i-delta;j>=0 && compare(keys[j],temp);j-=delta){       //组内直接插入排序，寻找插入位置
                    keys[j+delta] = keys[j];        //每组元素相距delta远
                    count_Exchange++;
                }
                keys[j+delta] = temp;       //插入元素
            }
            //System.out.print("datla="+delta+"\t"+ Arrays.toString(keys)+"\n");
        }
    }

    /*
    <3>堆排序
     */
    public static void heapSort(int[] keys){
        heapSort(keys,true);
    }
    //堆排序，当minheap为true时，创建最小堆，降序排序；否则创建最大堆，升序排序
    public static void heapSort(int[] keys,boolean minheap){
        for(int i = keys.length/2-1; i>=0; i--)
            sift(keys,i,keys.length-1,minheap);
        for (int i = keys.length-1; i>0; i--){
            swap(keys,0,i);
            sift(keys,0,i-1,minheap);
        }
    }
    //将keys数组中以parent为根的子树调整成最小/大堆，子序列范围为parent～end。
    private static void sift(int[] keys, int parent, int end, boolean minheap) {
//        System.out.print("sift\t"+parent+".."+end+"\t");
        int child = 2*parent +1;
        int value = keys[parent];
        while (child<=end){
            if (child<end && (minheap ? compare(keys[child],keys[child+1]) : compare(keys[child+1],keys[child])))
                child++;
            if (minheap ? compare(value,keys[child]) : compare(keys[child],value)){
                keys[parent] = keys[child];
                parent = child;
                child = 2* parent+1;
            }
            else
                break;
        }
        keys[parent]=value;
//        System.out.println(Arrays.toString(keys));
    }

    /*
    <4>冒泡排序
     */
    public static void bubbleSort(int[] keys){
        bubbleSort(keys,true);
    }

    private static void bubbleSort(int[] keys, boolean asc) {       // 冒泡排序，若asc为true，升序，否则降序
//        System.out.println("冒泡排序 ("+(asc?"升":"降")+"序)");
        boolean exchange = true;
        for (int i = 1; i < keys.length && exchange; i++) {
            exchange = false;
            for (int j = 0; j < keys.length-i; j++) {
                if (asc ? compare(keys[j],keys[j+1]):compare(keys[j+1],keys[j])){       //相邻元素比较，若反序，则交换
                    swap(keys,j,j+1);
                    exchange = true;                // 有交换
                }
            }
//            System.out.print("第"+i+"趟\t");
//            System.out.println(Arrays.toString(keys));
        }
    }

    /*
    <5>直接选择排序
     */
    public static void selectSort(int[] keys){
        for (int i = 0; i < keys.length-1; i++) {       // n-1趟排序
            int min = i;
            for (int j = i+1;j<keys.length;j++){
                if (compare(keys[min],keys[j]))         // 每趟在keys[i]开始的子序列中寻找最小元素
                    min = j;                            // 记住本趟最小元素下标
            }
            if (min!=i)
                swap(keys,i,min);
//            System.out.print("第"+(i+1)+"趟\t");
//            System.out.println(Arrays.toString(keys));
        }
    }
}
