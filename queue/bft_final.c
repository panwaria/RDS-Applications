//author: Abhinav Shrivastava
//bfs using retroactive queue

#include<conio.h>

#include<stdio.h>

 # define F 0
 # define T 1
 
float present=0;
int H;
//float trav[100][2];
float cache[100][3];


struct NODE *Binary_Tree (char , struct NODE *, int *);
   void Output(struct NODE *, int );
   struct  NODE *Balance_Right_Heavy(struct NODE *, int *);
   struct NODE *Balance_Left_Heavy(struct NODE *, int *);
   struct NODE *DELETE(struct NODE *, struct NODE *, int *);
  

struct NODE
   {
   	int data;
   	float time;
   	int Flag;
   	int mFlag;
   	struct  NODE *Left_Child;
   	struct  NODE *Right_Child;
   };
    struct NODE *te=NULL;
    struct NODE *td=NULL;
    struct NODE *Fr=NULL;
    struct NODE *B=NULL;
   



 struct NODE *  insert (int data, float time, struct NODE *Parent, int *H)
   {
   	struct NODE *Node1;
   	struct NODE *Node2;
   	if(!Parent)
   	{
   		Parent = (struct NODE*) malloc(sizeof(struct NODE));
   		Parent->time = time;
   		Parent->data = data;
   		Parent->Left_Child = NULL;
   		Parent->Right_Child = NULL;
   		Parent->Flag = 0;
   		Parent->mFlag = 0;
   		*H = T;
   		return (Parent);
   	}
    
   	if(time < Parent->time)
   	{
   		Parent->Left_Child = insert(data, time, Parent->Left_Child, H);
   		if(*H)
   		/* Left branch has grown higher */
   		{
   			switch(Parent->Flag)
   			{
   			case 1: /* Right heavy */
   				Parent->Flag = 0;
   				*H = F;
   				break;
   			case 0: /* Balanced tree */
   				Parent->Flag = -1;
   				break;
   			case -1: /* Left heavy */
   				Node1 = Parent->Left_Child;
   				if(Node1->Flag == -1)
   				{
   					printf("\n Left to Left Rotation\n");
   					Parent->Left_Child= Node1->Right_Child;
   					Node1->Right_Child = Parent;
   					Parent->Flag = 0;
   					Parent = Node1;
   				}
   				else
   				{
   					//Left to Right_Child rotation
   					Node2 = Node1->Right_Child;
   					Node1->Right_Child = Node2->Left_Child;
   					Node2->Left_Child = Node1;
   					Parent->Left_Child = Node2->Right_Child;
   					Node2->Right_Child = Parent;
   					if(Node2->Flag == -1)
   						Parent->Flag = 1;
   					else
   						Parent->Flag = 0;
   					if(Node2->Flag == 1)
   						Node1->Flag = -1;
   					else
   						Node1->Flag = 0;
   					Parent = Node2;
   				}
    
   				Parent->Flag = 0;
   				*H = F;
   			}
   		}
   	}
    
   	if(time > Parent->time)
   	{
   		Parent->Right_Child = insert(data, time, Parent->Right_Child, H);
   		if(*H)
   		/* Right branch has grown higher */
   		{
   			switch(Parent->Flag)
   			{
   			case -1: /* Left heavy */
   				Parent->Flag = 0;
   				*H = F;
   				break;
   			case 0: /* Balanced tree */
   				Parent->Flag = 1;
   				break;
    
   			case 1: /* Right heavy */
   				Node1 = Parent->Right_Child;
   				if(Node1->Flag == 1)
   				{
   					//Right to Right Rotation\n");
   					Parent->Right_Child= Node1->Left_Child;
   					Node1->Left_Child = Parent;
   					Parent->Flag = 0;
   					Parent = Node1;
   				}
   				else
   				{
   					//Right to Left Rotation
   					Node2 = Node1->Left_Child;
   					Node1->Left_Child = Node2->Right_Child;
   					Node2->Right_Child = Node1;
   					Parent->Right_Child = Node2->Left_Child;
   					Node2->Left_Child = Parent;
    
   					if(Node2->Flag == 1)
   						Parent->Flag = -1;
   					else
   						Parent->Flag = 0;
   					if(Node2->Flag == -1)
   						Node1->Flag = 1;
   					else
   						Node1->Flag = 0;
   					Parent = Node2;
   				}
    
   				Parent->Flag = 0;
   				*H = F;
   			}
   		}
   	}
   	if(time == Parent->time)
   	        printf("\noperation already exists\n");
   	return(Parent);
   }
   
   



   /* Balancing Right Heavy */
    
   struct NODE * Balance_Right_Heavy(struct NODE *Parent, int *H)
   {
   	struct NODE *Node1, *Node2;
    
   	switch(Parent->Flag)
   	{
   	case -1: 
   		Parent->Flag = 0;
   		break;
    
   	case 0: 
   		Parent->Flag = 1;
   		*H= F;
   		break;
    
   	case 1: /* Rebalance */
   		Node1 = Parent->Right_Child;
   		if(Node1->Flag >= 0)
   		{
   			// Right to Right Rotation
   			Parent->Right_Child= Node1->Left_Child;
   			Node1->Left_Child = Parent;
   			if(Node1->Flag == 0)
   			{
   				Parent->Flag = 1;
   				Node1->Flag = -1;
   				*H = F;
   			}
   			else
   			{
   				Parent->Flag = Node1->Flag = 0;
   			}
   			Parent = Node1;
   		}
   		else
   		{
   			// Right to Left Rotation
   			Node2 = Node1->Left_Child;
   			Node1->Left_Child = Node2->Right_Child;
   			Node2->Right_Child = Node1;
   			Parent->Right_Child = Node2->Left_Child;
   			Node2->Left_Child = Parent;
    
   			if(Node2->Flag == 1)
   				Parent->Flag = -1;
   			else
   				Parent->Flag = 0;
   			if(Node2->Flag == -1)
   				Node1->Flag = 1;
   			else
   				Node1->Flag = 0;
   			Parent = Node2;
   			Node2->Flag = 0;
   		}
   	}
   	return(Parent);
   }
    
   /* Balancing Left Heavy */
    
   struct NODE * Balance_Left_Heavy(struct NODE *Parent, int *H)
   {
   	struct NODE *Node1, *Node2;
    
   	switch(Parent->Flag)
   	{
   	case 1: 
   		Parent->Flag = 0;
   		break;
    
   	case 0: 
   		Parent->Flag = -1;
   		*H= F;
   		break;
    
   	case -1: /*  Rebalance */
   		Node1 = Parent->Left_Child;
   		if(Node1->Flag <= 0)
   		{
   			//Left to Left Rotation
   			Parent->Left_Child= Node1->Right_Child;
   			Node1->Right_Child = Parent;
   			if(Node1->Flag == 0)
   			{
   				Parent->Flag = -1;
   				Node1->Flag = 1;
   				*H = F;
   			}
   			else
   			{
   				Parent->Flag = Node1->Flag = 0;
   			}
   			Parent = Node1;
   		}
   		else
   		{
   			//Left to Right Rotation
   			Node2 = Node1->Right_Child;
   			Node1->Right_Child = Node2->Left_Child;
   			Node2->Left_Child = Node1;
   			Parent->Left_Child = Node2->Right_Child;
   			Node2->Right_Child = Parent;
    
   			if(Node2->Flag == -1)
   				Parent->Flag = 1;
   			else
   				Parent->Flag = 0;
    
   			if(Node2->Flag == 1)
   				Node1->Flag = -1;
   			else
   				Node1->Flag = 0;
   			Parent = Node2;
   			Node2->Flag = 0;
   		}
   	}
   	return(Parent);
   }
    
   /* Replace the NODE at which key is found with last Right_Child key of a Left_Child child */
    
   struct NODE * DELETE(struct NODE *R, struct NODE *Temp, int *H)
   {
   	struct NODE *DNODE = R;
   	if( R->Right_Child != NULL)
   	{
   		R->Right_Child = DELETE(R->Right_Child, Temp, H);
   		if(*H)
   			R = Balance_Left_Heavy(R, H);
   	}
   	else
   	{
   		DNODE = R;
   		Temp->time = R->time;
   		R = R->Left_Child;
   		free(DNODE);
   		*H = T;
   	}
   	return(R);
   }
   /* Delete the key element from the tree */
   
   struct NODE * InOrderSuc(float time, struct NODE *ptr, struct NODE *req)
   {
          struct NODE *temp = NULL;
          if(time<ptr->time)
             return(InOrderSuc(time, ptr->Left_Child, ptr));
          if(time>ptr->time)
             return(InOrderSuc(time, ptr->Right_Child, req));
          if(time==ptr->time)
             {
                if(ptr->Right_Child==NULL)
                   return(req);
                else
                  { 
                    temp=ptr->Right_Child;
                    while(temp->Left_Child!=NULL)
                      temp=temp->Left_Child;
                    return(temp);
                  }
             }        
   }
    
   struct NODE * Delete_Element(struct NODE *Parent, float time, int *H)
   {
   	struct NODE *Temp;
   	if(!Parent)
   	{
   		printf("\n Information does not exist");
   		return(Parent);
   	}
   	else
   	{
   		if (time< Parent->time )
   		{
   			Parent->Left_Child = Delete_Element(Parent->Left_Child, time, H);
   			if(*H)
   				Parent = Balance_Right_Heavy(Parent, H);
   		}
   		else
   			if(time > Parent->time)
   			{
   				Parent->Right_Child = Delete_Element(Parent->Right_Child, time, H);
   				if(*H)
   					Parent = Balance_Left_Heavy(Parent, H);
   			}
   			else
   			{
   				Temp= Parent;
   				if(Temp->Right_Child == NULL)
   				{
   					Parent = Temp->Left_Child;
   					*H = T;
   					free(Temp);
   				}
   				else
   					if(Temp->Left_Child == NULL)
   					{
   						Parent = Temp->Right_Child;
   						*H = T;
   						free(Temp);
   					}
   					else
   					{
   						Temp->Left_Child = DELETE(Temp->Left_Child, Temp, H);
   						if(*H)
   							Parent = Balance_Right_Heavy(Parent, H);
   					}
   			}
   	}
   	return(Parent);
   }


int count(struct NODE *ptr)
{
    if(ptr==NULL)
       return 0;
     else return(count(ptr->Left_Child)+1+count(ptr->Right_Child));
       
}

struct NODE * findKthInOrder(struct NODE * t, int k) 
{ 
 if (t == NULL) 
     return NULL; 
// can't find anything, empty 
 int numLeft = count(t->Left_Child);
  if (numLeft + 1 == k) 
     { // current NODE 
        //  return t->data;
          return t; 
     } 
  else 
       if (numLeft >= k) 
          { // in Left_Child subtree return 
               return findKthInOrder(t->Left_Child, k);
          }
       else 
          { 
               return findKthInOrder(t->Right_Child, k - (numLeft + 1)); 
          }
 } 

int pos(struct NODE *ptr, float time)
{
    if(ptr==NULL)
      return 0;
      
    if(ptr->time > time)
     return pos(ptr->Left_Child,time);
    else
     return pos(ptr->Left_Child,time)+1+pos(ptr->Right_Child,time);
}


int front(struct NODE *te, struct NODE *td, float time)
{
struct NODE *temp=NULL;
int rank;
rank = pos(td,time);
temp=findKthInOrder(te,1+rank);
if(temp==NULL)
    return -1;
if(temp->time<=time)
    return(temp->data);
else 
    return -1;
}

int back(struct NODE *te, float time)
{
struct NODE *temp=findKthInOrder(te, pos(te,time));
if(temp==NULL)
     return(-1);
else
     return(temp->data);
}

void setfront(struct NODE *te, struct NODE *td)
{
struct NODE *temp=NULL;
int rank;
rank = pos(td,present);
temp=findKthInOrder(te,1+rank);
Fr=temp;
}

void setback(struct NODE *te)
{
     struct NODE *temp=findKthInOrder(te, pos(te,present));
     B=temp;
}

int isexists(struct NODE *ptr, float time)
{
    static int flag = 0;
    if(ptr==NULL)
         return flag;
    
    if(ptr->time==time)
         {
            flag=1;
            return flag;
         }
    if(flag==1)
        return flag;
    isexists(ptr->Left_Child,time);
    if(flag==1)
        return flag;
     isexists(ptr->Right_Child,time);
    if(flag==1)
        return flag;
    return flag;
     
     
}

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


void enqueue(int data)
{
     cache[data][0]=present+1;
     cache[data][2]=0;
     te=insert(data,++present,te,&H);
                      setfront(te, td);
                      setback(te);
}

int dequeue()
{
    int temp;
    if(Fr!=NULL)
      {
             temp=Fr->data;
             td=insert(0,++present,td,&H);
             setfront(te, td);
             setback(te);
             cache[temp][1]=present;
             return(temp);
      }
    else
     {
       printf("empty\n");
       return 0 ;
     }
     
}

void bft()
{    int i,j,k,current;
     k=0;
     enqueue(1);
     while(current=dequeue())
     { 
      current--;
      
      printf("%d ",current+1);
     // trav[k][0]=(float)(current+1);
     // trav[k][1]=present;
      k++;
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

struct NODE * in(struct NODE * ptr,float t1,float t2)
{ 
       struct NODE *temp;     
       if(ptr==NULL)
          return NULL;
       if(temp=in(ptr->Left_Child,t1,t2))
          return temp;
         
       if(((ptr->time)<t2)&&((ptr->time)>t1))
       {
          return(ptr);
       }
       if(temp= in(ptr->Right_Child,t1,t2))
         return temp;
       return NULL;
}
void reposition(int target)
{
int i=0;
 for(i=0;i<11;i++)
 {
   graph[target-1][i]=0;
   graph[i][target-1]=0;
 }
 bft();
 return;
}  

void mark(int target)
{    
     float t1,t2;
     struct NODE *temp;
     cache[target][2]=1;
     t1=cache[target][1];
     temp=InOrderSuc(t1,td,NULL);
     if(temp!=NULL)
        t2=temp->time;
      else
        t2=10000.0;    
     
     temp=in(te,t1,t2);
     if(temp!=NULL)
     {
      
     mark(temp->data);
     
     while(1)
     {
       temp=InOrderSuc(temp->time,te,NULL);
       if(temp==NULL)
          break;
       if(temp->time>=t2)
         break;
       mark(temp->data);
     }
     }
     
}
void removenode(int target)
{
 mark(target);
 reposition(target);  
}

int main()
{
int i,j;
int target;
for(i=0;i<12;i++)
   for(j=0;j<11;j++)
   {
    graphbackup[i][j]=graph[i][j];
   }
bft();
for(i=0;i<11;i++)
   for(j=0;j<11;j++)
   {
    graph[i][j]=graphbackup[i][j];
   }

for(i=1;i<=11;i++)
  {
   //              printf("%2d %.1f %.1f\n",(int)trav[i][0],trav[i][1],trav[i][2]);
                printf("%2d %.1f %.1f %d\n",i,cache[i][0],cache[i][1],(int)cache[i][2]);
  }
printf("\nselect node to remove :");
scanf("%d",&target);
removenode(target);

//struct NODE *temp = InOrderSuc(16.0,td,NULL);
//printf("\n\nnext dequed :  %f",temp->time);/
for(i=1;i<=11;i++)
  {
     //            printf("%2d %.1f %.1f\n",(int)trav[i][0],trav[i][1],trav[i][2]);
                  printf("%2d %.1f %.1f %d\n",i,cache[i][0],cache[i][1],(int)cache[i][2]);
  }
getch();
return 0;
}
