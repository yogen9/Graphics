#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;
void DDA_Line(int x0,int y0,int x1,int y1)
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");
    int dx,dy,steps;
    dx=x1-x0;
    dy=y1-y0;
    if(abs(dx)>>abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }
    int incr_x=(dx/steps);
    int incr_y=(dy/steps);

    int new_x=x0;
    int new_y=y0;

    putpixel(new_x,new_y,WHITE);
    int i;

    for(i=0;i<=steps;i++)
    {
        new_x=new_x+incr_x;
        new_x=floor(new_x+0.5);
        new_y=new_y+incr_y;
        new_y=floor(new_y+0.5);
        putpixel(new_x,new_y,BLUE);
    }
    delay(50000);
    closegraph();
}
int main()
{
    int x0,y0,x1,y1;
    cout<<"Enter the start point:";
    cin>>x0>>y0;
    cout<<"Enter the end point: ";
    cin>>x1>>y1;
    DDA_Line(x0,y0,x1,y1);
}


