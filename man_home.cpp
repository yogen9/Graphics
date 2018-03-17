#include<graphics.h>
#include<iostream>
using namespace std;

int main()
{
    initwindow(1920,1080);

    for(int i=0;i<220;i++)
    {
        rectangle(200,200,400,400);
        line(400,200,450,150);
        line(400,400,450,350);
        line(450,150,450,350);
        line(200,200,250,150);
        line(250,150,450,150);
        line(280,400,280,280);
        line(320,400,320,280);
        line(320,280,280,280);
        rectangle(220,310,260,280);
        rectangle(340,310,380,280);
        rectangle(260,400,340,420);
        rectangle(240,420,340,440);
        circle(40+i,330,15);
        line(40+i,345,40+i,395);
        line(40+i,395,20+i,410);
        line(40+i,365,20+i,365);
        line(40+i,365,60+i,355);
        line(40+i,365,60+i,355);

        delay(50);
        cleardevice();

    }
    getch();
    closegraph();
}
