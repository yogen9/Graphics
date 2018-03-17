#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
using namespace std;
int TIPA=150;
int TIPA_NO_COLOR=13;
class drop
{
    int x,y,speed,len;
public:
    drop()
    {
        x=15+rand()%600;
        y=-(rand()%100);
        speed=5+rand()%10;
        len=15+rand()%5;
    }
    void show()
    {
         line(x,y,x,y+len);
    }
    void fall()
    {
        y=y+speed;
        if(y>600)
            y=-(rand()%100);
    }

};

int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");

    drop yo[TIPA];

    for(int i=0;i<1000;i++)
    {
            for(int j=0;j<TIPA;j++)
             {
                 setcolor(TIPA_NO_COLOR);
                yo[j].show();
                yo[j].fall();

             }
        delay(10);
        cleardevice();
    }
    getch();
    closegraph();
}
