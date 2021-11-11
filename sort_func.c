#include <stdlib.h>
#include <unistd.h>
#include<stdio.h>
#include<omp.h>
#include "sort.h"
int w = 0;

void rand_(const char* path,int k)
{
	
FILE* fp;
int a;
int* arr = malloc(sizeof(int)*k);
int t=0;
int flag =0;
int b;
fp = fopen(path,"w");
fprintf(fp,"%d\n",k);
for(int i=0;i<k;i++)
{
	a = rand()%((int)(k));
	b = rand()%((int)(k));
	if(a<b)
		fprintf(fp,"%d %d\n",a,b);
	else
		fprintf(fp,"%d %d\n",b,a);
}		
fclose(fp);
}
int read_(struct binary_tree* ptr,int* out)
{
	static int i = 0;
	if(ptr == NULL)
	{
		return 0;
	}
	read_(ptr->right,out);
//	printf("\n%d",ptr->key);
	out[i] = ptr->key;
	i+=1;	
	read_(ptr->left,out);
	return i;
}

void sort_endpoints(const char* path_in,const char* path_out,int thread_size){
FILE *fp;
int ini;
float n;
int dir;
int tid;
int k;
struct binary_tree* root=NULL;
struct binary_tree* p=NULL;
struct binary_tree* parent=NULL;
struct binary_tree* node=NULL;
omp_set_num_threads(thread_size);

/*read data from input file*/
fp = fopen(path_in,"r");
fscanf(fp,"%d",&k);

int *in  = (int*)malloc(sizeof(int)*k*2);
int *out = (int*)malloc(sizeof(int)*k*2);

for(int i=0;i<k;i++)
{
	fscanf(fp,"%d %d",&in[2*i],&in[2*i+1]);
}



/*create the tree*/
root = malloc(sizeof(struct binary_tree));
root->key = in[0];
root->left=NULL;
root->right =NULL;
int t=0;
#pragma omp parallel for shared(root,in) firstprivate(t,n,p,parent,dir)

 for(int i=1;i<2*k;i++)
{
	tid = omp_get_thread_num();
	p = root;
	n = in[i];
	node = malloc(sizeof(struct binary_tree));
	node->left=NULL;
	node->right = NULL;
	node->thread_num=tid;
	node->key = n;
	while(1)
	{	
		if(p == NULL)
		{			
				if(dir ==0)				
				{
					if( parent->left == NULL)
						parent->left = node;
				}					
				if(dir ==1)
				{
					if(parent->right == NULL)
						parent->right = node;
				}					
			if(dir ==0)
			{
				if(parent->left->thread_num == tid)
				{
					w+=1;
					break;
				}
				
			}
			if(dir ==1)	
			{
					w+=1;
					break;
			}
			p = parent;
			t+=1;
		}
		
		if(n < p->key)
		{
			parent = p;
			p = p->left;
			dir = 0;
		}
		else
		{
			if(p->key == n)
				break;
			parent = p;
			p = p->right;
			dir =1;
		}
	}
}

k=read_(root,out); 
fclose(fp);
fp = fopen(path_out,"w");
fprintf(fp,"%d\n",k);
for(int i=0;i<k;i++)
	fprintf(fp,"%d\n",out[i]);
fclose(fp);
}
