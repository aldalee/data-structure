package DataStructure.lab.experiment06;
/*
Huffman树类
 */
public class HuffmanTree {
    private String charset;     //字符集合
    private TriElement[] huftree;   //静态三叉链表结点数组
    //构造Huffman树，weights指定权值集合，数组长度为叶子结点数；默认字符集合从A开始
    public HuffmanTree(int[] weights){
        this.charset="";
        for (int i = 0; i < weights.length; i++)
            this.charset += (char)('A'+i);
        int n = weights.length;
        this.huftree = new TriElement[2*n-1];
        for (int i = 0; i < n; i++)
            this.huftree[i] = new TriElement(weights[i]);
        for (int i = n; i <2*n-1; i++) {
            int min1 = Integer.MAX_VALUE,min2 = min1;
            int x1=-1,x2=-1;
            for (int j = 0; j < i; j++)
                if(this.huftree[j].parent==-1)
                    if (this.huftree[j].data<min1){
                        min2 = min1;
                        x2 = x1;
                        min1 = this.huftree[j].data;
                        x1 = j;
                    }
                    else if (this.huftree[j].data<min2){
                        min2 = huftree[j].data;
                        x2 =j;
                        }
            this.huftree[x1].parent = i;
            this.huftree[x2].parent = i;
            this.huftree[i] = new TriElement(min1+min2,-1,x1,x2);
        }
    }
    private String getCode(int i){
        int n =8;
        char hufcode[] = new char[n];
        int child = i,parent = this.huftree[child].parent;
        for ( i = n-1; parent != -1; i--) {
            hufcode[i] = (huftree[parent].left == child)?'0':'1';
            child = parent;
            parent = huftree[child].parent;
        }
        return new String(hufcode,i+1,n-1-i);
    }
    public String toString(){
        String str = "Huffman树的结点数组：";
        for (int i = 0; i < this.huftree.length; i++) {
            str += this.huftree[i].toString()+",";
        }
        str += "\nHuffman编码：";
        for (int i = 0; i < this.charset.length(); i++) {
            str += this.charset.charAt(i)+":"+getCode(i)+",";
        }
        return str;
    }
    /*
    数据压缩
     */
    public String encode(String text){
        String compressed = "";
        for (int i = 0; i < text.length(); i++) {
           compressed += getCode(text.charAt(i)-'A');
        }
        return compressed;
    }
    /*
    数据解压缩
     */
    public String decode(String compressed){
        String text = "";
        int node = this.huftree.length-1;
        for (int i = 0; i < compressed.length(); i++) {
            if (compressed.charAt(i)=='0')
                node = huftree[node].left;
            else
                node = huftree[node].right;
            if (huftree[node].isLeaf()){
                text += this.charset.charAt(node);
                node = this.huftree.length-1;
            }
        }
        return text;
    }

    public static void main(String[] args) {
        //存在的问题：如何进行容错处理呢？？？
//        String text = "AAAABBBCDDBBAAA";
//        int[] weight = {7,5,1,2};
        String text = "ABCDEFGH";
        int[] weight = {19,2,13,5,11,7,3,17};
        HuffmanTree huffman = new HuffmanTree(weight);
        System.out.println(huffman.toString());
        String compressed = huffman.encode(text);
        System.out.println("将"+text+"压缩为"+compressed+","+compressed.length()+"位");
        System.out.println("将"+compressed+"解码为"+huffman.decode(compressed));
    }
}
