package DataStructure.lab.experiment03;
/*
顺序表
 */
public class SeqList<T> {

    protected Object[]element;  //对象数组存储顺序表的数据元素
    protected int n;            //顺序表元素个数

    //构造容量为length的空表
    public SeqList(int length){
        if (length<0)
            throw new NegativeArraySizeException("error:"+length);
        this.element=new Object[length];
        this.n=0;
    }
    //创建默认容量的空表
    public SeqList(){
        this(64);
    }
    //构造顺序表，由values数组提供元素
    public SeqList(T[] values){
        this(values.length);        //创建容量为values.length的空表
        //复制数组元素
        for (int i = 0; i <values.length ; i++) {
            this.element[i]=values[i];
        }
        this.n=element.length;
    }
    public boolean isEmpty(){
        return this.n==0;
    }
    public int size(){
        return this.n;
    }
    public T get(int i){
        if(i>=0&&i<this.n)
            return (T)this.element[i];
        return null;
    }
    public String toString(){
        String str ="[";
        if(this.n>0)
            str+=this.element[0].toString();
        for (int i = 1; i <this.n ; i++) {
            str+=","+this.element[i].toString();
        }
        return str+"]";
    }
    /*
    顺序表插入算法
     */
    public int insert(int i,T x) {
        if (x==null)
            throw new NullPointerException("x==null");
        if(i<0)
            i=0;
        if(i>this.n)
            i=this.n;
        Object[] source=this.element;
        if (this.n==element.length){
            this.element=new Object[source.length*2];
            for (int j = 0; j <i ; j++)
                this.element[j]=source[j];
        }
        //从i开始至表尾的元素向后移动，次序从后向前
        for (int j =this.n-1; j >=i ; j--)
            this.element[j+1]=source[j];
        this.element[i]=x;
        this.n++;
        return i;
    }
    public int insert(T x){
        return this.insert(this.n,x);
    }
    //插入不重复元素。查找不成功时尾插入
    public int insertDifferent(int i,T x){
        for (int j = 0; j < this.n; j++) {
            if (x.equals(this.element[j]))
                return this.insert(x);
        }
        return this.insert(i,x);
    }
    /*
    顺序表删除算法
     */
    public T remove(int i){
        if (this.n>0 && i>=0 && i<this.n){
            T old = (T)this.element[i];
            for (int j = i; j < this.n-1; j++) {
                this.element[j] = this.element[j+1];
            }
            this.element[this.n-1] = null;
            this.n--;
            return old;
        }
        return null;
    }
    //删除首次出现的与key相等的元素，返回被删除的元素，查找不成功返回null
    public T remove(T key){
        for (int i = 0; i <this.n ; i++) {
            if (key.equals(this.element[i]))
                this.remove(i);
        }
        return null;
    }
    public void clear(){
        this.n=0;   //设置长度未0,未释放数组空间
    }
    /*
    顺序表的更改算法
     */
    public void set(int i,T x){
        if (x==null)
            throw new NullPointerException("x==null");
        if (i<0 || i>=this.n)
            throw new IndexOutOfBoundsException("error:"+i);
        for (int j = 0; j < this.n; j++) {
            if (j==i)
                this.element[j]=x;
        }
    }
    /*
    顺序表查找算法
     */
    public int search(T key){
        for (int i = 0; i <this.n ; i++) {
            if (key.equals(this.element[i]))
                return i;
        }
        return -1;
    }
    //判断是否包含关键字为key的元素
    public boolean contains(T key){
        return this.search(key)!=-1;
    }

}
