#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;

int sign(int n)
{
    if(n>0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void brescnhon(int x0,int y0,int x1,int y1)
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");
    int dx,dy,interchange;
    dx=x1-x0;
    dy=y1-y0;

    if(abs(x0)>abs(x1))
    {
        int temp=x1;
        x1=x0;
        x0=temp;
        temp=y1;
        y1=y0;
        y0=temp;
    }

    int s1=sign(dx);
    int s2=sign(dy);
    interchange=0;

    if(dy>dx)
    {
        int temp=dx;
        dx=dy;
        dy=temp;
        interchange=1;
    }

    int p=2*dy-dx;
    int incr_E=2*dy;
    int incr_NE=2*(dy-dx);

    int new_x=x0;
    int new_y=y0;


    int i;

    for(i=0;i<=dx;i++)
    {
        putpixel(new_x,new_y,WHITE);
        if(p<=0)
        {
            p=p+incr_E;
            if(interchange=0)
            {
                new_x=new_x+s1;
            }
            else
            {
                new_y=new_y+s2;
            }
        }
        else
        {
            p=p+incr_NE;
            new_x=new_x+s1;
            new_y=new_y+s2;
        }
    }
    delay(50000);
    closegraph();
}

int main()
{
    int x0,y0,x1,y1;
    cout<<"Enter the start point:";
    cout<<"\nX0=";
    cin>>x0;
    cout<<"Y0=";
    cin>>y0;
    cout<<endl;
    cout<<"Enter the end point: ";
    cout<<"\nX1=";
    cin>>x1;
    cout<<"Y1=";
    cin>>y1;
    brescnhon(x0,y0,x1,y1);
    DWORD screenwidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenheight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenwidth,screenheight,"C:\\TURBOC3\\BGI");

    //settextstyle(BOLD_FONT,HORIZ_DIR,5);
    //outtextxy(50,50,"BRECNHON");
}
