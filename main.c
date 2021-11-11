#include <stdlib.h>
#include <unistd.h>
#include<stdio.h> 
 #include <string.h>
#include "functions.h"
#include "sort.h"
int w;
int num_re ;
extern int num_crit;
int main(int argc[],char* argv[]) 
{ 
/*      VARIABLES INITIALIZATION      */

struct LNode* head = NULL; 
FILE *fp;
int k1,k2;
int num;
int left_,right_;
struct list_intervals* new_interval,*temp_interval;
struct Node *t;

/*      CREATE A FILE WITH RANDOM INTERVAL      */							
const char* path_in = argv[1];
rand_(path_in,atoi(argv[4]));

/*      READ AND SORT INTERVALS ENDPOINTS      */
const char* path_endpoints = argv[2];
int thread_size = atoi(argv[3]);
sort_endpoints(path_in,path_endpoints,thread_size);
	
/*      CREATE THE BINARY TREE USING SORTED INTERVALS ENDPOINTS      */
fp = fopen(path_endpoints,"r");
fscanf(fp,"%d",&k2);
for(int i=0;i<k2;i++)
{
	fscanf(fp,"%d",&num);
	push(&head,num);
	w+=1;
}

/*Convert List to BST*/
struct Node *root = sortedListToBST(head); 
fclose(fp);
	/* ADD INTERVALS TO THE NODES*/
	fp = fopen(path_in,"r");
	fscanf(fp,"%d",&k2);
	int d=0;
	int* array = malloc(sizeof(int)*k2*2);
	for(int i=0;i<k2;i++)
	{
		fscanf(fp,"%d %d",&left_,&right_);
		array[2*i] = left_;
		array[2*i+1] = right_;

		t = lca(root, left_,right_);
		new_interval = malloc(sizeof(struct list_intervals));
		new_interval->index = i;
		w+=1;
		new_interval->next = NULL;
		
		if(t->num_intervals == 0)
			t->interval_first = new_interval;	
		else
		{				
			temp_interval = t->interval_first;
			while(temp_interval->next != NULL)
				temp_interval = temp_interval->next;
			
			temp_interval->next = new_interval;
			w+=1;
		}
		
		t->num_intervals +=1;
	}
	
	inner_tree_construct(root,array);
	
printf("\nNumber of writes for %d intervals",atoi(argv[4]));
printf("\nconstruction :%d",w);
	/*ADD NEW INTERVAL TO THE TREE*/
	int Num_new_nodes =atoi(argv[5]);
	for(int i=0;i<Num_new_nodes;i++)
	{
			w=0;
		int new_left = rand()%((int)(k2));
		int new_right = rand()%((int)(k2));
		
		if(new_left<new_right)
			interval_insertion(root,new_left,new_right,k2);
		else
			interval_insertion(root,new_right,new_left,k2);
	}

printf("\nupdate : %d",w);
 printf("\n\n");
    return 0; 
}
