#include <iostream>
#include <stack>
#include <stdlib.h>
#include <fstream>
#include<math.h>
#include <vector>
#include<iterator>
using namespace std;





struct Point
{
	float x, y;
};

struct tri
{
    Point p1,p2,p3;
};

struct edge{
    Point p1,p2;
};
class Triangle{
    public:
    tri t;
    edge e1,e2,e3;
    tri t1,t2,t3;

    Triangle(Point a,Point b,Point c)
    {
        t.p1=a;
        t.p2=b;
        t.p3=c;
        e1.p1=a;
        e1.p2=b;
        e2.p1=b;
        e2.p2=c;
        e3.p1=c;
        e3.p2=a;
    }
    void setT1(tri t)
    {
        t1=t;
    }
    void setT2(tri t)
    {
        t2=t;
    }
    void setT3(tri t)
    {
        t3=t;
    }


     tri getT()
     {
         return t;
     }
     tri getT1()
     {
         return t1;
     }
     tri getT2()
     {
         return t2;
     }
     tri getT3()
     {
         return t3;
     }
     edge gete1()
     {
         return e1;
     }
     edge gete2()
     {
         return e2;
     }
     edge gete3()
     {
         return e3;
     }
     Point get3rdpoint(edge e)
     {
         if(e.p1.x==t.p1.x && e.p2.x==t.p2.x)
         {
             return t.p3;
         }
         else if(e.p1.x==t.p2.x && e.p2.x==t.p3.x)
         {
             return t.p1;
         }
         if(e.p1.x==t.p3.x && e.p2.x==t.p1.x)
         {
             return t.p2;
         }

     }

};

float sign (Point p1, Point p2, Point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (Point pt, tri t)
{
    bool b1, b2, b3;

    b1 = sign(pt, t.p1,t.p2) < 0.0f;
    b2 = sign(pt, t.p2,t.p3) < 0.0f;
    b3 = sign(pt, t.p3,t.p1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}
bool PointInLine(edge e,Point p)
{
    int b=((p.x-e.p1.x)*(e.p1.y-e.p2.y))-((p.y-e.p1.y)*(e.p1.x-e.p2.x));
    cout<<"inline:"<<b<<endl;
    if(!b) {return true;}
    else
        return false;
}

bool edgeCompare(const edge& e1, const edge& e2)
{
    cout<<"inside compare"<<endl;
    return (e1.p1.x==e2.p1.x && e1.p1.y==e2.p1.y && e1.p2.x==e2.p2.x && e1.p2.y==e2.p2.y) || (e1.p1.x==e2.p2.x && e1.p1.y==e2.p2.y && e1.p2.x==e2.p1.x && e1.p2.y==e2.p1.y);

}
void printEdge(edge e)
{
    cout<<e.p1.x<<","<<e.p1.y<<"--"<<e.p2.x<<","<<e.p2.y<<endl;
}

vector<Triangle> Delaunay(Point points[],int n)
{
    vector<Triangle> T;
    Point p0,p_1,p_2;
    int idx;
    float xmax=-9999.0;
    float ymax=-9999.0;
    float ymin=9999.0;
    for(int i=0;i<n;i++)
    {
        if(points[i].x>xmax)
        {
            xmax=points[i].x;
            idx=i;
        }
    }
    p0=points[idx];
    Point temp=points[idx];
    points[idx]=points[n-1];
    points[n-1]=temp;
    n--;

    for(int i=0;i<n;i++)
    {
        cout<<"-->"<<points[i].x<<","<<points[i].y<<endl;
    }
    for(int i=0;i<n;i++)
    {
        if(points[i].y>ymax)
        {
            ymax=points[i].y;
            p_1=points[i];
        }
    }
    for(int i=0;i<n;i++)
    {
        if(points[i].y<ymin)
        {
            ymin=points[i].y;
            p_2=points[i];
        }
    }
    cout<<"Highest:"<<p0.x<<","<<p0.y<<endl;
    p_1.x+=500.0;
    p_1.y+=1000.0;
    p_2.x-=1000.0;
    p_2.y-=500.0;

    cout<<"p_1:"<<p_1.x<<","<<p_1.y<<endl;
    cout<<"p_2:"<<p_2.x<<","<<p_2.y<<endl;


    Triangle t0=Triangle(p0,p_1,p_2);
    cout<<"Init tri:"<<t0.getT().p1.x<<" "<<t0.getT().p1.y<<endl;
    T.push_back(t0);
    //cout<<T[0].e1.p1.x<<endl;
    for(int i=0;i<n;i++)
    {

        Point pr=points[i];
        cout<<pr.x<<" "<<pr.y<<endl;
        int it;
        for(it=0;it<=T.size();it++){

           if(PointInLine(T[it].gete1(),pr))
           {    cout<<"Inside Line e1"<<endl;
                for(int j=0;j<=T.size();j++)
                {
                    if(j!=it && (edgeCompare(T[it].gete1(),T[j].gete1()) || edgeCompare(T[it].gete1(),T[j].gete2()) || edgeCompare(T[it].gete1(),T[j].gete3()) ))
                    {
                        Point pl=T[it].get3rdpoint(T[it].gete1());
                        Point pk=T[j].get3rdpoint(T[it].gete1());
                        cout<<"Point1:"<<pl.x<<","<<pl.y<<endl;
                        cout<<"Point2:"<<pk.x<<","<<pk.y<<endl;
                    }
                }
                break;
           }
           else if(PointInLine(T[it].gete2(),pr))
           {
               Point pl,pk;
               cout<<"Inside Line e2:" <<endl;
               int id;
                for(int j=0;j<=T.size();j++)
                {
                    pl=T[it].get3rdpoint(T[it].gete2());
                    cout<<"Point1:"<<pl.x<<","<<pl.y<<endl;

                    if(j!=it && (edgeCompare(T[it].gete2(),T[j].gete1())))
                    {
                        pk=T[j].get3rdpoint(T[j].gete1());
                        cout<<"Point2:"<<pk.x<<","<<pk.y<<endl;
                        id=j;
                    }
                    else if(j!=it && (edgeCompare(T[it].gete2(),T[j].gete2())))
                    {
                        pk=T[j].get3rdpoint(T[j].gete2());
                        cout<<"Point2:"<<pk.x<<","<<pk.y<<endl;
                        id=j;
                    }
                    else if(j!=it && (edgeCompare(T[it].gete2(),T[j].gete3())))
                    {
                        pk=T[j].get3rdpoint(T[j].gete3());
                        cout<<"Point2:"<<pk.x<<","<<pk.y<<endl;
                        id=j;
                    }
                }

                Triangle newT1=Triangle(T[it].gete2().p1,pr,pl);
                Triangle newT2=Triangle(T[it].gete2().p2,pr,pl);
                Triangle newT3=Triangle(T[it].gete2().p1,pr,pk);
                Triangle newT4=Triangle(T[it].gete2().p2,pr,pk);
                T.erase(T.begin()+it);
                T.erase(T.begin()+id);
               T.push_back(newT1);
               T.push_back(newT2);
               T.push_back(newT3);
               T.push_back(newT4);

                break;
           }
           else if(PointInLine(T[it].gete3(),pr))
           {
               cout<<"Inside Line e3"<<endl;
                for(int j=0;j<=T.size();j++)
                {
                    if(j!=it && (edgeCompare(T[it].gete3(),T[j].gete1()) || edgeCompare(T[it].gete3(),T[j].gete2()) || edgeCompare(T[it].gete3(),T[j].gete3()) ))
                    {
                        Point pl=T[it].get3rdpoint(T[it].gete3());
                        Point pk=T[j].get3rdpoint(T[it].gete3());
                        cout<<"Point1:"<<pl.x<<","<<pl.y<<endl;
                        cout<<"Point2:"<<pk.x<<","<<pk.y<<endl;
                    }
                }
                break;
           }
           else if(PointInTriangle(pr,T[it].getT()))
           {
               cout<<"inside"<<endl;
               Triangle newT1=Triangle(T[it].gete1().p1,T[it].gete1().p2,pr);
               Triangle newT2=Triangle(T[it].gete2().p1,T[it].gete2().p2,pr);
               Triangle newT3=Triangle(T[it].gete3().p1,T[it].gete3().p2,pr);
               T.erase(T.begin()+it);
               T.push_back(newT1);
               T.push_back(newT2);
               T.push_back(newT3);
               break;
           }
           //it++;
        }

    }
    for(int j=0;j<T.size();j++){
        cout<<"T"<<j<<":"<<T[j].getT().p1.x<<","<<T[j].getT().p1.y<<"--"<<T[j].getT().p2.x<<","<<T[j].getT().p2.y<<"--"<<T[j].getT().p3.x<<","<<T[j].getT().p3.y<<endl;
    }

    return T;
}


bool isLeft(Point a, Point b, Point c){
     return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
}
bool isRight(Point a, Point b, Point c){
     return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) < 0;
}




int main()
{
    ifstream infile("input1.txt");
    int n;
	float a, b;
	if(infile>>a)
    {
        //cout<<a<<"\n";
        n=a;
    }
    Point points[n];


    int i=0;
    while (infile >> a >> b)
    {
        points[i]={a,b};
        i++;
        cout<<a<<","<<b<<"\n";
    }
    vector<Triangle> dt;
    dt=Delaunay(points,n);

    return 0;
}
