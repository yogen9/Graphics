#include<iostream>
#include<graphics.h>
using namespace std;

int main(){
    initwindow(1000,500);

    int n;
    cout<<"Enter the number of data(between 0 to 100) : ";
    cin>>n;

    int a[100];

    for(int i=1;i<=n;i++)
        cin>>a[i];

    line(10,10,10,410);
    line(10,410,910,410);


    for(int i=1;i<=n;i++)
    {
        int x=10+(i*60)+10;
        int y=410-(a[i]*4);
        rectangle(x,y,x+50,410);
    }

    getch();
    closegraph();
}
