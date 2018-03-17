#include <iostream>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include <ctime>
#include<windows.h>

#define BOUNDARY_COLOR LIGHTGREEN
using namespace std ;

int p1_color = YELLOW ;
int p2_color = LIGHTRED ;

    int x_min =  (200)/20*20 ;
    int y_min =  (200)/20*20 ;
    int x_max = (1920- 200)/20*20 ;
    int y_max = (1080- 200)/20*20 ;

    int prev1 = 2 ; // initial direction
    int prev2 = 2 ; // initial direction

int mode ;
int prevfoodx;
int prevfoody;

int points1 = 0 ;
int points2 = 0 ;
char p1[20] ;
char p2[20] ;

void gameover(void) ;
void settings_menu(int &level , int &speed);
void print_food(int food_x , int food_y) ;
void food_preference(int food_x , int food_y ,int color);
void graph_preference( int x , int y , int y1, int color ) ;
void get_info();
void selectcolors();


// -----------------------------------------------------------
class snake
{
public:

    int x , y ; // position of node in the game
    snake *next ;

    snake(int d_x , int d_y)
    {
        x=d_x;
        y=d_y;
        next = NULL ;
    }

    void addnode(int x, int y,snake **tail ) ;
    void drawgame(int color);
    void erasegame(void);
    void update(int new_x , int new_y) ;


};


void keyboard_input1( int &prev , int &old_head_x , int &old_head_y , snake **head  );
void keyboard_input2( int &prev , int &old_head_x , int &old_head_y , snake **head  );
void cpu_move( int &prev , int &old_head_x , int &old_head_y , snake **head , snake **head1, int food_x , int food_y );
bool snake_ahead(int future_head_x , int future_head_y , snake  *body1 , snake *body2) ;
void set_initial_positions(int &x1,int &y1,int &x2,int &y2);




    void set_initial_positions(int &x1,int &y1,int &x2,int &y2,int &food_x,int &food_y)
    {
        x1  = (500)/20*20;
        y1 = (500)/20*20 ;
        x2  = (800)/20*20;
        y2 = (800)/20*20 ;

          // food
        srand(time(0)) ;

        food_x  = (x_min+20 +rand()%(x_max-20-x_min-20))/20*20;
        food_y = (y_min+20 + rand()%(y_max-20-y_min-20))/20*20 ;
        prevfoodx = food_x ;
        prevfoody = food_y ;
    }



// -----MAIN-----MAIN-----MAIN----MAIN----MAIN---MAIN----MAIN-----

int main()
{



    int x1,y1,x2,y2;
    int food_x,food_y;
    snake *head1,*head2,*tail1,*tail2;
    int old_head_x1,old_head_x2,old_head_y1,old_head_y2 ;
    bool over = false ;

    cout << " 1. single player\n 2. two player \n 3. player vs cpu \n 4. cpu vs cpu ";
    cout << "\n\n->";
    cin >> mode ;

    int  level ,speed ;
    char msg[20] ;

    get_info();


    initwindow(1920,1080);

        cleardevice();


    settings_menu(level,speed);

    set_initial_positions(x1,y1,x2,y2,food_x,food_y);

    head1 = new snake(x1,y1) ;
    tail1 = head1 ;

    for(int node=1 ; node<=7 ; node++)
        head1->addnode(x1-20*node,y1 , &tail1);

    if(mode !=1) // if multi player
    {
        head2 = new snake(x2,y2) ;
        tail2 = head2 ;

        for(int node=1 ; node<=7 ; node++)
            head2->addnode(x2-20*node,y2 , &tail2);
    }

    setcolor(BOUNDARY_COLOR);
    rectangle(x_max , y_max , x_min , y_min);

    print_food(food_x , food_y ) ;


    while(!over)
    {
        if(prevfoodx != food_x || prevfoody != food_y )
             print_food(food_x , food_y ) ;

        old_head_x1 = head1->x ;
        old_head_y1 = head1->y ;

        if(mode !=1)
        {
            old_head_x2 = head2->x ;
            old_head_y2 = head2->y ;
        }

        // hit space to pause the game
        if(GetAsyncKeyState(VK_SPACE))
             {
                 delay(500);

                 while(1)
                 {
                     delay(500);
                     if(GetAsyncKeyState(VK_SPACE))
                        break;
                 }
             }



   switch(mode)
   {
   case 1 :
    {
        keyboard_input1( prev1 , old_head_x1 , old_head_y1 , &head1  ); break;
    }

   case 2:
    {
        keyboard_input1( prev1 , old_head_x1 , old_head_y1 , &head1  );
         keyboard_input2( prev2 , old_head_x2 , old_head_y2 , &head2  );
         break;
    }

   case 3:
    {
         keyboard_input1( prev1 , old_head_x1 , old_head_y1 , &head1  );
          cpu_move( prev2 , old_head_x2 , old_head_y2 , &head2 , &head1 ,food_x , food_y);
          break;
    }

   case 4:
    {
        cpu_move( prev2 , old_head_x2 , old_head_y2 , &head2 , &head1 ,food_x , food_y);
        cpu_move( prev1 , old_head_x1 , old_head_y1 , &head1 , &head2 ,food_x , food_y);
        break;
    }

   }


    head1->drawgame(p1_color);


    if(mode !=1)
    {
        head2->drawgame(p2_color);
        tail2->erasegame();
    }

    tail1->erasegame();



    // if the food is at the same place as head

        if  ( food_x == old_head_x1  && food_y==old_head_y1 )
        {
            snake *food_node ;

            if(prev1==2)
            food_node = new snake(food_x+20,food_y);

            else if(prev1==1)
                food_node = new snake(food_x-20,food_y);

            else if(prev1==3)
                food_node = new snake(food_x,food_y-20);

            else if(prev1==4)
               food_node = new snake(food_x,food_y+20);

            // add food as new head
            food_node->next = head1 ;
            head1 = food_node ;

            // generate new food
            prevfoodx = food_x ;
            prevfoody = food_y ;
            setfillstyle(1,BLACK);
            setcolor(WHITE);
            rectangle(prevfoodx-10,prevfoody-10,prevfoodx+10,prevfoody+10);
            floodfill(prevfoodx , prevfoody , WHITE);
            setcolor(BLACK);
            rectangle(prevfoodx-10,prevfoody-10,prevfoodx+10,prevfoody+10);
            food_x  = int(x_min +30+  rand()%(x_max-x_min-30) )/20*20;
            food_y = int(y_min +30+ rand()%(y_max-y_min-30))/20*20 ;

            points1 += 5 ;

        }

        else if( food_x == old_head_x2  && food_y==old_head_y2 && mode !=1 )
        {
            snake *food_node ;

            if(prev2==2)
                food_node = new snake(food_x+20,food_y);

            else if(prev2==1)
                food_node = new snake(food_x-20,food_y);

            else if(prev2==3)
                food_node = new snake(food_x,food_y-20);

            else if(prev2==4)
               food_node = new snake(food_x,food_y+20);

            // add food as new head
            food_node->next = head2 ;
            head2 = food_node ;

            // generate new food
             prevfoodx = food_x ;
            prevfoody = food_y ;
            setfillstyle(1,BLACK);
            setcolor(WHITE);
            rectangle(prevfoodx-10,prevfoody-10,prevfoodx+10,prevfoody+10);
            floodfill(prevfoodx , prevfoody , WHITE);
            setcolor(BLACK);
            rectangle(prevfoodx-10,prevfoody-10,prevfoodx+10,prevfoody+10);
            food_x  = int(x_min +30+  rand()%(x_max-x_min-30) )/20*20;
            food_y = int(y_min +30+ rand()%(y_max-y_min-30))/20*20 ;

            points2 += 5 ;

        }



        if (head1->x > x_max || head1->y > y_max || head1->x < x_min || head1->y < y_min)
         {
             over = true ;
             points1 = points1-5 ;

            setcolor(p1_color);
            outtextxy(200,50,p1) ;
            sprintf(msg," : %d ",points1);
            outtextxy(450,50,msg) ;
            break;
         }

        if(mode !=1)
        if (head2->x > x_max || head2->y > y_max || head2->x < x_min || head2->y < y_min)
         {
             over = true ;
             points2=points2-5 ;

            setcolor(p2_color);
            outtextxy(1000,50,p2) ;
            sprintf(msg,": %d ",points2);
            outtextxy(1250,50,msg) ;
            break;
         }



if(mode != 1)
{
       snake*  tp1=head1 ;
    while(tp1!=NULL)
    {
        if(head2->x == tp1->x && head2->y == tp1->y )
        {
            points1= points1 + 2   ;
            snake *temp = head2;

               if(head2 ->next == NULL)
                gameover();

            head2 = head2->next ;

            delete(temp);

            setcolor(p1_color);
            setfillstyle(1,p1_color);


        }

        tp1=tp1->next;
    }



        snake* tp2=head2 ;

        while(tp2!=NULL)
        {
            if(head1->x == tp2->x && head1->y == tp2->y )
            {
                points2= points2 + 2   ;
                 snake *temp = head1;

                if(head1 ->next == NULL)
                gameover();

                 head1 = head1->next ;

                 delete(temp);

                setcolor(p2_color);
                setfillstyle(1,p2_color);

            }

            tp2=tp2->next;
        }


}


            if(mode != 1)
        head2->update(old_head_x2,old_head_y2) ;


        head1->update(old_head_x1,old_head_y1) ;

        delay(speed);


        setcolor(p1_color);
        outtextxy(200,50,p1) ;
        sprintf(msg," : %d ",points1);
        outtextxy(450,50,msg) ;

        if(mode !=1)
        {
        setcolor(p2_color);
        outtextxy(1000,50,p2) ;
        sprintf(msg,": %d ",points2);
        outtextxy(1250,50,msg) ;

        }

}
    gameover();

    points1 = 0 ;
    points2 = 0 ;


getch();
closegraph();
return 0 ;

}
// -----MAIN-----MAIN-----MAIN----MAIN----MAIN---MAIN----MAIN-----





 void snake :: addnode(int x , int y , snake **tail)
 {
     snake *tp = this ;
     snake *newnode = new snake(x,y);
     (*tail)->next = newnode ;
     (*tail) = newnode ;
 }



  void snake::drawgame(int color)
 {
     snake *tp = this ;
    setcolor(color);

    rectangle(tp->x-10,tp->y-10,tp->x+10,tp->y+10);



     tp=tp->next;

     while(tp != NULL)
     {
        rectangle(tp->x-10,tp->y-10,tp->x+10,tp->y+10);
        tp = tp->next ;
     }



 }



   void snake::erasegame(void)
 {
    snake *tp = this ;
    setcolor(BLACK);
    rectangle(tp->x-10,tp->y-10,tp->x+10,tp->y+10);

 }



 void snake::update(int new_x,int new_y)
  {
     snake *tp = this->next ;
     int old_x , old_y ;

     while(tp != NULL)
     {
       old_x = tp->x ;
       old_y = tp->y ;
        tp->x  = new_x ;
        tp->y  = new_y ;
        new_x = old_x ;
        new_y = old_y ;

        tp = tp->next ;
     }

 }
//+++++++++++++++++++++++++++++++++++++++++++++++





//+++++++++++++++++++++++++++++++++++++++++++++++
void gameover(void)
{

    char msg[10];

      if(points1> points2)
      {
          strcpy(msg,p1);
          setcolor(p1_color);
          strcat(msg," wins") ;
           outtextxy(getmaxx()/2-200,getmaxy()/2+200,msg) ;
      }


    else if ( points2 > points1)
        {
           strcpy(msg,p2);
          setcolor(p2_color);
          strcat(msg," wins") ;
           outtextxy(getmaxx()/2-200,getmaxy()/2+200,msg) ;
      }

      else
    {
          setcolor(14);
            outtextxy(getmaxx()/2-200,getmaxy()/2+200,"DRAW") ;
      }

      settextstyle(BOLD_FONT , HORIZ_DIR , 6 ) ;
    sprintf(msg,"GAMEOVER ");
    outtextxy(800,500,msg) ;



     while(1)
        {
             if(GetAsyncKeyState(VK_SPACE))
                 return ;

            delay(200);
        }

    delay(200);


}
//+++++++++++++++++++++++++++++++++++++++++++++++




//+++++++++++++++++++++++++++++++++++++++++++++++
void settings_menu(int &level , int &speed)
{
     char msg[20];

 level = 4 ; // default
 bool change = false;

while(!change)
{
    cleardevice();
    settextstyle(BOLD_FONT , HORIZ_DIR , 9 ) ;
    setcolor(p1_color);
    outtextxy(800,200,"SNAKE PRO") ;

     setcolor(p2_color);
    settextstyle(BOLD_FONT , HORIZ_DIR , 5 ) ;

    switch(level)
    {
    case 0 :
         {
              setcolor(LIGHTCYAN);
              outtextxy(700,700,"SPEED : SUPER SLOW") ;
              break;
        }

    case 1:
         {
              setcolor(LIGHTGREEN);
              outtextxy(700,700,"SPEED : SLOW") ;
              break;
        }

    case 2:
         {
             setcolor(YELLOW);
              outtextxy(700,700,"SPEED : MEDIUM ") ;
              break;
        }

    case 3:
         {
            setcolor(LIGHTGREEN);
              outtextxy(700,700,"SPEED : FAST") ;
              break;
        }

    case 4:
         {
            setcolor(LIGHTBLUE);
              outtextxy(700,700,"SPEED : ULTRA FAST") ;
              break;
        }

    case 5:
         {
            setcolor(BLUE);
              outtextxy(700,700,"SPEED : INSANE") ;
              break;
        }
    }



     if ( GetAsyncKeyState(VK_DOWN) && level<=4 )
          level++;

    else if ( GetAsyncKeyState(VK_UP) && level>=1 )
        level--;

    else if ( GetAsyncKeyState(VK_SPACE) )
        change = true ;

    delay(100);

}

    speed = (500 - 100*level)/3 ;
    cleardevice();

}
//+++++++++++++++++++++++++++++++++++++++++++++++





//+++++++++++++++++++++++++++++++++++++++++++++++
void print_food(int food_x , int food_y )
{
    if (points1 > points2)
         food_preference(food_x , food_y ,p1_color ); // yellow

    else if (points1 < points2)
        food_preference(food_x , food_y ,p2_color ); // light

    else
     food_preference(food_x , food_y ,14 ); // yellow

}
//+++++++++++++++++++++++++++++++++++++++++++++++





//+++++++++++++++++++++++++++++++++++++++++++++++
void food_preference(int food_x , int food_y ,int color)
    {
        setfillstyle(1,color);
        setcolor(color);
        rectangle(food_x-10,food_y-10,food_x+10,food_y+10);
        floodfill(food_x , food_y , color);

    }
//+++++++++++++++++++++++++++++++++++++++++++++++





//+++++++++++++++++++++++++++++++++++++++++++++++
void keyboard_input1( int &prev , int &old_head_x , int &old_head_y , snake **head  )
{
       if(GetAsyncKeyState(VK_UP) && prev != 4 )
     {
         prev=3 ; // up
         old_head_y = (*head)->y ;
         (*head)->y = (*head)->y -20;
     }


    else if(GetAsyncKeyState(VK_DOWN) && prev != 3 )
    {
        prev=4 ; // down
        old_head_y = (*head)->y ;
        (*head)->y = (*head)->y+20;
    }

    else if(GetAsyncKeyState(VK_LEFT) && prev != 2 )
    {
        prev=1; // left
        old_head_x = (*head)->x ;
         (*head)->x = (*head)->x - 20 ;
    }


    else if(GetAsyncKeyState(VK_RIGHT) && prev != 1 )
    {
        prev=2; // right
        old_head_x = (*head)->x ;
        (*head)->x = (*head)->x + 20  ;
    }

    else
    {
        switch(prev)
        {
        case 1 :
            {
            old_head_x = (*head)->x ;
            (*head)->x = ((*head)->x)-20;
             break ;
            }

        case 2:
            {
                old_head_x = (*head)->x ;
               (*head)->x = (*head)->x + 20 ;
                break ;
            }
        case 3 :
            {
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y -20; break ;
            }
        case 4 :
             {
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y +20; break ;
            }

        }
    }

}
//+++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++
void keyboard_input2( int &prev , int &old_head_x , int &old_head_y , snake **head  )
{
       if(GetAsyncKeyState(0x57) && prev != 4 ) // w is up
     {
         prev=3 ; // up
         old_head_y = (*head)->y ;
         (*head)->y = (*head)->y -20;
     }


    else if(GetAsyncKeyState(0x53) && prev != 3 ) // s is down
    {
        prev=4 ; // down
        old_head_y = (*head)->y ;
        (*head)->y = (*head)->y+20;
    }

    else if(GetAsyncKeyState(0x41) && prev != 2 ) // a is left
    {
        prev=1; // left
        old_head_x = (*head)->x ;
         (*head)->x = (*head)->x - 20 ;
    }


    else if(GetAsyncKeyState(0x44) && prev != 1) // d is right
    {
        prev=2; // right
        old_head_x = (*head)->x ;
        (*head)->x = (*head)->x + 20  ;
    }

    else
    {
        switch(prev)
        {
        case 1 :
            {
            old_head_x = (*head)->x ;
            (*head)->x = ((*head)->x)-20;
             break ;
            }

        case 2:
            {
                old_head_x = (*head)->x ;
               (*head)->x = (*head)->x + 20 ;
                break ;
            }
        case 3 :
            {
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y -20; break ;
            }
        case 4 :
             {
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y +20; break ;
            }

        }
    }

}
//+++++++++++++++++++++++++++++++++++++++++++++++


void get_info()
{
    if(mode !=4)
    {
    cout << "player 1 : " ;
    cin >> p1 ;
    }

    if(mode ==2 )
    {
         cout << "player 2 : " ;
        cin >> p2 ;
    }

    if (mode ==3)
        strcpy(p2,"cpu");

    if(mode==4)
    {
        strcpy(p1,"cpu1");
        strcpy(p2,"cpu2");
    }


}


void selectcolors()
{

    settextstyle(BOLD_FONT , HORIZ_DIR , 4) ;
    setcolor(LIGHTCYAN);
              outtextxy(00,00,"select colors") ;

            while(1)
            {
                if(GetAsyncKeyState(VK_SPACE))
                    break;
            }

}


void cpu_move( int &prev , int &old_head_x , int &old_head_y , snake **head , snake **head1, int food_x , int food_y)
{

    // we always first give chance to the direction with less code (as in 1,2,3,4)

    if(prev == 1) // if snake is going to left
    {
        if( ( ( *head)->x-20 <= x_min || snake_ahead(  (*head)->x-20 , (*head)->y , (*head1) , *head ) ) || food_x > ( *head)->x ) // if it hits gonna the left boundary or there's snake at left side
        {

            if ((*head)->y-20 >= y_min && !snake_ahead(  (*head)->y-20 , (*head)->y , (*head1) , *head)) // if we can go to upside and there is no snake at upside
            {
                // go to upside
                    prev= 3 ;
                    old_head_y = (*head)->y ;
                    (*head)->y = (*head)->y-20;
                    return ;
            }

            else // if we cant go to upside we have to go to downside , no matter what
            {
                prev=4 ;
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y+20;
                return ;
            }

        }



        else if (food_x == (*head)->x )
        {
             if(food_y < (*head)->y && ! snake_ahead(  (*head)->x ,(*head)->y-20 , (*head1) , *head))  // if food is upper side and no snake at upper side
             {
                    // go to upside
                    prev= 3 ;
                    old_head_y = (*head)->y ;
                    (*head)->y = (*head)->y-20;
                    return ;
            }

          else if ( food_y > (*head)->y && !snake_ahead(  (*head)->x ,(*head)->y+20 , (*head1) , *head) ) //and no snake at lower side
              {
                  // go downside
                prev=4 ;
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y+20;
                return ;
            }

        }

            else // keep going
            {
                 old_head_x = (*head)->x ;
                (*head)->x = ((*head)->x)-20;
                return;
            }


    }



    else if(prev == 3) // if snake is going to up
    {
        if(( *head)->y-20 <= y_min || snake_ahead(  (*head)->x , (*head)->y-20 , (*head1) , *head ) )// if it hits gonna the upper boundary or there's snake at up side
        {
            if ((*head)->x-20 >= x_min && !snake_ahead(  (*head)->x-20 , (*head)->y , (*head1) , *head)) // if we can go to left side and there is no snake at left side
            {
                // go to leftside
                    prev= 1 ;
                    old_head_x = (*head)->x ;
                    (*head)->x = (*head)->x-20;
                    return;
            }

            else // if we cant go to upside we have to go to rightside , no matter what
            {
                // go to rightside
                prev=2 ;
                old_head_x= (*head)->x ;
                (*head)->x = (*head)->x+20;
                return;

            }

        }

         else if(food_x < (*head)->x && ! snake_ahead(  (*head)->x-20 ,(*head)->y , (*head1) , *head))  // if food is left side and no snake at left side
             {
                    // go to leftside
                    prev= 1 ;
                    old_head_x = (*head)->x ;
                    (*head)->x = (*head)->x-20;
                    return ;
            }

       // if food is at right side
        else if ( food_x > (*head)->x &&!snake_ahead(  (*head)->x+20 ,(*head)->y , (*head1) , *head) ) //and no snake at right side
              {
                  // go to rightside
                prev=2 ;
                old_head_x= (*head)->x ;
                (*head)->x = (*head)->x+20;
                return ;
            }

        else // keep going
        {
               old_head_y = (*head)->y ;
            (*head)->y = (*head)->y -20;
             return;
        }


    }

          else if(prev == 2) // if snake is going to right
    {
        if( ( ( *head)->x+20 >= x_max || snake_ahead(  (*head)->x+20 , (*head)->y , (*head1) , *head ) ) || food_x < ( *head)->x) // if it hits gonna the right boundary or there's snake at right side
        {
            if ((*head)->y-20 >= y_min && !snake_ahead(  (*head)->y-20 , (*head)->y , (*head1) , *head)) // if we can go to upside and there is no snake at upside
            {
                // go to upside
                    prev= 3 ;
                    old_head_y = (*head)->y ;
                    (*head)->y = (*head)->y-20;
                    return ;
            }

            else // if we cant go to upside we have to go to downside , no matter what
            {
                // go downside
                prev=4 ;
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y+20;
                return ;

            }

        }

            else if (food_x == (*head)->x )
        {
             if(food_y < (*head)->y && ! snake_ahead(  (*head)->x ,(*head)->y-20 , (*head1) , *head))  // if food is upper side and no snake at upper side
             {
                    // go to upside
                    prev= 3 ;
                    old_head_y = (*head)->y ;
                    (*head)->y = (*head)->y-20;
                    return ;
            }

          else if ( food_y > (*head)->y && !snake_ahead(  (*head)->x ,(*head)->y+20 , (*head1) , *head) ) //and no snake at lower side
              {
                  // go downside
                prev=4 ;
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y+20;
                return ;
            }


        }

         else // keep going
            {
                 old_head_x = (*head)->x ;
                (*head)->x = (*head)->x + 20 ;
                 return;

            }

    }


    else if(prev == 4) // if snake is going to down side
    {
        if(( *head)->y+20 >= y_max || snake_ahead(  (*head)->x , (*head)->y+20 , (*head1) , *head ) )// if it hits gonna the lower boundary or there's snake at lower side
        {
            if ((*head)->x-20 >= x_min && !snake_ahead(  (*head)->x-20 , (*head)->y , (*head1) , *head)) // if we can go to left side and there is no snake at left side
            {
                // go to left
                    prev= 1 ;
                    old_head_x = (*head)->x ;
                    (*head)->x = (*head)->x-20;
                    return;
            }

            else // if we cant go to upside we have to go to downside , no matter what
            {
                // go to right side
                prev=2 ;
                old_head_x= (*head)->x ;
                (*head)->x = (*head)->x+20;
                return;

            }

        }

         else if(food_x < (*head)->x && ! snake_ahead(  (*head)->x-20 ,(*head)->y , (*head1) , *head))  // if food is left side and no snake at left side
             {
                    // go to leftside
                    prev= 1 ;
                    old_head_x = (*head)->x ;
                    (*head)->x = (*head)->x-20;
                    return ;
            }

       // if food is at right side
        else if ( food_x > (*head)->x &&!snake_ahead(  (*head)->x+20 ,(*head)->y , (*head1) , *head) ) //and no snake at right side
              {
                  // go to rightside
                prev=2 ;
                old_head_x= (*head)->x ;
                (*head)->x = (*head)->x+20;
                return ;
            }

            else // keep going
            {
                old_head_y = (*head)->y ;
                (*head)->y = (*head)->y +20;
                 return;
            }

    }

}






bool snake_ahead(int future_head_x , int future_head_y , snake  *others_body , snake *self_body)
{
    snake* tp=others_body ;

    while(tp!=NULL)
    {
        if(future_head_x == tp->x && future_head_y == tp->y )
            return true ;

        tp=tp->next;
    }

     tp=self_body->next; // minimum distance to hit your own body

     if(tp==NULL)
        return false ;

    while(tp!=NULL)
    {
        if(future_head_x == tp->x && future_head_y == tp->y )
            return true ;

        tp=tp->next;
    }

    return false ;
}
