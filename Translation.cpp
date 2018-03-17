#include<iostream>
#include<math.h>
#include<graphics.h>
using namespace std;

void polygon(int x[],int y[],int n){
    for(int i=0;i<n-1;i++)
        line(x[i],y[i],x[i+1],y[i+1]);
    line(x[0],y[0],x[n-1],y[n-1]);
}

void translation(int x[],int y[],int tx,int ty,int n)
{
    for(int i=0;i<n;i++)
    {
        x[i]=x[i]+tx;
        y[i]=y[i]+ty;
    }
}

void scaling(int x[],int y[],int sx,int sy,int n)
{
    for(int i=0;i<n;i++)
    {
        x[i]=x[i]*sx;
        y[i]=y[i]*sy;
    }
}

float[3][3] rotationf(float thita,float *rotation)
{    rotation[3][3]={       {cos((3.14*thita)/180),sin((3.14*thita)/180),0},
                            {-sin((3.14*thita)/180),cos((3.14*thita)/180),0},
                            {0,0,1}};
    return rotation;
}

int main(){

    initwindow(1000,500);
    int ch1,ch2;
    int x[25]={};
    int y[25]={};
    int n=0;                    // vertices
    int tx,ty;               //for translation
    float sx,sy;            //for scaling
    int b[3][1]={};
    float thita=0; //in degree
    float rotation[3][3]={ {cos((3.14*thita)/180),sin((3.14*thita)/180),0},
                            {-sin((3.14*thita)/180),cos((3.14*thita)/180),0},
                            {0,0,1}};
    float temp[3][1]={};
    int *tempx=new int;
    int *tempy=new int;


    cout<<"Enter "<<endl;
    cout<<"1.Polygon"<<endl;
    cout<<"2.Circle"<<endl;
    cout<<"Choice : ";
    cin>>ch1;

    switch(ch1)
    {
        case 1: cout<<"Enter the number of vertices of polygon : ";
                cin>>n;
                for(int i=0;i<n;i++)
                {
                    cout<<"x"<<i+1<<" : ";
                    cin>>x[i];
                    cout<<"y"<<i+1<<" : ";
                    cin>>y[i];
                    cout<<"_________"<<endl;
                }
                polygon(x,y,n);
                break;

        case 2:
                break;
        default:
                break;
    }
    while(1)
    {
        cout<<endl<<endl;
        cout<<"Enter "<<endl;
        cout<<"1.Translation"<<endl;
        cout<<"2.Rotation"<<endl;
        cout<<"3.Scaling"<<endl;
        cout<<"Choice : ";
        cin>>ch2;

        switch(ch2)
        {
            case 1: cout<<"Enter the X direction Translation tx : ";
                    cin>>tx;
                    cout<<"Enter the Y direction Translation ty : ";
                    cin>>ty;
                    translation(x,y,tx,ty,n);
                    polygon(x,y,n);
                    break;

            case 2: cout<<"Enter the Thita(in DEGREE) : "<<endl;
                    cin>>thita;
                    for(int i=0;i<3;i++)
                    {
                         for(int j=0;j<3;j++)
                            cout<<rotation[i][j]<<" ";
                        cout<<endl;
                    }

                    for(int a=0;a<n;a++)
                    {
                        b[3][1]=x[a];
                        b[3][1]=y[a];
                        b[3][1]=1;
                        for(int i=0;i<3;i++)
                        {
                            for(int j=0;i<1;j++)
                            {
                                int sum=0;
                                for(int k=0;k<3;k++)
                                    sum=sum+rotation[i][k]*b[k][j];
                                temp[i][j]=sum;
                            }
                        }
                        tempx[a]=temp[0][0];
                        tempy[a]=temp[1][0];
                    }

                    polygon(tempx,tempy,n);
                    break;

            case 3: cout<<"Enter the X direction Scaling sx : ";
                    cin>>sx;
                    cout<<"Enter the Y direction Scaling sy : ";
                    cin>>sy;
                    scaling(x,y,sx,sy,n);
                    polygon(x,y,n);
                    break;
            default:
                    break;
        }
    }


    getch();





}
