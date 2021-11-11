struct binary_tree{
	int key;
	struct binary_tree *left ;
	struct binary_tree *right;
	int thread_num;
};


void sort_endpoints(const char*,const char*,int thread_size);
int read_(struct binary_tree* ptr,int* out);

void rand_(const char*,int k);