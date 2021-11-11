#include<math.h>
struct LNode 
{ 
    int data; 
    struct LNode* next; 
}; 
extern int w;
extern int num_re;
extern int  num_crit;
struct Node 
{ 
    int data; 
    struct Node* left, *right; 
	struct list_intervals* interval_left_endpoint;
	struct list_intervals* interval_right_endpoint;
	struct list_intervals* interval_first;
	int num_intervals;
	int* left_sorted_index;
	int* left_sorted_endpoint;
	int* right_sorted_index;
	int* right_sorted_endpoint;
	struct inner_BST_node* left_inner_BST_tree;
	struct inner_BST_node* right_inner_BST_tree;
};

struct list_intervals{
	int index;
	int data;
	struct list_intervals* next;
};

struct subset 
{ 
    int parent, rank, ancestor, child, sibling, color; 
}; 
  
struct inner_BST_node
{
	int data;
	int index;
	struct inner_BST_node* left;
	struct inner_BST_node* right;
	int weight;
	int init_weight;
	int critical;
};

struct Query 
{ 
    int L, R; 
}; 

/*     ALPHA VALUE     */

struct Node* sortedListToBST(struct LNode *head) ;
struct Node* sortedListToBSTRecur(struct LNode **head_ref, int n) ;
int countLNodes(struct LNode *head) ;
void push(struct LNode** head_ref, int new_data) ;
void printList(struct LNode *node) ;
struct Node* newNode(int data) ;
void preOrder(struct Node* node); 

////////////////////////////////////////////////////////////////////////////////////////////////
/*                         LCA FUNCTIONS                                  */

struct Node* newNode(int data);
struct Node *lca(struct Node* root, int n1, int n2) ;


///////////////////////////////////////////////////////////////////////////////////////////////////
				/*       Constuction of inner trees        */
void inner_tree_construct(struct Node *root,int* array);
struct inner_BST_node*  inner_BST_tree_construction (struct list_intervals*,int n);
struct inner_BST_node*  inner_BST_tree_construction_recur (struct list_intervals**,int n);
struct inner_BST_node* BST_newNode(int ,int) ;
struct list_intervals *link_list_construct(int* ,int*,int,int);
void BST_preOrder(struct list_intervals* node) ;
void BST_print(struct inner_BST_node* node) ;
void set_weights(struct inner_BST_node* node) ;
void insert_into_inner_tree(struct inner_BST_node* root, int new_interval,int n);
void interval_insertion(struct Node* root,int left,int right,int n);
void print_whole_trees(struct Node* root);
struct list_intervals* tree_to_link_list(struct inner_BST_node* node);
struct inner_BST_node* inner_tree_reconstruct(struct inner_BST_node* root,struct list_intervals* list);
void rebalancing(struct inner_BST_node* root,int value);


/*                   RADIX SORT FUNCTIONS                            */

void countSort(int arr[], int n, int exp,int* index) ;
void radixsort(int arr[], int n,int* index) ;


/////////////////////////////////////////////////////////////////////////////////////////////////////
            	/*ADD NEW INTERVAL TO THE TREE*/
void sort_func(const char* path);
