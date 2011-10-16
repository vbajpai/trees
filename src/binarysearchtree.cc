/* Binary Search Tree Implementation */

#include<iostream>
#include<conio.h>
using namespace std;

class Btree
{
   private:
   
   int info;
   Btree *left;
   Btree *right;   
   
   public:
   
   Btree(int e)                                 /* Constructor -  Creates Tree Node */
   {
          info = e;
          left = NULL;
          right = NULL;          
   }
   
   Btree * setleft(int e)
   {
          if(left !=NULL)
    			    cout<<"Invalid Insertion!";
	      else
    			    left = new Btree(e);
                              
          return(left);
   }

   Btree * setright(int e)
   {          
         if(right!=NULL)
  			    cout<<"Invalid Insertion!";
 		 else
                right = new Btree(e);
          
          return(right);
   }
   
   void insert(int e, Btree **p, Btree **q, bool *duplicate, bool *voidinsert)
   {		
		        *p = *q = this;
				 
			     while((*q)!=NULL)
			     {
    				*p = *q;
    				if(e == (*p)->info)
					{
					     *duplicate = true;	
    				     break;
					}
    				if(e > (*p)->info)
    					  *q = (*p)->right;
    				else
    					  *q = (*p)->left;
			     }
				 
			     if(*p==NULL)
                       *voidinsert = true;  
			     else
			     {
                     if(e>=(*p)->info)
			     	         *q = (*p)->setright(e);
                     else
			                 *q = (*p)->setleft(e);                
                 }		
   }   
   
   void intrav()
   {
          if(this!=NULL)
          {
              left->intrav();         
              cout<<info<<" ->";
              right->intrav();                         
          }
   } 
    
   void search(int e,Btree **pos,Btree **parent,bool *found,int *level)
   {
        if(this==NULL)
		{
			*pos = *parent = NULL; 
		}                      
        else
        {
    			     *pos = this;
    			     while(*pos!=NULL)
    			     {
        				 if((*pos)->info == e)
        				 {
        					 if(*pos==this)
        					            *parent = NULL;
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
	
   void deletenode(Btree **root, Btree *parent)
   {
		 if(this->left !=NULL && this->right!=NULL)
                this->delnodecaseB(root,parent);
         else
                this->delnodecaseA(root,parent);
   }
   
   void delnodecaseB(Btree **root, Btree *parent)
   {
         Btree *save,*child;
         
         save = this;
         child = right;
         
         while(child->left !=NULL)
         {
                 save = child;
                 child = child->left;                  
         }     
            
         child->delnodecaseA(root, save);
         
         if(parent!=NULL)
         {
                 if(parent->left == this)
                                 parent->left = child;
                 else
                                 parent->right = child;
         }
         else
                 *root = child;
                 
         child->left = left;
         child->right = right;
    }

   void delnodecaseA(Btree **root, Btree *parent)
   {
         Btree *child;
         
         if(left == NULL && right ==NULL)    
         {
                 if(parent == NULL)                       // ROOT NODE      
                     *root = NULL;
                 else
                 {                                               
                     if(parent->left == this)
                                     parent->left = NULL;    
                     else
                                     parent->right = NULL;
                 }
                                    
         }
         else
         {
                 if(left ==NULL || right == NULL)  
                 {                    
                              if(right == NULL)
                                             child = left;
                              else
                                             child = right;
                      if(parent!=NULL)
                      {                       
                              if(parent->left == this)
                                              parent->left = child;    
                              else
                                              parent->right = child;
                      }
                      else
                              *root=child;                                                                      
                 }    
         }          
   }   
};

int main()
{
	 /* -------------------------------------Declarations -------------------------------------*/
     int ch,e,level=0;
     bool found = false, duplicate = false, voidinsert = false;
     Btree *root=NULL;
     Btree *p = NULL,*q = NULL;
     Btree *pos = NULL,*parent = NULL,*child = NULL;	 
     /* ----------------------------------------------------- -------------------------------------*/
	 
     do
     {
	     system("cls");
	     cout<<"\n\nBinary Search Tree Implementation Using Dynamic Nodes\n\n";
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
			 
			 if(root==NULL)               /* Tree Empty */
				    root =  new Btree(e);
			 else
			        root->insert(e, &p, &q, &duplicate, &voidinsert);	
			 
			 if(duplicate == true)
			 {
					cout<<"\nDuplicate Entry!";
					getch();
			 }
					
			 if(voidinsert == true)
			 {
					cout<<"Void Insertion!";
					getch();
			 }
			 
			 break;
			 
		 case 2: /*Traversal*/
              
			 if(root==NULL)
				 cout<<"\nTree Empty!";
			 else
			 {			 
				 cout<<"\n\nInorder Traversal:";
				 root->intrav();				
			 }
			 getch();
			 break;
			 
		 case 3: /*Searching */
             
             cout<<"\nEnter Element To Search:";
			 cin>>e;
			 
			 root->search(e,&pos,&parent,&found,&level);
			 
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
             			 
			 root->search(e,&pos,&parent,&found,&level);
			 
             if(pos==NULL && parent ==NULL)
                          cout<<"\nTree Empty!"; 
             else
             {
    			 if(found==false)
                        cout<<"\n"<<e<<" Does Not Exist!";
                 else
                 {
						pos->deletenode(&root, parent);
                                                    
                        delete pos;
                        pos = NULL;     
                                                        
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
