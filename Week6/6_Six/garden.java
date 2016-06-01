import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Vector;
import java.lang.Character;

public class Garden {
    public static class Node
    {
        boolean visited;
        int type;
        int height;
        int x;
        int y;
        Node up;
        Node down;
        Node left;
        Node right;
        Node(int t,int height,int x,int y)
        {
            this.visited=false;
            this.type=t;
            this.height=height;
            this.x=x;
            this.y=y;
        }
        
        
    }
    public static HashMap<Integer,Node> nMap;
    
    public static Node getNode(int x,int y)
    {
        return nMap.get((10*x)+y);
    }
    public static Node getSourceNode(ArrayList<Node>nodeList)
    {
        for(Node n:nodeList)
        {
            if(n.type == 0)
            {
                return n;
            }
        }
        return null;
    }
    public static void solve(Node n)
    {
        n.visited=true;
        if(n.left!=null && n.left.visited == false && n.height>=n.left.height)
        {
            solve(n.left);
        }
        if(n.right!=null && n.right.visited == false && n.height>=n.right.height)
        {
            solve(n.right);
        }
        if(n.down!=null && n.down.visited == false && n.height>=n.down.height)
        {
            solve(n.down);
        }
        if(n.up!=null && n.up.visited == false && n.height>=n.up.height)
        {
            solve(n.up);
        }
    }
    public static void main(String args[]) throws NumberFormatException, IOException
    {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        int cases=Integer.parseInt(br.readLine());
        for(int i=1;i<=cases;i++)
        {
            int h,w,j,k,l,m,o,p,q,r,s,t;
            ArrayList<Node>nodeList=new ArrayList<Node>();
            ArrayList<Node> nList=new ArrayList<Node>();
            ArrayList<Node>ndList=new ArrayList<Node>();
            nMap=new HashMap<Integer, Node>();
            Vector<Integer> v=new Vector<Integer>();
            String input;
            Node source = null;
            Node n0=null;
            String inp[]=br.readLine().split(" ");
            h=Integer.parseInt(inp[0]);
            w=Integer.parseInt(inp[1]);
            for(j=0;j<4;j++)
            {
                input=br.readLine();
                for(k=0;k<4;k++)
                {
                    if(Character.isDigit(input.charAt(k)))
                    {
                        Character ch=input.charAt(k);
                        n0=new Node(1,Integer.valueOf(ch.toString()),k,j);
                        nMap.put((k*10)+j, n0);
                        nodeList.add(n0);
                        ndList.add(n0);
                        
                        
                    }
                    if(input.charAt(k)== '*')
                    {
                        source=new Node(0,w,k,j);
                        nodeList.add(source);
                        nMap.put((k*10)+j, source);
                    }
                    if(input.charAt(k)== '?')
                    {
                        n0=new Node(2,-1,k,j);
                        nMap.put((k*10)+j, n0);
                        nodeList.add(n0);
                        nList.add(n0);
                        
                    }
                }
            }
            for(j=0;j<nodeList.size();j++)
            {
                Node n1=nodeList.get(j);
                Node right=getNode(n1.x+1, n1.y);
                Node left=getNode(n1.x-1,n1.y);
                Node up=getNode(n1.x,n1.y-1);
                Node down=getNode(n1.x,n1.y+1);
                n1.right=right!=null?right:null;
                n1.left=left!=null?left:null;
                n1.down=down!=null?down:null;
                n1.up=up!=null?up:null;
                
            }
            
            int size=nList.size();
            int count=0,flag=0;
            switch(size)
            {
                case 0:
                    solve(source);
                    for(Node n:ndList)
                    {
                        if(n.visited == false)
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag== 0)
                        count=1;
                    break;
                case 1:
                    for(m=0;m<=h;m++)
                    {
                        nList.get(0).height=m;
                        flag=0;
                        for(Node n:nodeList)
                            n.visited=false;
                        solve(source);
                        for(Node n:ndList)
                        {
                            if(n.visited == false)
                            {
                                flag=1;
                                break;
                            }
                        }
                        if(flag== 0)
                            count++;
                    }
                    break;
                case 2:
                    for(o=0;o<=h;o++)
                    {
                        nList.get(1).height=o;
                        for(m=0;m<=h;m++)
                        {
                            nList.get(0).height=m;
                            flag=0;
                            for(Node n:nodeList)
                                n.visited=false;
                            solve(source);
                            for(Node n:ndList)
                            {
                                if(n.visited == false)
                                {
                                    flag=1;
                                    break;
                                }
                            }
                            if(flag== 0)
                                count++;
                        }
                    }
                    break;
                case 3:
                    for(p=0;p<=h;p++)
                    {
                        nList.get(2).height=p;
                        for(o=0;o<=h;o++)
                        {
                            nList.get(1).height=o;
                            for(m=0;m<=h;m++)
                            {
                                nList.get(0).height=m;
                                flag=0;
                                for(Node n:nodeList)
                                    n.visited=false;
                                solve(source);
                                for(Node n:ndList)
                                {
                                    if(n.visited == false)
                                    {
                                        flag=1;
                                        break;
                                    }
                                }
                                if(flag== 0)
                                    count++;
                            }
                        }
                    }
                    break;
                case 4:
                    for(q=0;q<=h;q++)
                    {
                        nList.get(3).height=q;
                        for(p=0;p<=h;p++)
                        {
                            nList.get(2).height=p;
                            for(o=0;o<=h;o++)
                            {
                                nList.get(1).height=o;
                                for(m=0;m<=h;m++)
                                {
                                    nList.get(0).height=m;
                                    flag=0;
                                    for(Node n:nodeList)
                                        n.visited=false;
                                    solve(source);
                                    for(Node n:ndList)
                                    {
                                        if(n.visited == false)
                                        {
                                            flag=1;
                                            break;
                                        }
                                    }
                                    if(flag== 0)
                                        count++;
                                }
                            }
                        }
                    }
                    break;
                case 5:
                    for(r=0;r<=h;r++)
                    {
                        nList.get(4).height=r;
                        for(q=0;q<=h;q++)
                        {
                            nList.get(3).height=q;
                            for(p=0;p<=h;p++)
                            {
                                nList.get(2).height=p;
                                for(o=0;o<=h;o++)
                                {
                                    nList.get(1).height=o;
                                    for(m=0;m<=h;m++)
                                    {
                                        nList.get(0).height=m;
                                        flag=0;
                                        for(Node n:nodeList)
                                            n.visited=false;
                                        solve(source);
                                        for(Node n:ndList)
                                        {
                                            if(n.visited == false)
                                            {
                                                flag=1;
                                                break;
                                            }
                                        }
                                        if(flag== 0)
                                            count++;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 6:
                    for(s=0;s<=h;s++)
                    {
                        nList.get(5).height=s;
                        for(r=0;r<=h;r++)
                        {
                            nList.get(4).height=r;
                            for(q=0;q<=h;q++)
                            {
                                nList.get(3).height=q;
                                for(p=0;p<=h;p++)
                                {
                                    nList.get(2).height=p;
                                    for(o=0;o<=h;o++)
                                    {
                                        nList.get(1).height=o;
                                        for(m=0;m<=h;m++)
                                        {
                                            nList.get(0).height=m;
                                            flag=0;
                                            for(Node n:nodeList)
                                                n.visited=false;
                                            solve(source);
                                            for(Node n:ndList)
                                            {
                                                if(n.visited == false)
                                                {
                                                    flag=1;
                                                    break;
                                                }
                                            }
                                            if(flag== 0)
                                                count++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 7:
                    for(t=0;t<=h;t++)
                    {
                        nList.get(6).height=t;
                        for(s=0;s<=h;s++)
                        {
                            nList.get(5).height=s;
                            for(r=0;r<=h;r++)
                            {
                                nList.get(4).height=r;
                                for(q=0;q<=h;q++)
                                {
                                    nList.get(3).height=q;
                                    for(p=0;p<=h;p++)
                                    {
                                        nList.get(2).height=p;
                                        for(o=0;o<=h;o++)
                                        {
                                            nList.get(1).height=o;
                                            for(m=0;m<=h;m++)
                                            {
                                                nList.get(0).height=m;
                                                flag=0;
                                                for(Node n:nodeList)
                                                    n.visited=false;
                                                solve(source);
                                                for(Node n:ndList)
                                                {
                                                    if(n.visited == false)
                                                    {
                                                        flag=1;
                                                        break;
                                                    }
                                                }
                                                if(flag== 0)
                                                    count++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        
                    }
                    break;
            }
            System.out.println("Case #"+i+": "+count);
            br.readLine();
            
        }
        
    }
}
