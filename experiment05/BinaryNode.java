package DataStructure.lab.experiment05;

public class BinaryNode<T> {
    public T data;  //数据域，存储数据元素
    public BinaryNode<T> left,right;    //节点域，分别指向左右孩子结点
    //构造结点
    public BinaryNode(T data,BinaryNode<T> left,BinaryNode<T> right){
        this.data = data;
        this.left = left;
        this.right = right;
    }
    //构造元素为data的叶子结点
    public BinaryNode(T data){
        this(data,null,null);
    }

    public BinaryNode<T> getLeft() {
        return left;
    }

    public BinaryNode<T> getRight() {
        return right;
    }

    //返回结点数据域的描述字符串
    @Override
    public String toString() {
        return this.data.toString();
    }
    //判断是否是叶子结点
    public boolean isEmpty(){
        return this.left == null && this.right == null;
    }
}
