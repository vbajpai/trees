// Binary Search Tree Implementation //


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct btree {
            			int info;
            			struct btree *left;
            			struct btree *right;
		             }BTREE;

typedef struct stack {
                			BTREE *info;
                			struct stack *next;
                			int rchild;      // TREATED AS BOOLEON FOR POSTORDER TRAVERSAL ONLY
		             }s;
s* top=NULL;           // TOP POINTS TO STACK TOP
int rchild=FALSE;       // FOR CHECK
int empty=FALSE;
BTREE* root=NULL;
BTREE* p, *q;
BTREE * maketree(int);
BTREE * setright(BTREE *,int);
BTREE * setleft(BTREE *,int);
void pretrav(BTREE *);
void intrav(BTREE *);
void posttrav(BTREE *);
void pretravstack(BTREE *);
void posttravstack(BTREE *);
int emptys(void);
void pushs(BTREE *);
BTREE * pops(void);
void freenode(s*);
s* getnode(void);
void intravstack(BTREE *);
void search(int,BTREE **,BTREE **,int *,int *);
BTREE *pos,*parent,*child;
void deltree(BTREE *);
void delnodecaseA(BTREE *,BTREE *);
void delnodecaseB(BTREE *,BTREE *);
main(void)
{
     int ch,e,found=FALSE,level=0;
     while(1)
     {
	     system("cls");
	     printf("\n\nBinary Search Tree Implementation Using Dynamic Nodes\n\n");
	     printf("1. Insert Elements\n");
	     printf("2. Traverse Tree\n");
	     printf("3. Search Element\n");
	     printf("4. Delete Elements\n");
	     printf("5. Exit\n");
	     printf("\nEnter Choice:");
	     scanf("%d",&ch);
	     switch(ch)
	     {
		 case 1:
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
				   printf("\nDuplicate Entry!");
				   getch();
				   break;
			     }
			     if(e>=p->info)
					   q = setright(p,e);
			     else
					   q = setleft(p,e);
			 }
			 break;
		 case 2:
			 if(root==NULL)
				 printf("\nTree Empty!");
			 else
			 {
				 printf("\nPreoder Traversal:");
				 pretrav(root);
				 printf("\n\nPreorder Traversal Using Stacks:");
				 pretravstack(root);
				 printf("\n\nInorder Traversal:");
				 intrav(root);
				 printf("\n\nInorder Traversal Using Stacks:");
				 intravstack(root);
				 printf("\n\nPostorder Traversal:");
				 posttrav(root);
				 printf("\n\nPostorder Traversal Using Stacks:");
				 posttravstack(root);
			 }
			 getch();
			 break;
		 case 3:
             
             printf("\nEnter Element To Search:");
			 scanf("%d",&e);
			 search(e,&pos,&parent,&found,&level);
			     if(pos==NULL && parent == NULL)
			                  printf("\nTree Empty!");
			     else
                 {             
                     if(found==TRUE)
    				       printf("\n%d found at level %d!",e,level);
    			     else
    				       printf("\n%d does not exist!",e);
                 }
             found = FALSE;
             level = 0;
			 getch();
			 break;
		 case 4:
             printf("\nEnter Element To Delete:");
			 scanf("%d",&e);			 
			 search(e,&pos,&parent,&found,&level);
             if(pos==NULL and parent ==NULL)
                          printf("\nTree Empty!"); 
             else
             {
    			 if(found==FALSE)
                        printf("\n%d Does Not Exist!",e);
                 else
                 {
                        if(pos->left !=NULL && pos->right!=NULL)
                                 delnodecaseB(pos,parent);
                        else
                                 delnodecaseA(pos,parent); 
                        deltree(pos);                                       
                        printf("\n%d Deleted Successfully!",e);               
                 }
             }
             found = FALSE;
             level = 0;
             getch();
			 break;
		 case 5:
             exit(0);
	     }
     }
}

void delnodecaseB(BTREE *pos,BTREE *parent)
{
     BTREE*save,*child;
     save = pos;
     child = pos->right;
         while(child->left !=NULL)
         {
             save = child;
             child = child->left;                  
         }        
     delnodecaseA(child,save);
         if(parent!=NULL)
         {
             if(parent->left == pos)
                             parent->left = child;
             else
                             parent->right = child;
         }
         else
             root = child;
     child->left = pos->left;
     child->right = pos->right;
}

void delnodecaseA(BTREE *pos,BTREE *parent)
{
     if(pos->left == NULL and pos->right ==NULL)   /* NODE IS LEAF 
                                                                         (CASE 1)     */
         {
             if(parent == NULL)                       // ROOT NODE      
                 root = NULL;
             else
             {                                               
                 if(parent->left == pos)
                                 parent->left = NULL;    
                 else
                                 parent->right = NULL;
             }
                                
         }
     else
         {
             if(pos->left ==NULL || pos->right == NULL)  /* NODE HAS 1 CHILD */
             {                    
                          if(pos->right == NULL)
                                         child = pos->left;
                          else
                                         child = pos->right;
                  if(parent!=NULL)
                  {                       
                          if(parent->left == pos)
                                          parent->left = child;    
                          else
                                          parent->right = child;
                  }
                  else
                          root=child;   
                                                               
             }    
         }          
}

void deltree(BTREE *pos)                               // DELETE TREE NODE
{
    free(pos);    
}

BTREE * maketree(int e)                               // CREATE TREE NODE
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
		 if(p->left !=NULL)
			    printf("Invalid Insertion!");
		 else
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
		 if(p->right!=NULL)
			    printf("Invalid Insertion!");
		 else
			    p->right = maketree(e);
      }
      return(p->right);
}

void pretrav(BTREE *p)
{
      if(p!=NULL)
      {
    	  printf(" %d->",p->info);
    	  pretrav(p->left);
    	  pretrav(p->right);
      }
}

void intravstack(BTREE *p)
{
     while(p!=NULL && empty==FALSE)
     {
         while(p!=NULL)
         {
              pushs(p);
              p = p->left;                       
         }     
         while(!emptys())
         {                         
              p = pops();
              printf("%d->",p->info);
              if(p->right !=NULL)
              {
                          p = p->right;           
                          empty = FALSE;               
                          break;                           
              }              
              else
                          empty = TRUE;    
         }
         
     }
     empty = FALSE;
}

void pretravstack(BTREE *p)
{
     while(!emptys() || p!=NULL)
     {
    	while(p!=NULL)
    	{
    	   printf("%d->",p->info);
    	   if(p->right!=NULL)
    			     pushs(p->right);
    	   p = p->left;
    	}
       if(!emptys())
       	   p = pops();
     }
}

void posttravstack(BTREE *p)
{
     while(p!=NULL)
     {
            while(p!=NULL)
            {
                  pushs(p);
                  if(p->right!=NULL)       
                  {
                             rchild = TRUE;
                             pushs(p->right);     
                  }              
                             rchild = FALSE;
                             p = p->left;                                                 
                  
            }              
            p = pops();
            while(rchild==FALSE && !emptys())
            {
                 printf("%d->",p->info);
                 p = pops();                 
            }
            if(!emptys())
                 rchild = FALSE;
            else
            {
                printf("%d->",p->info);
                break;
            }
                          
     }     
}

BTREE * pops(void)
{
      BTREE *x;
      s* temp;
      x = top->info;
      rchild = top->rchild;
      temp = top;
      top = top->next;
      freenode(temp);
      return(x);
}

void freenode(s* p)
{
     free(p);
}

int emptys(void)
{
    if(top==NULL)
		 return(TRUE);
    else
         return(FALSE);    
}

void pushs(BTREE *x)
{
     s* p;
     p = getnode();
     p->info = x;
     p->next = top;
     if(rchild==TRUE)
                 p->rchild = TRUE;    
     else
                 p->rchild = FALSE;
     top = p;
}

s* getnode(void)
{
    s* p;
    p = (s*)malloc(sizeof(s));
    return(p);
}


void intrav(BTREE *p)
{
      if(p!=NULL)
      {
          intrav(p->left);         
          printf(" %d->",p->info);
          intrav(p->right);                         
      }
}

void posttrav(BTREE *p)
{
      if(p!=NULL)
      {
          posttrav(p->left);         
          posttrav(p->right);     
          printf(" %d->",p->info);                    
      }
}

void search(int e,BTREE **pos,BTREE **parent,int *found,int *level)
{
    if(root==NULL)
             *pos = *parent = NULL;      
    else
			 {
			     *pos = root;
			     while(*pos!=NULL)
			     {
    				 if((*pos)->info == e)
    				 {
    					 if(*pos==root)
    					            *parent = NULL;
                         *found = TRUE;                         
    					 break;
    				 }
    				 else
    				 {
                         *parent = *pos;
    					 if(e > (*pos)->info )    					           
                                  *pos = (*pos)->right;                         	      
    					 else		         
    						      *pos = (*pos)->left;
    					 (*level)++;
    				 }
			     }
			     
			 }  
}
