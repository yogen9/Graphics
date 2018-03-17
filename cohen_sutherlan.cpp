#include<iostream>
#include<graphics.h>
using namespace std;

int calcode(int xmin,int xmax,int ymin,int ymax,int x,int y)
{
    int code=0;
    if(y>ymax)
        code=0x8;
    else if(y<ymin)
        code=0x4;
    if(x>xmax)
        code=code | 0x2;
    else if(x<xmin)
        code=code | 0x1;
    return code;
}

void cohensu(int xmin,int xmax,int ymin,int ymax,int x1,int y1,int x2,int y2)
{
    int accept=0;
    int done=0;
    int x,y;

    int outcode0=calcode(xmin,xmax,ymin,ymax,x1,y1);
    cout<<outcode0<<endl;
    int outcode1=calcode(xmin,xmax,ymin,ymax,x2,y2);
    cout<<outcode1<<endl;

    do{
        if(outcode0==0 && outcode1==0)
        {
            accept=1;
            done=1;
        }
        else if(outcode0 & outcode1)
            done=1;
        else
        {
            int outcodeout=outcode0 ? outcode0:outcode1;

            if(outcodeout & 0x8)
            {
                x=x1+(((x2-x1)*(ymax-y1))/(y2-y1));
                y=ymax;
            }
            else if(outcodeout & 0x4)
            {
                x=x1+(((x2-x1)*(ymin-y1))/(y2-y1));
                y=ymin;
            }
            else if(outcodeout & 0x2)
            {
                y=y1+(((y2-y1)*(xmax-x1))/(x2-x1));
                x=xmax;
            }
            else
            {
                y=y1+(((y2-y1)*(xmin-x1))/(x2-x1));
                x=xmin;
            }

            if(outcodeout==outcode0)
            {
                x1=x;
                y1=y;
                outcode0=calcode(xmin,xmax,ymin,ymax,x1,y1);
            }
            else{
                x2=x;
                y2=y;
                outcode1=calcode(xmin,xmax,ymin,ymax,x2,y2);
            }
        }
    }while(done==0);

    if(accept==1)
        line(x1,y1,x2,y2);

    cout<<accept<<done;
}

int main()
{
    initwindow(1000,500);
    int xmin=200;
    int xmax=800;
    int ymin=100;
    int ymax=400;
    int x1,x2,y1,y2;
    rectangle(xmin,ymax,xmax,ymin);

    cout<<"Enter the x1,y1,x2,y2 : ";
    cin>>x1>>y1>>x2>>y2;

    cohensu(xmin,xmax,ymin,ymax,x1,y1,x2,y2);
    getch();
}
