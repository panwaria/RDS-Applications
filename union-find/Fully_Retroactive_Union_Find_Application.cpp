/* 
Author: Prakhar Panwaria
Date: 14-10-08
Description: To implement Full-Retroactivity in Union-Find 
             Data Structure by using Hash Table.
*/
#include<iostream>
#include<conio.h>
#include<stdio.h>
using namespace std;

struct operation
{
       float timer;
       int op;
       float x;
       float y;
       float t;
       operation *right;
       operation *left;       
};
operation* head;
float timer=0;

struct node
{
       int no;
       float t;
       float value;
       node *parent;
       int tree;
       int rank;
};
float e[200][200]; // Representing Edges.
node* tree[200];
int tree_no=0;
node* _node[200];
int node_no=0;
int hash_node[200];

int Create(float val,float t);
int Union(float x,float y, float timer);
node* Find(node*);
int Sameset();
int Manipulate(float t);
void add_operation(int op,float x,float y,float t);
void display_operation();
void insert_operation();
void delete_operation();

int main()
{
            
      int op=100;
      int res;
      cout<<"                 OPERATIONS\n";
      cout<<"-----------------------------------------------\n\n";
      cout<<"0. Show Menu\n";
      cout<<"1. Create(x)\n";
      cout<<"2. Union(x,y)\n";
      cout<<"3. Find(x)\n";
      cout<<"4. Sameset(x,y)\n";
      cout<<"5. Display operations\n";
      cout<<"6. Insert operation at time 't'\n";
      cout<<"7. Delete operation at time 't'\n";
      cout<<"8. Evaluate the Temperature\n";
      cout<<"9. Exit\n";
      cout<<"\n>>Enter the operation no. at time = "<<timer<<" : ";

while(op!=9)
{
      float sum=0,t,frac=0;
      int total=0,i;
      cin>>op;

      switch(op)
      {
                case 0:
                      cout<<"\n\n                 OPERATIONS\n";
                      cout<<"-----------------------------------------------\n\n";
                      cout<<"0. Show Menu\n";
                      cout<<"1. Create(x)\n";
                      cout<<"2. Union(x,y)\n";
                      cout<<"3. Find(x)\n";
                      cout<<"4. Sameset(x,y)\n";
                      cout<<"5. Display operations\n";
                      cout<<"6. Insert operation at time 't'\n";
                      cout<<"7. Delete operation at time 't'\n";
                      cout<<"8. Evaluate the Temperature\n";
                      cout<<"9. Exit\n";
                      //cout<<"Enter the operation no. at time = "<<timer<<" : ";
                      break;
                case 1:
                     float val;
                     cout<<"\n**************** CREATE(x) ********************\n";
                     cout<<"Enter the value of the node to be created : ";
                     cin>>val;
                     cout<<"Enter the temperature measured at this station: ";
                     cin>>t;
                     cout<<"\n";
                     add_operation(op,val,0,t);
                     break;
                case 2:
                     float x,y;
                     cout<<"\n**************** UNION(x,y) ********************\n";
                     cout<<"Enter the value of first node(x) : ";
                     cin>>x;
                     cout<<"Enter the value of second node(y) : ";
                     cin>>y;    
                     cout<<"\n";
                     add_operation(op,x,y,-10);
                     break;
                case 3:
                     int h;
                     Manipulate(-100);
                     cout<<"\n**************** FIND OPERATION **********************\n";
                     cout<<"Enter the value of the node whose root is to be found : ";
                     cin>>val;
                     h=hash_node[(int)val];
                     node *root;
                     root=Find(_node[h]);
                     cout<<"\nThe value of the root is : "<<root->value<<"\n\n";
                     break;
                case 4:
                     res=Sameset();
                     break;      
                case 5:
                     display_operation();
                     break;     
                case 6:
                     insert_operation();
                     break;
                case 7:
                     delete_operation();
                     break;        
                case 8: 
                     cout<<"\n**************** TEMPERATURE EVALUATION ********************\n";
                     node_no=0;
                     Manipulate(-100);
                     sum=0;total=0;frac=0;
                     
                     cout<<"Total no. of Nodes = "<<node_no<<"\n";
                     for(i=0;i<node_no;i++)
                     {
                       cout<<"Node["<<i<<"]=> Value="<<_node[i]->value<<", Tmp.="<<_node[i]->t<<", Tree="<<_node[i]->tree<<", no="<<_node[i]->no<<"\n";
                     }
                     for(i=0;i<node_no;i++)
                     {
                                           
                     // hash_node[(int)i]
                             if(_node[i]->tree == 1)
                             {     //cout << "Ho";
                                   frac += (float)(_node[i]->t/_node[i]->no);
                                   cout<<"\nTree["<<i<<"] Value="<<_node[i]->value<<", Tmp.Sum = "<<_node[i]->t<<", no= "<<_node[i]->no<<"\n";
                                   //sum += _node[i]->t;
                                   //total += _node[i]->no;
                             }
                     }
                     //cout<<"\nTemperature Sum = "<<sum<<" and Total= "<<total<<"\n";
                     cout<<"\nResult ="<<frac<<"\n\n";
                     break;
                                              
                case 9:
                     exit(0);
                     break;
                case 10:
                    for(int i=0;i<8;i++)
                    {
                        for(int j=0;j<8;j++)
                        {
                            if(e[i][j] == -10)
                            cout<<"x"<<" ";
                            else
                            cout<<e[i][j]<<" ";
                        }
                        cout<<"\n";
                    }
                     break;     
                default:
                     cout<<"\nEnter valid operation again.\n";
      }
      cout<<">>Enter the operation no. at time = "<<timer<<" : ";
}// end of while
//getche();
return 0;
}//End of Main()

void add_operation(int op,float x,float y,float t)
{
     operation *temp,*temp2;
     if(timer == 0)
     {
              temp = new operation;
              temp->timer = timer++;
              temp->op = op;
              temp->x=x;
              temp->y=y;
              temp->t=t;
              temp->left = NULL;
              temp->right = NULL;
              head=temp;
     }
     else
     {
         
         temp2=head;
         while(temp2->right !=NULL)
         {
               temp2=temp2->right;
         }
         temp = new operation;
         temp->timer= timer++;
         temp->op=op;
         temp->x=x;
         temp->y=y;
         temp->t=t;
         temp->left=NULL;
         temp->right=NULL;
         temp2->right=temp;
     }
}// End of add_operation()

void display_operation()
{
     operation *temp;
     temp=head;
     cout<<"\n**************** DISPLAY OPERATION ********************\n";
     while(temp != NULL)
     {
            cout<<"--["<<temp->op<<",t="<<temp->timer<<",x="<<temp->x<<",y="<<temp->y<<",t="<<temp->t<<"]--";
            temp = temp->right;
     }
     cout<<"\n\n";
}//End of display_operation()

void insert_operation()
{
     float t,x,y,tmp;
     int op,flag=1;
     operation *temp1,*temp2,*temp;
     cout<<"\n**************** INSERT OPERATION ********************";
     cout<<"\nEnter the time at which operation is inserted : ";
     cin>>t;
     cout<<"Enter the operation no. to insert : ";
     cin>>op;
     while(op!=1 && op!=2)
     {
                cout<<"Enter the correct operation no. to insert : ";            
                cin>>op;
     } 
     if(op==1)
     {
                cout<<"Enter the value of the node to be created : ";
                cin>>x;
                cout<<"Enter the temperature measured at this station: ";
                cin>>tmp;
                cout<<"\n";
                y=0;
     }
     else if(op==2)
     {
                 cout<<"Enter the value of first node(x) : ";
                 cin>>x;
                 cout<<"Enter the value of second node(y) : ";
                 cin>>y;  
                 tmp=-10;  
                 cout<<"\n";
     }     
     temp1=head;
     temp = new operation;
     temp->timer = t;
     temp->op = op;
     temp->x = x;
     temp->y = y;
     temp->t = tmp;
     if(temp1 == NULL)
     {
           temp->left=NULL;
           temp->right=NULL;
           head=temp;
     }
     else if(temp1->right == NULL)
     {
         if(temp1->timer > t)
         {
               temp->left=NULL;
               temp->right=temp1;
               temp1->left=temp;
               head=temp;
         }
         else
         {
               temp->left=temp1;
               temp->right=NULL;
               temp1->right=temp;
         }             
     }
     else if(temp1->timer > t)
     {
           temp->left=NULL;
           temp->right=temp1;
           temp1->left=temp;
           head=temp;
     }
     else
     {
           while(temp1->right->timer < t)
           {
               temp1=temp1->right;
               if(temp1->right == NULL)
               {
                       flag=0;break;
               }
           }
           if(flag!=0)
           {
               temp2=temp1->right;
               temp->left=temp1;
               temp->right=temp2;
               temp1->right=temp;
               temp2->left=temp;
           }
           else
           {
               temp1->right=temp;
               temp->left=temp1;
               temp->right=NULL;
           }
     }
          cout<<"Now the list of operations become : \n";
          display_operation();
}//End of insert_operation().
  
void delete_operation()
{
     float t,least_time;
     int op,flag=1;
     operation *temp1,*temp2,*temp;
     cout<<"\n**************** DELETE OPERATION ********************";
     cout<<"\nEnter the time at which operation is to be deleted : ";
     cin>>t;
     temp1=head;
     if(head==NULL)
            cout<<"No Operations now...Sorry!! \n";
     else
     {
         least_time=head->timer;
         if(t!=timer && t!=least_time )
         {
             
             while(temp1->right->timer != t)
             {
                   temp1=temp1->right;               
                   if(temp1->right == NULL)
                   {
                           flag=0;break;
                   }
             }
             if(flag!=0)
             {
                 temp2 = temp1->right;
                 op = temp2->op;
                 if(temp2->right!=NULL)
                      temp2->right->left = temp1;
                 temp1->right = temp2->right; 
             }
             else
                 cout<<"\nTime="<<t<<" not found.\n";
         }  
         else if(t == least_time)
         {
              if(temp1->timer == least_time)
                      head = temp1->right;
               else
                      cout<<"\nTime=0 not found!!!.\n";
         }
         else if(t == timer)
         {
             temp1=head;
             while(temp1->right->timer != t)
             {
                   temp1=temp1->right;
             }
             temp1->right = NULL; 
         } 
     }    
    
     cout<<"Now the list of operations become : \n";
     display_operation();   
}// End of delete_operation().
                    
 
int Create(float val,float t)
{
    hash_node[(int)val]=node_no;
    node *temp;
    temp = new node;
    /*cout<<"\nEnter the temperature measured at this station: ";
    cin>>temp->t;*/
    temp->t=t;
    temp->no=1;
    temp->value = val;
    temp->parent = temp;
    temp->tree=1;
    temp->rank=0;
    /* Taking care of all the nodes. */
    _node[node_no++]=temp;
    /* Taking note of trees. */
    tree[tree_no++]=temp;

    return 0;    
}

int Union(float x,float y,float timer)
{ 
    node *xRoot, *yRoot, *root;
    int i;
    xRoot=Find(_node[hash_node[(int)x]]);
    yRoot=Find(_node[hash_node[(int)y]]);    
   
    if(xRoot->rank > yRoot->rank)
    {
        yRoot->parent = xRoot;
        //
        xRoot->no += 1;
        xRoot->t += yRoot->t;
        //
        root = xRoot;
        yRoot->tree=0;
    }
    else if(xRoot->rank < yRoot->rank) 
    {
        xRoot->parent = yRoot;
        //
        yRoot->no += 1;
        yRoot->t += xRoot->t;
        //
        root = yRoot;
        xRoot->tree=0;
    }
    else if(xRoot->rank == yRoot->rank)
    {
        yRoot->parent = xRoot;
        //
        xRoot->no += 1;
        xRoot->t += yRoot->t;
        //
        root = xRoot;
     	xRoot->rank = xRoot->rank + 1;
     	yRoot->tree=0;
    }
    if(root == xRoot)
    {
        e[(int)yRoot->value][(int)root->value]=timer;
        e[(int)root->value][(int)yRoot->value]=timer;
    }
    else if(root == yRoot)
    {
        e[(int)xRoot->value][(int)root->value]=timer;
        e[(int)root->value][(int)xRoot->value]=timer;
    }
    for(i=0;i<200;i++)
    {
        if(root == xRoot &&  _node[hash_node[(int)i]]->parent == yRoot)
            {
                e[(int)root->value][i]=timer;
                e[i][(int)root->value]=timer;
            }
        else if (root == yRoot &&  _node[hash_node[(int)i]]->parent == xRoot)
            {   
                e[(int)root->value][i]=timer;
                e[i][(int)root->value]=timer;
            }       
    }
}// End of Union().

node* Find(node* temp)
{
    if(temp->parent == temp)
          return temp;
    else
    {
          temp->parent = Find(temp->parent);
          return temp->parent;
    }
}// End of Find().

int Sameset()
{
    float t,x,y;
    cout<<"\n************* SAMESET(x,y) *******************\n";
    cout<<"Enter the time at which the operation is to perform : ";
    cin>>t;
    cout<<"Enter the value of first node(x) : ";
    cin>>x;
    cout<<"Enter the value of second node(y) : ";
    cin>>y; 
    Manipulate(-100);
    node *xRoot, *yRoot, *root;
    xRoot=Find(_node[hash_node[(int)x]]);
    yRoot=Find(_node[hash_node[(int)y]]);  
    if(xRoot == yRoot)
    {
        if(e[(int)xRoot->value][(int)x] <= t && e[(int)yRoot->value][(int)y] <= t)
            cout<<"'"<<x<<"' and '"<<y<<"' are in same set.\n";
        else
            cout<<"'"<<x<<"' and '"<<y<<"' are NOT in same set.\n";
    }
    else
        cout<<"'"<<x<<"' and '"<<y<<"' are NOT in same set.\n";

    return 0;    
}
                            
int Manipulate(float t)
{  
    int i,j;
    for(i=0;i<200;i++)
    {
         for(j=0;j<200;j++)
         {
               e[i][j] = -10;
        }
    }
    operation *temp;
    temp = head;
    if(t == -100)
    {
        while(temp != NULL)
        {
            if(temp->op == 1)
                   {Create(temp->x,temp->t);
                    e[(int)temp->x][(int)temp->x]=temp->timer;}
            else if(temp->op == 2)
                   Union(temp->x,temp->y,temp->timer);
                  
            temp=temp->right;
        }        
    }
    else
    {
        while(temp->timer <= t && temp != NULL)
        {
            if(temp->op == 1)
               {Create(temp->x,temp->t);
                e[(int)temp->x][(int)temp->x]=temp->timer;}
            else if(temp->op == 2)
               Union(temp->x,temp->y,temp->timer);
            if(temp->right != NULL)
                temp=temp->right;
            else break;
        }
    }
    return 0;    
}//End of Manipulate.
                            
