package DataStructure.lab.experiment05;

public class BinaryTree<T> {
    public BinaryNode<T> root;  //根结点，二叉链表结点结构
    //构造空二叉树
    public BinaryTree(){
        this.root =null;
    }
    //判断是否空二叉树
    public boolean isEmpty(){
        return this.root ==null;
    }
    //输出先根次序遍历序列
    public void preorder(){
        preorder(this.root);    //先根次序遍历以root结点为根的二叉树
        System.out.println();
    }
    //先根次序遍历以p结点为根的子树，递归方法
    public void preorder(BinaryNode<T> p){
        if (p!=null){
            System.out.print(p.data.toString());
            preorder(p.left);
            preorder(p.right);
        }
    }
    //返回先根次序遍历二叉树所有结点的描述字符串，包括空子树标记
    public String toString() {
        return toString(this.root);
    }
    //返回先根次序遍历以p为根的子树描述符串，递归算法
    private String toString(BinaryNode<T> p){
        if (p == null)
            return "^";     //输出空子树标记
        return p.data.toString()+" "+toString(p.left)+toString(p.right);
    }
    //输出中根次序遍历序列
    public void inorder(){
        inorder(this.root);
        System.out.println();
    }
    //中根次序遍历以p结点为根的子树，递归方法
    public void inorder(BinaryNode<T> p){
        if (p!=null){
            inorder(p.left);
            System.out.print(p.data.toString()+" ");
            inorder(p.right);
        }
    }
    //后根次序遍历以p结点为根的子树，递归方法
    public void postorder(){
        postorder(this.root);
        System.out.println();
    }
    public void postorder(BinaryNode<T> p){
        if (p!=null){
            postorder(p.left);
            postorder(p.right);
            System.out.print(p.data.toString()+" ");
        }
    }
    //以标明空子树的先根序列构造一棵二叉树
    public BinaryTree(T[] prelist){
        this.root=create(prelist);
    }
    private int i=0;
    private BinaryNode<T> create(T[] prelist){
        BinaryNode<T> p =null;
        if (i<prelist.length){
            T element = prelist[i++];
            if (element != null){
                p = new BinaryNode<>(element);
                p.left = create(prelist);
                p.right = create(prelist);
            }
        }
        return p;
    }
    //统计叶子结点个数
    public  int leafCount(BinaryNode<T> p){
        if (p!=null){
            if (p.isEmpty())
                return 1;
            else{
                int ln=leafCount(p.left);
                int rn=leafCount(p.right);
                return (ln+rn);
            }
        }else
            return 0;
    }

    //测试
    public static void main(String[] args) {
//        String[] prelist = {"A","B","D",null,"G",null,null,null,"C","E",null,null,"F","H"};
        String[] prelist = {"A","B","D",null,"H",null,null,"E","I",null,null,"J",null,null,"C","F",null,"K",null,null,"G",null,null};
        BinaryTree<String> bitree = new BinaryTree<>(prelist);
        System.out.println("先根次序遍历二叉树："+bitree.toString());
        System.out.print("中根次序遍历二叉树：");
        bitree.inorder();
        System.out.print("后根次序遍历二叉树：");
        bitree.postorder();
        System.out.print("叶子节点数为：");
        System.out.println(bitree.leafCount(bitree.root));
    }
}