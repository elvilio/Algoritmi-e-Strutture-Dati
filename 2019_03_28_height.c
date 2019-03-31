#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node_def {
	int id;
	struct tree_node_def* left;
	struct tree_node_def* right;
} tree_node;


int max(int x, int y){
	return (x<y)? y: x;
}


int get_int();
tree_node* build_tree(int root, int* left, int* right);
void free_tree(tree_node* tree);
int height(tree_node* tree);



int main() {
	int n = get_int(), root = get_int();
	int* left = malloc(sizeof(int)*n);
	int* right = malloc(sizeof(int)*n);
	int i;

	for (i = 0; i < n; ++i)
	{
		int id = get_int(), l=get_int(), r=get_int();
		left[id] = l;
		right[id] = r;
	}

	tree_node* tree = build_tree(root, left, right);
	printf("%d\n", height(tree));
	free_tree(tree);
	return 0;
}

int get_int() {
	int n = 0;
	int negative = 0;
	int c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	if (c == '-') {
		negative = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		n = 10 * n + c - '0';
		c = getchar();
	}
	return negative ? -n : n;
}

tree_node* build_tree(int root, int* left, int* right){
	if (root == -1) return NULL;
	tree_node* ret = malloc(sizeof(*ret));
	ret->id = root;
	ret->left = build_tree(left[root], left, right);
	ret->right = build_tree(right[root], left, right);
	return ret;
}

int height(tree_node* tree){
	if(tree == NULL) return -1;
	return max(height(tree->left)+1, height(tree->right)+1);
}

void free_tree(tree_node* tree){
	if (tree == NULL) return;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}