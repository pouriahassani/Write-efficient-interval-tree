#include <stdlib.h>
#include <unistd.h>
#include<stdio.h> 
#include "functions.h"
#include <string.h>
#include<math.h>
/* Link list node */  
int alpha = 16;
int num_re =0;
int num_crit=0;
/* This function counts the number of nodes in Linked List and then calls 
   sortedListToBSTRecur() to construct BST */
struct Node* sortedListToBST(struct LNode *head) 
{ 
    /*Count the number of nodes in Linked List */
    int n = countLNodes(head); 
  
    /* Construct BST */
    return sortedListToBSTRecur(&head, n); 
} 
  
/* The main function that constructs balanced BST and returns root of it. 
       head_ref -->  Pointer to pointer to head node of linked list 
       n  --> No. of nodes in Linked List */
struct Node* sortedListToBSTRecur(struct LNode **head_ref, int n) 
{ 
    /* Base Case */
    if (n <= 0) 
        return NULL; 
  
    /* Recursively construct the left subtree */
    struct Node *left = sortedListToBSTRecur(head_ref, n/2); 
  
    /* Allocate memory for root, and link the above constructed left  
       subtree with root */
    struct Node *root = newNode((*head_ref)->data); 
    root->left = left; 
  
    /* Change head pointer of Linked List for parent recursive calls */
    *head_ref = (*head_ref)->next; 
  
    /* Recursively construct the right subtree and link it with root  
      The number of nodes in right subtree  is total nodes - nodes in  
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = sortedListToBSTRecur(head_ref, n-n/2-1); 
  
    return root; 
} 
/* UTILITY FUNCTIONS */
  
/* A utility function that returns count of nodes in a given Linked List */
int countLNodes(struct LNode *head) 
{ 
    int count = 0; 
    struct LNode *temp = head; 
    while(temp) 
    { 
        temp = temp->next; 
        count++; 
    } 
    return count; 
} 
  
/* Function to insert a node at the beginging of the linked list */
void push(struct LNode** head_ref, int new_data) 
{ 
    /* allocate node */
    struct LNode* new_node = 
        (struct LNode*) malloc(sizeof(struct LNode)); 
    /* put in the data  */
    new_node->data  = new_data; 
  
    /* link the old list off the new node */
    new_node->next = (*head_ref); 
  
    /* move the head to point to the new node */
    (*head_ref)    = new_node; 
} 
  
/* Function to print nodes in a given linked list */
void printList(struct LNode *node) 
{ 
    while(node!=NULL) 
    { 
        printf("%d ", node->data); 
        node = node->next; 
    } 
} 
  
/* Helper function that allocates a new node with the 
   given data and NULL left and right pointers. */
struct Node* newNode(int data) 
{ 
    struct Node* node = (struct Node*) 
                         malloc(sizeof(struct Node)); 
    node->data = data; 
    node->left = NULL; 
    node->right = NULL; 
	node->interval_first = NULL;
	node->num_intervals=0;
	w+=1;
    return node; 
} 

struct inner_BST_node* BST_newNode(int data,int index) 
{ 
    struct inner_BST_node* node = (struct inner_BST_node*) 
                         malloc(sizeof(struct inner_BST_node)); 
    node->data = data; 
	node->index = index; 
    node->left = NULL; 
    node->right = NULL; 
    return node; 
} 


/* A utility function to print preorder traversal of BST */
void preOrder(struct Node* node) 
{ 
    if (node == NULL) 
        return; 
    printf("%d ", node->data); 
    preOrder(node->left); 
    preOrder(node->right); 
} 
void BST_preOrder(struct list_intervals* node) 
{ 
    if (node == NULL) 
        return; 
    printf("\tindex %d ",node->data); 
    BST_preOrder(node->next); 
} 


void BST_print(struct inner_BST_node* node) 
{ 
    if (node == NULL) 
        return; 
	 BST_print(node->left);
    printf("\t data%d weight %d",node->data,node->weight); 
	BST_print(node->right); 
} 


////////////////////////////////////////////////////////////////////////////////////////////////*
/*                          LCA FUNCTIONS                                      */
/* Function to find LCA of n1 and n2. The function assumes that both 
n1 and n2 are present in BST */
struct Node *lca(struct Node* root, int n1, int n2) 
{ 
	if (root == NULL) return NULL; 

	// If both n1 and n2 are smaller than root, then LCA lies in left 
	if (root->data > n1 && root->data > n2) 
		return lca(root->left, n1, n2); 

	// If both n1 and n2 are greater than root, then LCA lies in right 
	if (root->data < n1 && root->data < n2) 
		return lca(root->right, n1, n2); 

	w+=1;
	return root; 
} 



///////////////////////////////////////////////////////////////////////////////////////////////////
				/*       Constuction of inner trees        */

void inner_tree_construct(struct Node* root,int * array)
{
	if(root == NULL)
		return;
	
	inner_tree_construct(root->left,array);
	if(root->num_intervals != 0)
	{
		root->left_sorted_index = malloc(sizeof(int) * root->num_intervals);
		root->left_sorted_endpoint = malloc(sizeof(int) * root->num_intervals);
		root->right_sorted_index = malloc(sizeof(int) * root->num_intervals);
		root->right_sorted_endpoint = malloc(sizeof(int) * root->num_intervals);
		struct list_intervals* intervals = root->interval_first;

		for(int i=0;i<root->num_intervals;i++)
		{
			root->left_sorted_index[i] = intervals->index;
			root->left_sorted_endpoint[i] = array[ intervals->index*2];
			root->right_sorted_index[i] = intervals->index;
			root->right_sorted_endpoint[i] = array[ intervals->index*2+1];
			intervals = intervals->next;
		}
		radixsort(root->left_sorted_endpoint,root->num_intervals,root->left_sorted_index);
		radixsort(root->right_sorted_endpoint,root->num_intervals,root->right_sorted_index);
		root->interval_left_endpoint = link_list_construct(root->left_sorted_index,root->left_sorted_endpoint,root->num_intervals,root->num_intervals);
		root->interval_right_endpoint = link_list_construct(root->right_sorted_index,root->right_sorted_endpoint,root->num_intervals,root->num_intervals);	
		root->left_inner_BST_tree = inner_BST_tree_construction(root->interval_left_endpoint,root->num_intervals);
		root->right_inner_BST_tree = inner_BST_tree_construction(root->interval_right_endpoint,root->num_intervals);
	 }

	 if(root->right_inner_BST_tree !=NULL)
		root->right_inner_BST_tree->critical = 1;

	 if(root->left_inner_BST_tree !=NULL)
		root->left_inner_BST_tree->critical = 1; 

	set_weights(root->right_inner_BST_tree);
	set_weights(root->left_inner_BST_tree);
	inner_tree_construct(root->right,array);

}

/*   LINK LIST CREATION OF INDEXES AND DATA*/
struct list_intervals* link_list_construct(int *arr_ind,int* arr_data,int n,int i)
{
	if(i==0)
		return NULL;
	
	struct list_intervals* node = malloc(sizeof(struct list_intervals));
	node->index = arr_ind[n-i];
	node->data = arr_data[n-i];
	node->next = link_list_construct(arr_ind,arr_data,n,i-1);
	return node;
}


struct inner_BST_node* inner_BST_tree_construction(struct list_intervals *head,int n) 
{ 
    /*Count the number of nodes in Linked List */  
    /* Construct BST */
    return inner_BST_tree_construction_recur(&head, n); 
} 

struct inner_BST_node*  inner_BST_tree_construction_recur (struct list_intervals** node,int n)
{
	    /* Base Case */
    if (n <= 0) 
        return NULL; 
  
    /* Recursively construct the left subtree */
    struct inner_BST_node *left = inner_BST_tree_construction_recur(node, n/2); 
  
    /* Allocate memory for root, and link the above constructed left  
       subtree with root */
    struct inner_BST_node *root = BST_newNode((*node)->data,(*node)->index); 
    root->left = left; 
  
    /* Change head pointer of Linked List for parent re cursive calls */
    *node = (*node)->next; 
  
    /* Recursively construct the right subtree and link it with root  
      The number of nodes in right subtree  is total nodes - nodes in  
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = inner_BST_tree_construction_recur(node, n-n/2-1); 
  
    return root; 
}


void set_weights(struct inner_BST_node* node) 
{ 
	if(node==NULL)
		return;
	w+=1;
	
	 set_weights(node->left);
	 set_weights(node->right);
	 
    if (node->left == NULL && node->right == NULL)
	{
		node->weight =2;
		node->init_weight = 2;
	}
	
	if(node->left == NULL && node->right != NULL)
	{
		node->weight =node->right->weight +1;
		node->init_weight = node->weight;	
	}
	
	if(node->left != NULL && node->right == NULL)
	{
		node->weight =node->left->weight +1;
		node->init_weight = node->weight;
	}
		
	if(node->left != NULL && node->right != NULL)
	{
		node->weight =node->right->weight +node->left->weight;
		node->init_weight = node->weight;		
	}

	
	int left_bound =(int) log((node->weight +2)/4) / log(alpha);
	int right_bound =(int) log((node->weight +1)/2) / log(alpha);
	
	node->critical = 0;
	for(int i=left_bound;i<=right_bound;i++)
	{
		if(node->weight>=2*alpha^i -1 && node->weight <= 4*alpha^i - 2 && i>=0)
		{
			node->critical = 1;
			num_crit+=1;
			break;
		}
	}
} 
/////////////////////////////////////////////////////////////////////////////////////////////////////
            	/*ADD NEW INTERVAL TO THE TREE*/
void interval_insertion(struct Node* root,int left,int right,int n)
{
	struct list_intervals* list;
	if(left <= root->data && right >=root->data)
	{
		insert_into_inner_tree(root->left_inner_BST_tree ,left,n);
		insert_into_inner_tree(root->right_inner_BST_tree ,right,n);
		rebalancing(root->left_inner_BST_tree,left);
		rebalancing(root->left_inner_BST_tree,right);
		return;
	}
	
	if(right < root->data)
	{
		interval_insertion(root->left,left,right,n);
		return;
	}
	
		if(left > root->data)
	{
		interval_insertion(root->right,left,right,n);
		return;
	}
	
}
/*				INSERT INTO INNER TREE                      */
void insert_into_inner_tree(struct inner_BST_node* root, int new_interval,int n)
{
	if(root == NULL)
		return;
	
	if(new_interval <= root->data && root->left != NULL)
	{
		if(root->critical == 1)
		{
			root->weight +=1;
			w+=1;
		}
		insert_into_inner_tree(root->left,new_interval,n);
	}
	
	if(new_interval > root->data && root->right != NULL)
	{
		if(root->critical == 1)
		{
			root->weight +=1;
			w+=1;
		}
		insert_into_inner_tree(root->right,new_interval,n);
	}
	
	if(new_interval <= root->data && root->left == NULL)
	{
		root->left  = BST_newNode(new_interval,n);
		root->left->critical = 1;
		root->left->weight = 2;
		if(root->critical == 1)
		{
			root->weight +=1;
			w+=1;
		}
	}

	if(new_interval > root->data && root->right == NULL)
	{
		root->right = BST_newNode(new_interval,n);
		if(root->critical == 1)
		{
			root->weight +=1;
			w+=1;
		}
		root->right->critical = 1;
		root->right->weight = 2;
	}
	

}

/*        REBALANCE FUNCTION AFTER ADDING NEW INTERVAL         */
void rebalancing(struct inner_BST_node* root,int value)
{
	if(root == NULL)
		return;
	if(root->weight >= 2* root->init_weight && root->critical == 1)
	{
		num_re+=1;
		struct list_intervals* list = NULL;
		list = tree_to_link_list(root);
		root = inner_tree_reconstruct(root,list);
	set_weights(root);
	return;
	}
	
	if(value <= root->data)
		rebalancing(root->left,value);
	else
		rebalancing(root->right,value);
}

/*            RECONSTRUCTION OF THE INNER TREE     */
struct inner_BST_node* inner_tree_reconstruct(struct inner_BST_node* root,struct list_intervals* list)
{
	root = inner_BST_tree_construction(list,root->weight - 1);
	set_weights(root);
	return root;
}


/* PRINT THE TREE TO CHECK CORRECTNESS*/
void print_whole_trees(struct Node* root)
{
	if(root == NULL)
		return;
	print_whole_trees(root->left);
	print_whole_trees(root->right);
}


/*         CHANGE A BINARY TREE INTO A LINK LIST      */
struct list_intervals* tree_to_link_list(struct inner_BST_node* root)
{
	w+=1;
    struct list_intervals *list1 = (root->left) ? tree_to_link_list(root->left) : NULL;
    struct list_intervals *list2 = (root->right) ? tree_to_link_list(root->right) : NULL;
   	struct list_intervals*list3 = malloc(sizeof(struct list_intervals));
	list3->data = root->data;
	list3->index = root->index;
	list3->next = NULL;
    // The "middle" list3 cannot be NULL; append list2 to list3
    list3->next = list2; // If list2 is NULL, it's OK
	
    if (!list1)
		return list3; // Nothing to prepend

  	struct list_intervals* last = list1;

    while (last->next) last=last->next; // Go to the end of list1
		last->next = list3; // Append list3+list2 to the end of list1
    
	return list1;
}


/*                        RADIX SORT FUNCTIONS                        */


// A utility function to get maximum value in arr[] 
int getMax(int arr[], int n) 
{ 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
} 
  
// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
void countSort(int arr[], int n, int exp,int* index) 
{ 
    int output[n]; // output array 
	int ind[n];
    int i, count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    // Build the output array 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
		ind[count[ (arr[i]/exp)%10 ] - 1] = index[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
	{
	        arr[i] = output[i]; 
			index[i] = ind[i];
	}
} 
  
// The main function to that sorts arr[] of size n using  
// Radix Sort 
void radixsort(int arr[], int n,int* index) 
{ 
    // Find the maximum number to know number of digits 
    int m = getMax(arr, n); 
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m/exp > 0; exp *= 10) 
        countSort(arr, n, exp,index); 
} 

