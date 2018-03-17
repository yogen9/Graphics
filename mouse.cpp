#include<iostream>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
using namespace std;
union REGS in, out;

void initmouse(){
       //	in.x.ax = 0; //get mouse state
	int86(51, &in, &out); //initialize mouse
	cout<<"value of ax="<<out.x.ax;
	if(out.x.ax == 0){ //if mouse has not been initialized

		cout<<"not initialized"<<endl;
		exit(1);
	}
	in.x.ax = 1; //show mouse pointer
	int86(51, &in, &out);
	in.x.ax = 7; //set x
	in.x.cx = 0; //min x
	in.x.dx = getmaxx();  //max x
	int86(51, &in, &out);
	in.x.ax = 8; //set y
	in.x.cx = 0; //min y
	in.x.dx = getmaxy(); //max y
	int86(51, &in, &out);
}
void mouseread(int &a, int &b, int &c){
	in.x.ax = 3; //record mouse presses
	int86(51, &in, &out);
	a = out.x.cx; //store x value
	b = out.x.dx; //store y value
	c = out.x.bx; //store button value
}
void polygon(int x[], int y[], int size){
	for(int i = 0; i<size-1; i++){
		line(x[i], y[i], x[i+1], y[i+1]);
	}
	line(x[0], y[0], x[i], y[i]);
}
void main(){
	int xc[100], yc[100], x, y, b, flag = 0, gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	initmouse(); //initialize mouse
	int i = 0;   //to keep track of count of no of memebers in array
	do{
		mouseread(x, y, b);    //continuously check if button is pressed
		if((b == 1) && (flag == 0)){ //left click has been pressed and released
			xc[i] = x;
			yc[i] = y;
			putpixel(x, y, WHITE);
			i++;
			flag = 1;
		}
		if(b == 0) //no key pressed
			flag = 0;
	}while(!(b==2));
	in.x.ax = 2; //hide mouse pointer
	int86(51, &in, &out);
	polygon(xc, yc, i); //generate polygon
	getch();
}
