package DataStructure.lab.experiment06;
/*
二叉树的静态三叉链表结点类
 */
public class TriElement {
  int data; //数据域
  int parent,left,right;    //父母结点和左右孩子结点下标
  public TriElement(int data,int parent,int left,int right){
      this.data = data;
      this.parent = parent;
      this.left = left;
      this.right = right;
  }
  public TriElement(int data){
      this(data,-1,-1,-1);
  }
    //返回结点的描述字符串
    @Override
    public String toString() {
        return "("+this.data+","+this.parent+","+this.left+","+this.right+")";
    }
    //判断是否是叶子结点
    public boolean isLeaf(){
      return this.left == -1 && this.right == -1;
    }
}
