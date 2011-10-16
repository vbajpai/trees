// Program to Find Redundant Entries Using Binary Search Tree //

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define SIZE 50
typedef struct btree {
                        int info;
                        struct btree *left;
                        struct btree *right;
                     }BTREE;
BTREE* root=NULL;
BTREE* p, *q;
BTREE * maketree(int);
BTREE * setright(BTREE *,int);
BTREE * setleft(BTREE *,int); 
void pretrav(BTREE *);
void intrav(BTREE *);
void posttrav(BTREE *);
main(void)
{
     int k=1,n,e,a[SIZE],i=0;     
     char key;
             system("cls"); 
             printf("\n\nTo Find the Duplicate Entries Entered By User\n");
             printf("To Stop, HIT ESC\n\n");
             printf("Enter Number of Elements to Enter:");
             scanf("%d",&n);  
             
             while(k<=n)
             {
                         printf("\nEnter Element:");
                         scanf("%d",&e);
                         if(root==NULL)               // Tree Empty
                                    root =  maketree(e);        
                         else
                         {
                             p = q = root;
                             while(q!=NULL)
                             {
                                p = q;
                                if(e==p->info)
                                     break;
                                if(e > p->info)
                                          q = p->right;
                                else
                                          q = p->left;
                             }
                             if(e==p->info)
                             {
                                   a[i] = e;
                                   i++;
                             }
                             if(e > p->info)
                                           q = setright(p,e);
                             else
                             if(e < p->info)
                                           q = setleft(p,e);
                         }    
                         k++;                                                         
             }
             
             printf("\n\nTraversal!\n\n");
             printf("Redundant Entries:");
             for(k = 0;k<i;k++)
             {
                   printf("%d, ",a[k]);      
             }
             printf("\n\nNon-Redundant Entries:");
             
                         if(root==NULL)
                                 printf("\nTree Empty!");
                         else
                         {
                                 intrav(root);                                
                         }
                         getch();
                         
}
BTREE * maketree(int e) 
{
      p = (BTREE*)malloc(sizeof(BTREE));
      p->info = e;
      p->left = NULL;
      p->right = NULL;
      return(p);
}

BTREE * setleft(BTREE *p,int e)
{
      if(p==NULL)
                 printf("Void Insertion!");
      else
      {
                 if(p->left ==NULL)
                       p->left = maketree(e);                     
      }    
      return(p->left);                   
}

BTREE * setright(BTREE *p,int e)
{
      if(p==NULL)
                 printf("Void Insertion!");
      else
      {
                 if(p->right==NULL)
                          p->right = maketree(e);                     
      }                     
      return(p->left);  
}

void intrav(BTREE *p)
{
      if(p!=NULL)
      {
          intrav(p->left);         
          printf(" %d,",p->info);
          intrav(p->right);                         
      }
}



