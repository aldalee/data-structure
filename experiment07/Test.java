package DataStructure.lab.experiment07;

public class Test {
    public static void main(String[] args) {
        String[] vertices= {"A","B","C","D","E","F","G"};//无向图的顶点集合
        Triple edges[]= {new Triple(0,1,7),new Triple(0,5,13),new Triple(0,6,6)
                ,new Triple(1,0,7),new Triple(1,2,12),new Triple(1,6,4)
                ,new Triple(2,1,12),new Triple(2,3,5),new Triple(2,6,19)
                ,new Triple(3,2,5),new Triple(3,4,11),new Triple(3,6,20)
                ,new Triple(4,3,11),new Triple(4,5,10),new Triple(4,6,16)
                ,new Triple(5,4,10),new Triple(5,0,13),new Triple(5,6,15)
                ,new Triple(6,0,7),new Triple(6,1,4),new Triple(6,2,19)
                ,new Triple(6,3,20),new Triple(6,4,16),new Triple(6,5,15)};
        //无向图的边集合
        MatrixGraph<String> graph=new MatrixGraph<String>(vertices,edges);//构造无向图
        System.out.println("带权无向图G:"+graph.toString());//输出无向图的邻接矩阵

        System.out.println("---------------深度优先遍历---------------");
        //调用MatrixGraph类中的DFSTraverse方法，输出每一个点开始的深度优先遍历
        for(int i=0;i<graph.vertexCount();i++)
            graph.DFSTraverse(i);

        System.out.println("---------------广度优先遍历---------------");
        //调用MatrixGraph类中的BFSTraverse方法，输出每一个点开始的广度优先遍历
        for(int i=0;i<graph.vertexCount();i++)
            graph.BFSTraverse(i);

        System.out.println("---------------Dijkstra算法的最短路径---------------");
        for(int i=0;i<graph.vertexCount();i++)
            graph.DijkstraShortestPath(i);

        System.out.println("---------------Floyd算法的最短路径---------------");
        graph.FloydShortestPath();
    }
 
}
