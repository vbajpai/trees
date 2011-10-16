//Binary Search Algorithm Implementation//

#include<stdio.h>
#include<conio.h>
#define SIZE 50
#define TRUE 3
#define FALSE 4
#define DESC 2
#define ASC 1
int Bsearch(int *a,int ,int,int*,int);
main(void)
{
          int a[SIZE],i=0,index,num,order;
          int found=FALSE,item;
          char ch;
          system("cls");
          printf("\n\nBinary Search Algorithm Implementation");
          printf("\n--------------------------------------\n\n");
          printf("Number of Values to be Entered [<50] :");
          scanf("%d",&num);
          printf("\n1. Ascending:");
          printf("\n2. Descending:");
          printf("\n\nEnter Type of Ordering:");
          scanf("%d",&order);
          printf("\nEnter Values of Ordered Array\n\n");
          while(i<num)
          {
                    printf("Values for a[%d]:",i); 
                    scanf("%d",&a[i]);         
                    i++;            
          }
          do
          {                  
              printf("\n\nEnter Element to Search:");
              scanf("%d",&item);
              
              index = Bsearch(a,num,item,&found,order);
              if(found==TRUE)
                      printf("\n\n%d found at index:%d",item,index);
              else
                      printf("\n%d not found!",item);  
              found = FALSE;
              printf("\n\nExit(Y/N):");
              fflush(stdin);
              scanf("%c",&ch);              
          }while(ch=='N' || ch=='n');                              
}

int Bsearch(int *a,int n,int item,int *found,int order)
{
          
          int low = 0;
          int high = n-1;
          int mid = (high+low)/2;
          while(low<=high)
          {
                 if(*(a+mid)==item)
                 {
                        *found = TRUE;
                        return (mid);
                 }                               
                 if(*(a+mid)>item)  
                 {
                      if(order==ASC)              
                           high = mid - 1;                      
                      else if(order == DESC)
                           low = mid + 1;
                 }
                 else
                 {
                      if(order==ASC)
                           low =  mid + 1;
                      else if(order == DESC)
                           high = mid - 1;
                 }
                                   
                 mid = (low+high)/2;                                             
          }          
}
