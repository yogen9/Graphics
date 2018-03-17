#include<iostream>
#include<graphics.h>
using namespace std;
int xp=500;
int yp=250;
int r=100;

void circlepoint(int x,int y)
{
    putpixel(xp+x,yp+y,WHITE);
    putpixel(xp+x,yp-y,BLUE);
    putpixel(xp-x,yp-y,YELLOW);
    putpixel(xp-x,yp+y,RED);

    putpixel(xp+y,yp+x,WHITE);
    putpixel(xp-y,yp-x,BLUE);
    putpixel(xp+y,yp-x,YELLOW);
    putpixel(xp-y,yp+x,RED);
}

void circle()
{
    int x=0;
    int y=r;

    circlepoint(x,y);

    int d=1-r;

    while(y>x)
    {
        if(d>0)
        {
            d=d+2*(x-y)+5;
            x=x+1;
            y=y-1;
        }
        else
        {
            d=d+2*x+3;
            x=x+1;
        }
        circlepoint(x,y);
    }


}


int main()
{
    initwindow(1000,500);
    circle();
    getch();
}
