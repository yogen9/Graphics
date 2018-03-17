#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<vector>
using namespace std;

int scale=20;
int fx;
int fy;
int a;

void location()
{
    int row ,col;
    a=1+rand()%2;
    row=(int)(960/scale);
    col=(int)(460/scale);
    fx=20+(20*(rand()%row));
    fy=20+(20*(rand()%col));
}
void food(void)
{
    if(a==1) circle(fx+10,fy+10,10);
    else if(a==2) rectangle(fx,fy,fx+scale,fy+scale);
}

class snake
{
    int x;
    int y;
    int xspeed;
    int yspeed;
    int total;
public:
    snake()
    {
        x=40;
        y=40;
        xspeed=1;
        yspeed=0;
        total=1;
    }
    void roll()
    {

        x=x+xspeed*scale;
        y=y+yspeed*scale;

        if(x<20 || x>960 || y<20 || y>460)
        {
            xspeed=0;
            yspeed=0;
        }
    }
    void show()
    {
        for(int i=1;i<=total;i++)
        {
            rectangle(x-(i*scale),y,x+scale,y+scale);
            setfillstyle(SOLID_FILL,BLUE);
            floodfill(x-(i*scale)+1,y+1,WHITE);

        }
        rectangle(x,y,x+scale,y+scale);
        setfillstyle(SOLID_FILL,BLUE);
        floodfill(x+1,y+1,WHITE);
    }
    void keyevent()
    {
        if(GetAsyncKeyState(VK_UP))
            direction(0,-1);
        else if(GetAsyncKeyState(VK_DOWN) )
            direction(0,1);
        else if(GetAsyncKeyState(VK_LEFT) )
            direction(-1,0);
        else if(GetAsyncKeyState(VK_RIGHT) )
            direction(1,0);
    }
    void direction(int x,int y)
    {
        xspeed=x;
        yspeed=y;
    }
    void eat()
    {
        if(x==fx and y==fy)
        {
             location();
             total++;
        }
    }

};


int main()
{
    initwindow(1000,500);

    snake *yo=new snake();

    location();
    while(1)
    {
        rectangle(20,20,980,480);
        yo->show();
        yo->roll();
        yo->keyevent();
        food();
        yo->eat();

        delay(100);
        cleardevice();
    }


    getch();
    closegraph();

}
