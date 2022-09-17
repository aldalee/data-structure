package DataStructure.lab.experiment08;

import java.util.Arrays;

public class BinarySearch {

    public static void main(String[] args) {
        System.out.println("---------快速排序(升序)--------");
        int[] arr = {3,17,12,61,8,70,97,75,53,26,54,61};
        System.out.println("快速排序前："+Arrays.toString(arr)+"\n");
        long startTime = System.currentTimeMillis();
        quickSort(arr);
        long endTime = System.currentTimeMillis();
        System.out.println("\n快速排序后："+Arrays.toString(arr));
        System.out.println("运行时间"+(endTime-startTime));

        System.out.println("---------希尔排序(升序)---------");
        int[] arr1 = {3,17,12,61,8,70,97,75,53,26,54,61};
        System.out.println("\n希尔排序前："+Arrays.toString(arr1)+"\n");
        shellSort(arr1);
        System.out.println("\n希尔排序后："+Arrays.toString(arr1)+"\n");

        int[] list = {10,20,30,40,50,60,70,80,90};
        System.out.println("\n元素集合为"+ Arrays.toString(list));

        System.out.println("---------非递归查找---------");
        int i = binarySearch(list,90);
        showSearch(i,46);
        i = binarySearch(list,35);
        showSearch(i,35);

        System.out.println("---------递归查找---------");
        int key = 90;
        int aimIndex = BinSreachOfRecursion(list,0,list.length-1,key);
        showSearch(aimIndex,key);
        aimIndex = BinSreachOfRecursion(list,0,list.length-1,35);
        showSearch(aimIndex,35);

    }
    //非递归实现
    public static int binarySearch(int[] list,int key) {
        int low = 0;
        int high = list.length - 1;
        while (high >= low) {
            int mid = (low + high) / 2;
            if (key < list[mid])
                high = mid - 1;
            else if (key == list[mid])
                return mid;
            else
                low = mid + 1;
        }
        return -1;
    }
    //递归实现
    public static int BinSreachOfRecursion(int[] arr, int start, int end,int key) {
        if(arr == null) {
            return -1;
        }
        if(start > end) {
            return -1;
        }
//        int mid = (end - start)/2 + start;
        int mid = (start+end)/2;
        if(arr[mid] > key) {
            return BinSreachOfRecursion(arr, start, mid-1, key);
        } else if(arr[mid] < key) {
            return BinSreachOfRecursion(arr, mid+1, end, key);
        } else {
            return mid;
        }
    }
    //快速排序
    public static void quickSort(int[] keys){
        quickSort(keys, 0, keys.length-1);
    }

    //对存于keys数组begin～end之间的子序列进行一趟快速排序，递归算法
    private static void quickSort(int[] keys, int begin, int end){
        int count = 0;      //统计比较次数
        //序列有效
        if (begin>=0 && begin<keys.length && end>=0 && end<keys.length && begin<end){

            int i=begin, j=end;                    //i、j下标分别从子序列的前后两端开始
            int vot=keys[i];                       //子序列第一个值作为基准值
            while (i!=j){
                while (i<j && keys[j]>=vot)        //（升序）从后向前寻找较小值，不移动与基准值相等元素
//                while (i<j && vot>=keys[j])      //（降序）从后向前寻找较大值，不移动与基准值相等元素
                    j--;
                if (i<j)
                    keys[i++]=keys[j];                 //子序列后端较小元素向前移动
                while (i<j && keys[i]<=vot)           //（升序）从前向后寻找较大值，不移动与基准值相等元素
//                while (i<j && keys[i]>=vot)        //（降序）从前向后寻找较小值，不移动与基准值相等元素
                    i++;
                if (i<j)
                    keys[j--]=keys[i];    //子序列前端较大元素向后移动
            }
            keys[i]=vot;           //基准值到达最终位置
            System.out.print(begin+".."+end+"\tvot="+vot+"\t");

            System.out.println(Arrays.toString(keys));
            quickSort(keys, begin, j-1);        //前端子序列再排序，递归调用
            quickSort(keys, i+1, end);         //后端子序列再排序，递归调用
        }
    }
    //希尔排序
    public static void shellSort(int[] keys){
        for (int delta = keys.length/2; delta > 0 ; delta/=2) {
            for (int i = delta; i < keys.length; i++) {
                int temp = keys[i],j;
                for (j = i-delta;j>=0 && temp < keys[j];j-=delta)
                    keys[j+delta] = keys[j];
                keys[j+delta] = temp;
            }
            System.out.print("datla="+delta+"\t"+Arrays.toString(keys)+"\n");
        }
    }

    //查找结果
    public static void showSearch(int index,int key){
        if (index >= 0) {
            System.out.println("查找的元素\""+key+"\"的索引："+index);
        } else {
            System.out.println("查找的元素\""+key+"\"不存在！");
        }
    }
}