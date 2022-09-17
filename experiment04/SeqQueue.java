package DataStructure.lab.experiment04;

public class SeqQueue<T> implements Queue<T> {
    public Object element[];   //存储队列元素的数组
    public int front,rear;     //front,rear分别为队列头尾下表
    //构造容量为length的空队列
    public SeqQueue(int length){
        if (length<64)
            length = 64;
        this.element = new Object[length];
        this.front=this.rear=0;
    }
    public SeqQueue(){
        this(64);
    }
    @Override
    public boolean isEmpty() {
        return this.front==this.rear;
    }
    @Override
    public boolean add(T x) {
        if (x==null)
            return false;
        //若队列满，则扩容
        if (this.front==(this.rear+1)%this.element.length){
            Object[] temp = this.element;
            this.element = new Object[temp.length*2];
            int j=0;
            for(int i=this.front;i!=this.rear;i=(i+1)%temp.length)
                this.element[j++]=temp[i];
            this.front=0;
            this.rear=j;
        }
        this.element[this.rear]=x;
        this.rear=(this.rear+1)%this.element.length;
        return true;
    }
    @Override
    public T peek() {   //返回队头元素，没有删除
        return this.isEmpty()?null:(T)this.element[this.front];
    }
    @Override
    public T poll() {   //出队，返回对头元素
        if (this.isEmpty())
            return null;
        T temp = (T)this.element[this.front];
        this.front=(this.front+1)%this.element.length;
        return temp;
    }
}
