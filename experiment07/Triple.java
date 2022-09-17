package DataStructure.lab.experiment07;

public class Triple implements Comparable<Triple>{
    int row,column,value;
    public int compareTo(Triple tri)
    {
        if(this.row==tri.row&&this.column==tri.column)
            return 0;
        return (this.row<tri.row||this.row==tri.row&&this.column<tri.column)? -1:1;
    }
    public Triple(Triple tri)
    {
        this(tri.row,tri.column,tri.value);
    }
    public Triple(int row,int column,int value)
    {
        if(row>=0&&column>=0)
        {
            this.row=row;
            this.column=column;
            this.value=value;
        }
        else throw new IllegalArgumentException("行，列不能为负数：row="+row+",column="+column);
    }
}
