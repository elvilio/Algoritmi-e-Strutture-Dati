#include <stdio.h>
#include <stdlib.h>

struct tree_node {
	int val;
	int priority;
	int max_prior;
	struct tree_node *left;
	struct tree_node *right;
};

int prior_find(struct tree_node* tree){
	return (tree==NULL) ? 0 : tree->max_prior;
}

int max3(int a,int b,int c) {return (a>c)? (a>b)? a : b : (c>b)? c : b;}

void padding(char ch, int n) {
	int i;
	for(i = 0;i < n;i++)
		putchar(ch);
}

void structure(struct tree_node *root, int level) {
	int i;
	if(root == NULL) {
		padding('\t',level);
		puts("~");
	}
	else {
		structure(root->right, level+1);
		padding('\t', level);
		printf("%d\n", root->val);
		structure(root->left, level+1);
	}
}

struct tree_node* build_tree(int* data, int* prior, int begin, int end){
	if (begin >= end) return NULL;
	struct tree_node* root = malloc(sizeof(struct tree_node));
	int middle = (begin+end)/2;
	root->priority = prior[middle];
	root->val = data[middle];
	root->left = build_tree(data, prior, begin, middle);
	root->right = build_tree(data, prior, middle+1, end);
	root->max_prior = max3(prior_find(root->left), prior_find(root->right), root->priority);
	return root;
}

int find(struct tree_node* tree, int val){
	if (tree == NULL) return 0;
	if (tree->val == val) return 1;
	if (tree->val > val) return find(tree->left, val);
	return find(tree->right, val);
}

struct tree_node* insert(struct tree_node* tree, int val, int prior){
	if (tree==NULL){
		struct tree_node* root = malloc(sizeof(struct tree_node));
		root->val = val;
		root->priority = prior;
		root->left = NULL;
		root->right = NULL;
		root->max_prior = prior;
		return root;
	}
	if (tree->val > val) tree->left = insert(tree->left, val, prior);
	if (tree->val < val) tree->right = insert(tree->right, val, prior);
	if (tree->val == val) tree->priority = prior;
	tree->max_prior = max3(prior_find(tree->left), prior_find(tree->right), tree->priority);
	return tree;
}

struct tree_node* min_tree(struct tree_node* tree){
	if (tree == NULL) return tree;
	struct tree_node* current = tree;
	while(current->left != NULL){
		current = current->left;
	}
	return current;
}

struct tree_node* delete(struct tree_node* tree, int val){
	if (tree==NULL) return NULL;
	if (tree->val > val) tree->left = delete(tree->left, val);
	if (tree->val < val) tree->right = delete(tree->right, val);
	if (tree->val == val) {
		if (tree->right == NULL) {
			struct tree_node* temp = tree->left;
			free(tree);
			return temp;
		}
		if (tree->left == NULL){
			struct tree_node* temp = tree->right;
			free(tree);
			return temp;
		}
		struct tree_node* temp = min_tree(tree->right);
		tree->val = temp->val;
		tree->priority = temp->priority;
		tree->right = delete(tree->right,temp->val);
	}
	tree->max_prior = max3(prior_find(tree->left), prior_find(tree->right), tree->priority);
	return tree;
}

int count_(struct tree_node* tree, int begin, int end, int il, int ir){
	if (tree==NULL) return 0;
	if (il&&ir) return tree->max_prior;
	if (end <= tree->val) return count_(tree->left, begin, end, il, ir);
	if (begin > tree->val) return count_(tree->right, begin, end, il, ir);

	int lc = count_(tree->left, begin, end, il, 1);
	int rc = count_(tree->right, begin, end, 1, ir);

	return max3(lc,rc,tree->priority);
}

int count(struct tree_node* tree, int begin, int end) {
	return count_(tree, begin, end, 0, 0);
}


int main() {
	int n, o, i;
	scanf("%d%d", &n, &o);
	int* data = malloc(sizeof(int)*n);
	int* prior = malloc(sizeof(int)*n);
	for (i=0; i<n; i++) {
		scanf("%d%d", &data[i], &prior[i]);
	}
	struct tree_node* vals = build_tree(data, prior, 0, n);
	for (i=0; i<o; i++) {
		char op;
		int num, num2;
		scanf(" %c%d", &op, &num);
		switch(op){
			case('f'):
				printf("%d\n", find(vals, num));
				break;
			case('i'):
				scanf("%d", &num2);
				vals = insert(vals, num, num2);
				break;
			case('d'):
				vals = delete(vals, num);
				break;
			case('r'):
				scanf("%d", &num2);
				printf("%d\n", count(vals, num, num2));
				break;
		}
		// structure(vals, 0);
	}
	return 0;
}