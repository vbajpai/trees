// Expression Tree Implementation Using Prefix Expression //

/*
Algorithm for creating Expression Tree from a Prefix Expression
1) Reverse the prefix expression
2) Examine the next element in the input.
3) If it is operand then
i) create a leaf node i.e. node having no child (node- >left_child=node->right_child=NULL)
ii) copy the operand in data part
iii) PUSH node's address on stack
4) If it is an operator, then
i) create a node
ii) copy the operator in data part
iii) POP address of node from stack and assign it to node->left_child
iv) POP address of node from stack and assign it to node->right_child
v) PUSH node's address on stack
5) If there is more input go to step 2
6) If there is no more input, POP the address from stack, which is the address of the ROOT node of Expression Tree.

*/

// Expression Tree Implementation Using Prefix Expression //

#include<stdio.h>
#include<conio.h>
#include<string.h>          //for strrev()
#include<stdlib.h>          // for malloc()

#define SIZE 50
#define TRUE 1
#define FALSE 0

// TREE STRUCTURE //
typedef struct tree {
                        char info;                  // to account for operators as nodes
                        struct tree *left;
                        struct tree *right;    
                    }BTREE;
BTREE *root = NULL;

// STACK STRUCTURE //
typedef struct stack {
                        BTREE * info[SIZE];         // stack contains node's addresses
                        int top;   
                     }STACK;
STACK s;                     

void CreateExprTree(char *);
BTREE* maketree(char);
BTREE * getnode(void);
int isdigits(char);
void pushs(BTREE *);
void pretrav(BTREE *);
void intrav(BTREE *);
void postrav(BTREE *);
BTREE* pops(void);

main(void)
{
          s.top = -1;          
          char prefix[SIZE];
          
          printf("\n\nExpression Tree Implementation Using Prefix Expression\n");
          printf("------------------------------------------------------\n\n");
          printf("\n\nEnter Prefix Expression:");
          scanf("%s",prefix);    
          
          strrev(prefix);                    // Reverse of prefix supplied to create expression tree
          CreateExprTree(prefix);
          
          printf("\n\nEquivalent Expressions\n");
          printf("------------------------------------------------------\n\n");
                    
          printf("\n\nPrefix Expression:");
          pretrav(root);
          
          printf("\n\nInfix Expression:");
          intrav(root);
          
          printf("\n\nPostfix Expression:");
          postrav(root);
          
          getch();
}

void CreateExprTree(char *prefix)
{
          BTREE *p;
                         
          while(*prefix!='\0')
          {
                if(isdigits(*prefix))
                {
                              p = maketree(*prefix);
                              pushs(p);         
                }
                else                                // char is operator
                {
                              p = maketree(*prefix);                             
                              p->left = pops();
                              p->right = pops();
                              pushs(p);                                                    
                }                            
                
                prefix++;                                  
          }       
          
          root = pops();                // stack now contains address of root node omlu 
                                        // which is popped                                          
             
}

BTREE* maketree(char item)
{
     BTREE *p;  
     p = getnode();
     p->info = item;
     p->left = NULL;
     p->right = NULL;     
     return(p);
}

BTREE * getnode(void)
{
     BTREE *p; 
     p = (BTREE*)malloc(sizeof(BTREE));
     return(p);     
}

int isdigits(char temp)
{
	 if(temp >= '0' && temp <='9')
                return TRUE;
	 else
                return FALSE;    
}

void pushs(BTREE *item)
{        
     if(s.top==SIZE-1)
     {
                    printf("\n\nStack Overflow!");          
                    getch();
                    exit(1);
     }
     
     s.info[++s.top] = item; 
}   

BTREE* pops(void)
{
     if(s.top==-1)
     {
                    printf("\n\nStack Underflow!");
                    getch();
                    exit(1);                               
     }         
     
     return(s.info[s.top--]);
}

void pretrav(BTREE *p)
{
      if(p!=NULL)
      {
    	  printf(" %c, ",p->info);
    	  pretrav(p->left);
    	  pretrav(p->right);
      }
}

void intrav(BTREE *p)
{
      if(p!=NULL)
      {
          intrav(p->left);       
    	  printf(" %c, ",p->info);    	  
    	  intrav(p->right);
      }
}

void postrav(BTREE *p)
{
      if(p!=NULL)
      {    	  
    	  postrav(p->left);
    	  postrav(p->right);
    	  printf(" %c, ",p->info);
      }
}
