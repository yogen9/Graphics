#include<iostream>
#include<graphics.h>
#include<conio.h>
using namespace std;


int xc=250;
int yc=250;


void point(int x,int y){
    putpixel(xc+x,yc+y,WHITE);
    putpixel(xc-x,yc+y,WHITE);
    putpixel(xc+x,yc-y,WHITE);
    putpixel(xc-x,yc-y,WHITE);

}
void eclipse(int a,int b){
    int x=0;
    int y=b;

    int d1=(b*b)-((a*a)*b)+((a*a)/4);

    point(x,y);

    while((a*a)*(y-0.5)>(b*b)*(x+1))
    {
        if(d1<0){
            d1=d1+((b*b)*((2*x)+3));
            x=x+1;
        }
        else
        {
            d1=d1+((b*b)*((2*x)+3))+((a*a)*(-2*y+2));
            x=x+1;
            y=y-1;
        }
        point(x,y);
    }

    int d2=(b*b)*(x+0.5)*(x+0.5)+(a*a)*(y-1)*(y-1)-(a*a)*(b*b);

    while(y>0)
    {
        if(d2<0)
        {
            d2=d2+(b*b)*(2*x+2)+(a*a)*(-2*y+3);
            x=x+1;
            y=y-1;
        }
        else
        {
            d2=d2+(a*a)*(-2*y+3);
            y=y-1;
        }
        point(x,y);
    }

}
int main()
{
    initwindow(1000,500);
    int a,b;

    cout<<"Enter the a :";
    cin>>a;
    cout<<"Enter the b:";
    cin>>b;

    eclipse(a,b);
    getch();

}
