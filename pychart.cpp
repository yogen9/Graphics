#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;

int main(){
    initwindow(1000,500);

    int n;
    cout<<"Enter the number of data : ";
    cin>>n;

    int a[100];

    for(int i=1;i<=n;i++)
        cin>>a[i];

    int b=0;
    for(int i=1;i<=n;i++)
        b+=a[i];

    cout<<b<<endl;
    int c[100];
    for(int i=1;i<=n;i++)
    {
        c[i]=(360*a[i])/b;
        cout<<c[i]<<endl;
    }

    circle(500,250,100);

    float thita=c[1];
    for(int i=1;i<=n;i++)
    {
        cout<<"thita : "<<thita<<endl;
        float rad=(thita*3.14)/180;
        cout<<"rad : "<<rad<<endl;
        line(500,250,500+100*cos(rad),250+100*sin(rad));
        thita+=c[i];
    }


    getch();
    closegraph();
}
