#include<conio.h>

int graph[11][11]={
           {0,1,0,1,0,0,0,0,0,0,0},
           {1,0,1,0,0,0,0,1,0,0,0},
           {0,1,0,0,0,1,1,0,0,0,0},
           {1,0,0,0,1,0,0,0,0,0,0},
           {0,0,0,1,0,1,0,0,0,0,0},
           {0,0,1,0,1,0,0,0,0,0,0},
           {0,0,1,0,0,0,0,1,0,0,0},
           {0,1,0,0,0,0,1,0,1,0,0},
           {0,0,0,0,0,0,0,1,0,1,0},
           {0,0,0,0,0,0,0,0,1,0,1},
           {0,0,0,0,0,0,0,0,0,1,0}
           };

int graphbackup[11][11];
int queue[100],front=-1,back=-1;

void enqueue(int key)
{
     if(front==-1)
       front++;
     queue[++back]=key;
    // printf("*%d enqued front=%d back=%d* ", key,front,back);
}

int dequeue()
{   
    if((front==-1)||(front>back))
       {
              //   printf("empty");
                 getch();
                 exit(0);
       }
       front++;
     //  printf("yess");
    return(queue[front-1]);
}

void bft()
{    int i,j,current;
     enqueue(1);
     while(current=dequeue())
     { 
      current--;
      
      printf("%d ",current+1);
      for(i=0;i<11;i++)
      {
        if(graph[current][i]==1)
          { 
           enqueue(i+1);
           for(j=0;j<11;j++)
             graph[j][i]=0;
           }
      }
      for(i=0;i<11;i++)
      {
        graph[current][i]=0;
        graph[i][current]=0;
      }
    /*  printf("\nqueue:");
      for(j=front;j<=back;j++)
      {
      printf("%d ",queue[j]);
      }
      printf("\n");
      */  
     }
     
}

int main()
{
int i,j;

for(i=0;i<11;i++)
   for(j=0;j<11;j++)
   {
    graphbackup[i][j]=graph[i][j];
   }
bft();
getch();
return 0;
}
