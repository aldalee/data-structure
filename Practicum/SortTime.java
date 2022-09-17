package DataStructure.lab.Practicum;
/*
对不同算法的排序时间进行升序排序，可以直观的看出性能好的算法
 */
public class SortTime implements Comparable{
    String sortName;
    int sortTime;
    SortTime(int sortTime,String sortName){
        this.sortTime = sortTime;
        this.sortName = sortName;
    }
    @Override
    public int compareTo(Object o) {
        SortTime st = (SortTime) o;
        if ((this.sortTime - st.sortTime)==0)
            return 1;
        else
            return (this.sortTime - st.sortTime);
    }
}
