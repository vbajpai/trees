/* Red Black Tree Implementation */

#include<iostream>
#include<conio.h>
using namespace std;

class RBtree;

class Btree
{
   protected:
   
   RBtree *left;
   RBtree *right;
   int info;    
   
   public:
   
   static RBtree *sentinal;
   static RBtree *root;
   
   Btree(int e)                                 /* Constructor -  Creates Tree Node */
   {
		  left = sentinal;
          right = sentinal;  	
          info = e;                  
   }
   
};

class RBtree: public Btree
{
   private:
   
   RBtree *parent;
   enum c {RED, BLACK}color;

   public:

   RBtree(int e, RBtree *p):Btree(e)
   {
		if(p!=NULL)				/* non-root */
		{
			parent = p;		
			color = RED;
		}
		else					/*sentinal*/
		{
			parent = sentinal;
			color = BLACK;
		}
   }
   
   void Insert(int e, bool *duplicate)
   {		
		        RBtree *p = sentinal, *q = this;
				 
			     while(q!=sentinal)
			     {
    				p = q;
    				if(e == p->info)
					{
					     *duplicate = true;	
    				     break;
					}
    				if(e > p->info)
    					  q = p->right;
    				else
    					  q = p->left;
			     }
				 
			     if(e>=p->info)
			     	       q = p->Setright(e);
                 else
			               q = p->Setleft(e);  
				
				 InsertFixup(q);
   }  
   
   RBtree * Setleft(int e)
   {
          if(left !=sentinal)
    			    cout<<"Invalid Insertion!";
	      else
    			    left = new RBtree(e, this);
                              
          return(left);
   }

   RBtree * Setright(int e)
   {          
         if(right!=sentinal)
  			    cout<<"Invalid Insertion!";
 		 else
                right = new RBtree(e, this);
          
          return(right);
   }
   
   void InsertFixup(RBtree *z)
   {
		RBtree *y = sentinal;
		
		if(this == z)				/* root note */
		{
			z->color = BLACK;
			return;
		}
		
		while(z!=root && (z->parent)->color == RED)
		{
			if(z->parent == ((z->parent)->parent)->left)
			{
				y = ((z->parent)->parent)->right;
				if(y->color == RED)
				{
					(z->parent)->color = BLACK;
					y->color = BLACK;
					((z->parent)->parent)->color = RED;
					z = (z->parent)->parent;
				}
				else
				{
					if(z == (z->parent)->right)
					{
						z = z->parent;
						LeftRotate(z);	
					}
					
					(z->parent)->color = BLACK;
					((z->parent)->parent)->color = RED;
					RightRotate((z->parent)->parent);
				}
			}
			else
			{
				y = ((z->parent)->parent)->left;
				if(y->color == RED)
				{
					(z->parent)->color = BLACK;
					y->color = BLACK;
					((z->parent)->parent)->color = RED;
					z = (z->parent)->parent;
				}
				else
				{
					if(z == (z->parent)->left)
					{
						z = z->parent;
						RightRotate(z);						
					}
					
					(z->parent)->color = BLACK;
					((z->parent)->parent)->color = RED;
					LeftRotate((z->parent)->parent);
				}
			}
		}
		
		root->color = BLACK;
   }
   
   void LeftRotate(RBtree *x)
   {
		RBtree *y = x->right;
		x->right = y ->left;
		(y->left)->parent = x;
		y->parent = x->parent;
		
		if(x->parent == sentinal)
			root = y;
		else
		{
			if(x == (x->parent)->left)
				(x->parent)->left = y;
			else
				(x->parent)->right = y;
		}	
		
		y->left = x;
		x->parent = y;
   }		
   
   void RightRotate(RBtree *y)
   {
		RBtree *x = y->left;
		y->left = x ->right;
		(x->right)->parent = y;
		x->parent = y->parent;
		
		if(y->parent == sentinal)
			root = x;
		else
		{
			if(y == (y->parent)->right)
				(y->parent)->right = x;
			else
				(y->parent)->left = x;
		}	
		
		x->right = y;
		y->parent = x;
   }
   
   void Search(int e,RBtree **pos,RBtree **parent,bool *found,int *level)
   {
        if(this==sentinal)
                 *pos = *parent = sentinal;      
        else
        {
    			     *pos = this;
    			     while(*pos!=sentinal)
    			     {
        				 if((*pos)->info == e)
        				 {
        					 if(*pos==this)
        					            *parent = sentinal;
                             *found = true;                         
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
   
   void Intrav()
   {
          if(this!=sentinal)
          {
              left->Intrav();         
              cout<<info<<"(";
			  if(color == RED)
				cout<<"RED";
			  else
				cout<<"BLACK";
			  cout<<")"<<" ->";
              right->Intrav();                         
          }
   }

   RBtree* Successor(RBtree *z)
   {
	    RBtree* child = z->right; 
         
        while(child->left !=sentinal)
                child = child->left;   
		return(child);
   }
   
   void DeleteFixup(RBtree *x)
   {
		RBtree *w=sentinal;
		while(x!=root && x->color == BLACK)
		{
			if(x==(x->parent)->left)
			{
				w = (x->parent)->right;
				if(w->color == RED)
				{
					w->color = BLACK;
					(x->parent)->color = RED;
					LeftRotate(x->parent);
					w = (x->parent)->right;
				}
				
				if((w->left)->color == BLACK && (w->right)->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if((w->right)->color == BLACK)
					{
						(w->left)->color = BLACK;
						w->color = RED;
						RightRotate(w);
						w = (x->parent)->right;
					}
					
					w->color = (x->parent)->color;
					(x->parent)->color = BLACK;
					(w->right)->color = BLACK;
					LeftRotate(x->parent);
					x = root;					
				}
			}
			else
			{
				w = (x->parent)->left;
				if(w->color == RED)
				{
					w->color = BLACK;
					(x->parent)->color = RED;
					RightRotate(x->parent);
					w = (x->parent)->left;
				}
				
				if((w->right)->color == BLACK && (w->left)->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if((w->left)->color == BLACK)
					{
						(w->right)->color = BLACK;
						w->color = RED;
						LeftRotate(w);
						w = (x->parent)->left;
					}
					
					w->color = (x->parent)->color;
					(x->parent)->color = BLACK;
					(w->left)->color = BLACK;
					RightRotate(x->parent);
					x = root;					
				}
			}
		}
		
		x->color = BLACK;
   }
   
   RBtree * DeleteNode()
   {
		RBtree *y=sentinal,*x=sentinal;
		
		if(left==sentinal || right==sentinal)
				y = this;
		else	
				y = Successor(this);
		
		if(y->left != sentinal)
				x = y->left;
		else
				x = y->right;
		
		x->parent = y->parent;
		
		if(y->parent == sentinal)
			root = x;
		else 
		{
			if( y == (y->parent)->left)
				(y->parent)->left = x;
			else
				(y->parent)->right = x;				
		}		
		
		if(y != this)
			info = y->info;
		
		if(y->color == BLACK)
			DeleteFixup(x);	
		
		return y;
   }	
   
     
};

/*----------------------------------Sentinal-----------------------------------------*/
RBtree * Btree::sentinal = NULL;
RBtree * Btree::root = NULL;
/*--------------------------------------------------------------------------------------*/

int main()
{
	 /* -------------------------------------Declarations -------------------------------------*/
     int ch,e,level=0;
     bool found = false, duplicate = false;     
     RBtree *pos = NULL,*parent = NULL;	
	 Btree::sentinal = new RBtree(0,NULL);	 
     /* ----------------------------------------------------- -------------------------------------*/
	 
     do
     {
	     system("cls");
	     cout<<"\n\nRed Black Tree Implementation Using Dynamic Nodes\n\n";
	     cout<<"1. Insert Elements\n";
	     cout<<"2. Traverse Tree\n";
	     cout<<"3. Search Element\n";
	     cout<<"4. Delete Elements\n";
	     cout<<"5. Exit\n";
	     cout<<"\nEnter Choice:";
	     cin>>ch;
	     
	     switch(ch)
	     {
		 case 1: /*Insertion */
			 cout<<"\nEnter Element:";
			 cin>>e;
			 
			 if(Btree::root == NULL)               /* Tree Empty  */
			 {
					Btree::root = new RBtree(e, Btree::sentinal);
					Btree::root->InsertFixup(Btree::root);					
			 }
			 else
			        Btree::root->Insert(e, &duplicate);	
			 
			 if(duplicate == true)
			 {
					cout<<"\nDuplicate Entry!";
					getch();
			 }
			 
			 break;
			 
		 case 2: /*Traversal*/
              
			 if(Btree::root==Btree::sentinal)
				 cout<<"\nTree Empty!";
			 else
			 {			 
				 cout<<"\n\nInorder Traversal:";
				 Btree::root->Intrav();				
			 }
			 getch();
			 break;
			 
		 case 3: /*Searching */
             
             cout<<"\nEnter Element To Search:";
			 cin>>e;
			 
			 Btree::root->Search(e,&pos,&parent,&found,&level);
			 
             if(pos==NULL && parent == NULL)
			                  cout<<"\nTree Empty!";
             else
             {             
                     if(found==true)
    				       cout<<"\n"<<e<<" found at level "<<level;
    			     else
    				       cout<<"\n"<<e<<" does not exist!";
             }
                 
             found = false;
             level = 0;
			  getch();
			 break;
		  
		 case 4: /*Deletion */
              
             cout<<"\nEnter Element To Delete:";
			 cin>>e;
             			 
			 Btree::root->Search(e,&pos,&parent,&found,&level);
			 
             if(pos==NULL && parent == NULL)
                          cout<<"\nTree Empty!"; 
             else
             {
    			 if(found==false)
                        cout<<"\n"<<e<<" Does Not Exist!";
                 else
                 {
						RBtree *x = pos->DeleteNode();
                                                    
                        delete x;
                        x = NULL;     
                                                        
                        cout<<"\n"<<e<<" Deleted Successfully!";               
                 }
             }
             found = false;
             level = 0;
             getch();
			 break;
			
		 case 5: /*Quit*/              
             exit(0);
		
		 default:
			 cout<<"\n\nInvalid Choice!";
			 getch();             
	     }
     
	 }while(true);
}
