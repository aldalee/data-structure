package DataStructure.lab.experiment07;

public class MatrixGraph<T> extends AbstractGraph<T> {
    protected Matrix matrix;
    public MatrixGraph(int length)
    {
        super(length);
        this.matrix=new Matrix(length);
    }
    public MatrixGraph(T[] vertices)
    {
        this(vertices.length);
        for(int i=0;i<vertices.length;i++)
            this.insertVertex(vertices[i]);
    }
    public MatrixGraph(T[] vertices,Triple[] edges)
    {
        this(vertices);
        for(int j=0;j<edges.length;j++)
            this.insertEdge(edges[j]);
    }
    public String toString()//将图以邻接矩阵输出
    {
        String str="邻接矩阵：\n";
        int n=this.vertexCount();
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                if(this.matrix.get(i,j)==MAX_WEIGHT)//当两点距离无限大时
                    str+="     ∞";
                else str+=String.format("%6d", this.matrix.get(i, j));
            str+="\n";
        }
        return str;
    }
    public void insertEdge(int i,int j,int weight)
    {
        if(i!=j)
        {
            if(weight<=0||weight>MAX_WEIGHT)
                weight=MAX_WEIGHT;
            this.matrix.set(i,j,weight);
        }
        else throw new IllegalArgumentException("不能插入自身环，i="+i+",j="+j);
    }
    public void insertEdge(Triple edge)
    {
        this.insertEdge(edge.row,edge.column,edge.value);
    }
    public int insertVertex(T x)
    {
        int i=this.vertexlist.insert(x);
        if(i>=this.matrix.getRows())
            this.matrix.setRowsColumns(i+1, i+1);
        for(int j=0;j<i;j++)
        {
            this.matrix.set(i, j, MAX_WEIGHT);
            this.matrix.set(j, i, MAX_WEIGHT);
        }
        return i;
    }

    public int weight(int i,int j)
    {
        return this.matrix.get(i, j);
    }
    protected int next(int i,int j)
    {
        int n=this.vertexCount();
        if(i>=0&&i<n&&j>=-1&&j<n&&i!=j)
            for(int k=j+1;k<n;k++)
                if(this.matrix.get(i, k)>0&&this.matrix.get(i, k)<MAX_WEIGHT)
                    return k;
        return -1;
    }
    public void DFSTraverse(int i)//深度优先遍历
    {
        boolean[] visited =new boolean[this.vertexCount()];//标记数组，初始值为false
        int j=i;
        do
        {
            if(!visited[j])//若顶点未被访问
            {
                System.out.print("\t\t\t{");
                this.depthfs(j,visited);//以j为起始点，调用depthfs方法
                System.out.print("}");
            }
            j=(j+1)%this.vertexCount();//在其他连通分支中找未被访问的点
        }while(j!=1);
        System.out.println();
    }
    private void depthfs(int i,boolean []visited)
    {
        System.out.print(this.getVertex(i)+" ");
        visited[i]=true;//标示该点以被访问
        int j=this.next(i, -1);
        while(j!=-1)//利用递归遍历所有节点
        {
            if(!visited[j])
                depthfs(j,visited);
            j=this.next(i, j);//使j等于下一个邻接节点
        }
    }
    public void BFSTraverse(int i)//广度优先遍历
    {
        boolean visited[]=new boolean[this.vertexCount()];//
        int j=i;
        do
        {
            if(!visited[j])//若顶点未被访问
            {
                System.out.print("\t\t\t{");
                breadthfs(j,visited);//以j为起始点，调用breadthfs方法
                System.out.print("}");
            }
            j=(j+1)%this.vertexCount();//在其他连通分支中找未被访问的点
        }while(j!=i);
        System.out.println();
    }
    private void breadthfs(int i,boolean[] visited)
    {
        System.out.print(this.getVertex(i)+" ");
        visited[i]=true;//标示该点以被访问
        LinkedQueue<Integer> que=new LinkedQueue<Integer>();//创建队列
        que.add(i);//访问过的节点入队
        while(!que.isEmpty())//若队列不空
        {
            i=que.poll();//出队
            for(int j=next(i,-1);j!=-1;j=next(i,j))//j依次获得vi的所有邻接顶点
                if(!visited[j])//若顶点未被访问
                {
                    System.out.print(this.getVertex(j)+" ");
                    visited[j]=true;
                    que.add(j);//访问过的节点入队
                }
        }
    }
    public void DijkstraShortestPath(int i)//见数据结构书209页，Dijkstra算法,单源
    {
        int n=this.vertexCount();//图的顶点数
        boolean[] vset=new boolean[n];//构造长度为n的boolean型数组，初值为false
        vset[i]=true;//标记源点
        int[] dist=new int[n];//最短路径长度
        int[] path=new int[n];//最短路径的终点的前一个节点
        for(int j=0;j<n;j++)//初始化dist和path数组
        {
            dist[j]=this.weight(i, j);
            path[j]=(j!=i&&dist[j]<MAX_WEIGHT)?i:-i;
        }
        for(int j=(i+1)%n;j!=i;j=(j+1)%n)//寻找vi到vj的最短路径，
        {
            int mindist=MAX_WEIGHT,min=0;
            for(int k=0;k<n;k++)
                if(!vset[k]&&dist[k]<mindist)
                {
                    mindist=dist[k];//路径长度最小值
                    min=k;//路径长度最小值下标
                }
            if(mindist==MAX_WEIGHT)
                break;
            vset[min]=true;
            for(int k=0;k<n;k++)//调整从vi到V-S中其他顶点的最短路径及长度
                if(!vset[k]&&this.weight(min, k)<MAX_WEIGHT&&dist[min]+this.weight(min,k)<dist[k])
                {
                    dist[k]=dist[min]+this.weight(min, k);//用更短路径替换
                    path[k]=min;//最短路径经过min顶点
                }
        }
        System.out.print(this.getVertex(i)+"顶点的最短路径：");
        for(int j=0;j<n;j++)//输出顶点vi的单源最短路径
            if(j!=i)
            {
                SinglyList<T> pathlink=new SinglyList<T>();//构造单链表，记录最短路径经过的顶点
                pathlink.insert(0,this.getVertex(j));//单链表插入最短路径终点vj
                for(int k=path[j];k!=i&&k!=j&&k!=-1;k=path[k])//寻找vi到vj的最短路径
                    pathlink.insert(0,this.getVertex(k));//表头插入经过的顶点
                pathlink.insert(0, this.getVertex(i));//最短路径的起点vi
                System.out.println(pathlink.toString()+"长度"+(dist[j]==MAX_WEIGHT?"∞":dist[j]));
            }
        System.out.println();
    }
    public void FloydShortestPath()
    {
        int n=this.vertexCount();//图的顶点数
        Matrix path=new Matrix(n),dist=new Matrix(n);//最短路径及长度矩阵，初值为0
        for(int i=0;i<n;i++)//初始化dist，path矩阵
            for(int j=0;j<n;j++)
            {
                int w=this.weight(i, j);
                dist.set(i, j, w);//dist初值为图的邻接矩阵
                path.set(i, j, (i!=j&&w<MAX_WEIGHT?i:-i));
            }
        for(int k=0;k<n;k++)//以vk作为其他路径的中间顶点
            for(int i=0;i<n;i++)//测试每对从vi到vj的路径长度是否更短
                if(i!=k)
                    for(int j=0;j<n;j++)
                        if(j!=k&&dist.get(i, j)>dist.get(i, k)+dist.get(k,j))//若更短则替换
                        {
                            dist.set(i, j,dist.get(i, k)+dist.get(k, j));
                            path.set(i, j, path.get(k, j));
                        }
        System.out.println("每对顶点间的最短路径：");
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                if(i!=j)
                    System.out.println(toPath(path,i,j)+"长度"+(dist.get(i,j)==MAX_WEIGHT?"∞":dist.get(i, j)));
            System.out.println();
        }
    }
    private String toPath(Matrix path,int i,int j)
//返回path路径矩阵中从顶点vi到vj的一条路径字符串
    {
        SinglyList<T> pathlink=new SinglyList<T>();//单链表，记录最短路径经过顶点，用于反序
        pathlink.insert(0, this.getVertex(j));//单链表插入最短路径终点vj
        for(int k=path.get(i, j);k!=i&&k!=j&&k!=-1;k=path.get(i, k))
            pathlink.insert(0, this.getVertex(k));  //单链表头插入经过的顶点，反序
        pathlink.insert(0,this.getVertex(i));//最短路径的起点vi
        return pathlink.toString();
    }
}