package DataStructure.lab.experiment04;

public interface Queue<T> {
    public abstract boolean isEmpty();
    public abstract boolean add(T x);
    public abstract T peek();   //返回队头元素，没有删除。
    public abstract T poll();   //出队，返回对头元素
}
