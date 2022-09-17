package DataStructure.lab.experiment07;

public abstract class AbstractGraph<T> {

    protected static final int MAX_WEIGHT=0x0000ffff;
    protected SeqList<T> vertexlist;
    public AbstractGraph(int length)
    {
        this.vertexlist=new SeqList<T>(length);
    }

    public AbstractGraph()
    {
        this(10);
    }

    public int vertexCount()
    {
        return this.vertexlist.size();
    }

    public String toString()
    {
        return "顶点集合："+this.vertexlist.toString();
    }

    public T getVertex(int i)
    {
        return this.vertexlist.get(i);
    }

    public void setVertex(int i, T x)
    {
        this.vertexlist.set(i,x);
    }
    public abstract int insertVertex(T x);
    public abstract int weight(int i, int j);
    protected abstract int next(int i,int j);
}
