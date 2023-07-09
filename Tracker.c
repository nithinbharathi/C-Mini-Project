#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

struct node{
	char expenses[50];
	int amount;
	struct node* next;
};


struct node2{
	struct node* node_addr;
};


struct node2 cache[50];
struct node* head = NULL;
int budget_amount,rem_amount,list_size=0,total =0;
char space;
		
    
		void display_details(){
				struct node* ptr = head;
				while(ptr != NULL){
					printf("\n\t%s\t%d",ptr->expenses,ptr->amount);
					ptr = ptr->next;
				}
				printf("\n\tBudget Amount: %d",budget_amount);
				printf("\n\tBalance Amount: %d\n",rem_amount);
			
		}
   
    void change_budget(){
    	int b;
    	printf("\n\tEnter The New Budget:");
    	scanf("%d%c",&b,&space);
    	budget_amount = b;
    	rem_amount = budget_amount - total;
    	total = 0;
    	display_details();
    }
    
    
    void calc(int amn,int flag){
      if(flag == 1){
              if(rem_amount == 0){
                rem_amount = budget_amount - amn;

          }else{
            rem_amount -= amn;
          }

      }else{
        rem_amount +=amn;

      }
    }
    
    
    struct node* create_node(int size){
      struct node *n;
      n = (struct node*)malloc(size*8);
      return n;
    }


		
		void remove_from_cache(int n,struct node* addr,int last){
				cache[n].node_addr = addr;
				int i;
				if(addr != NULL){
            for(i=n+1;i<last;i++){
              cache[i].node_addr = cache[i+1].node_addr;
            }	
			    }	
		}
		
		
		void add_expense(char arr[],int amn,int size){
        list_size++;
        total +=amn;
        struct node* n = create_node(size);
        n->amount = amn;
        n->next = NULL;
        int i;
        for(i =0;i<size;i++){
          n->expenses[i] = arr[i];
        }
        if(head == NULL){
          head = n;
        }else{
          struct node* ptr = head;
          while(ptr->next != NULL){
            ptr = ptr->next;
          }
          ptr->next = n;
        }
        cache[list_size].node_addr = n;
        calc(amn,1);
        display_details();
      }
	
  
		void remove_entry(){
          int n,count=1,last;
          last = list_size;
          printf("\n\tEnter the entry to be deleted: ");
          scanf("%d%c",&n,&space);
          struct node* ptr = head;
          struct node* temp  =NULL;
          if(n<= 0 || n>list_size){
            printf("\n\t Enter a valid Entry Number !!!");
          }
          if(head == NULL){
            printf("\n\t List Empty Cannot Remove !!!! ");
          }else if(n == 1){
            head = head->next;
            remove_from_cache(n,head,last);
            calc(ptr->amount,0);
            ptr->next = NULL;

          }else{
          /*	while(count<n-1){
              ptr = ptr->next;
              count++;
            }*/
              ptr = cache[n-1].node_addr;
              temp = ptr->next;
              calc(temp->amount,0);
              remove_from_cache(n,temp->next,last);
              ptr->next = temp->next;
              temp->next = NULL;		
          }
		list_size--;
		printf("\n\tRemoved Entry Successfully !!");
		display_details();	
	}
  
  
  
void  main() 
{ 
  int expense_amount;
  char expenses[50],choice;
  
  printf("\n\t\tWELOCOME\t\t\tTO\t\t\tmyBudget APP\n\n");
  printf("\n\t Press The Following:\n");
  printf("\t1-->ADD EXPENSES\n");
  printf("\t2-->REMOVE EXPENSES\n");
  printf("\t3-->SHOW RESULT\n");
  printf("\t4-->EDIT BUDGET AMOUNT\n");
  printf("--------------------------------------------------------------------------------------------------------------------\n");
  printf("\tPlease Enter Your Budget: ");
  scanf("%d%c",&budget_amount,&space);
  printf("\n\tEnter Your Expense: ");
  scanf("%[^\n]s",expenses);
  printf("\n\tEnter Your Expense Amount: ");
  scanf("%d%c",&expense_amount,&space);
  int size = sizeof(expenses)/sizeof(expenses[0]);
  add_expense(expenses,expense_amount,size);
  printf("\n\tDo You Wish To Continue y/n ?");
  scanf("%c%c",&choice,&space);
  
  if(choice == 'y'){
      printf("\n\tPress c To Change Budget Amount: ");
      printf("\n\tPress r To Remove An Entry: ");
      printf("\n\tPress y To Continue Adding Expenses: ");
      printf("\n\tPress e To End: ");
      scanf("%c%c",&choice,&space);
      
  		  while(choice != 'e' ){
  			    if(choice == 'c'){
			  		      change_budget();
			            printf("\n\tPress c To Change Budget Amount.");
			  	        printf("\n\tPress r To Remove An Entry.");
					        printf("\n\tPress y To Continue Adding.");
					        printf("\n\tPress e To End: ");
					        scanf("%c%c",&choice,&space);
			      }
			  if(choice == 'y'){
			  	    printf("\n\tExpense:");
           		scanf("%[^\n]s",expenses);
           		printf("\n\tExpense Amount:");
				      scanf("%d%c",&expense_amount,&space);
				      size = sizeof(expenses)/sizeof(expenses[0]);
				      add_expense(expenses,expense_amount,size);
				      printf("\n\tPress c To Change Budget Amount.");
			  	    printf("\n\tPress r To Remove An Entry.");
				      printf("\n\tPress y To Continue Adding.");
			        printf("\n\tPress e To End: ");
				      scanf("%c%c",&choice,&space);
              
			  }if(choice == 'r'){
			  	    remove_entry();
			  	    printf("\n\tPress c To Change Budget Amount.");
			  	    printf("\n\tPress r To Remove An Entry.");
				      printf("\n\tPress y To Continue Adding.");
			        printf("\n\tPress e To End: ");
				      scanf("%c%c",&choice,&space);
			  } 
  		}
  		display_details();
  		free(head);
 
  }else{
  	display_details();
  	free(head);
  }
   
}
