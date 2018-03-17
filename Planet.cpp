#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;
int radious=200;
int centerx=250;
int centery=250;
int main()
{

    initwindow(1000,500);

    for(float i=0;i<360;i=i+0.1)
    {
        int circle2x=centerx+radious*cos(i);
        int circle2y=centery+radious*sin(i);

        setcolor(RED);
        circle(centerx,centery,radious);

        setcolor(WHITE);
        circle(circle2x,circle2y,50);

        floodfill(circle2x-25,circle2y-25,WHITE);
        floodfill(circle2x+25,circle2y+25,WHITE);
        setfillstyle(SOLID_FILL,BLUE);

        delay(10);
        cleardevice();

    }
    getch();
    closegraph();
}

