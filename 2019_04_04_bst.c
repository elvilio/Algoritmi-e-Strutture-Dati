#include <stdio.h>
#include <stdlib.h>

struct tree_node {
	int val;
	int size;
	struct tree_node *left;
	struct tree_node *right;
};

int sz(struct tree_node* tree){
	return (tree==NULL) ? 0: tree->size;
}

struct tree_node* build_tree(int* data, int begin, int end){
	if (begin >= end) return NULL;
	struct tree_node* root=malloc(sizeof(struct tree_node));
	int middle = (begin+end)/2;
	root->size = end-begin;
	root->val = data[middle];
	root->left = build_tree(data, begin, middle);
	root->right = build_tree(data, middle+1, end);
	return root;
}

int find(struct tree_node* tree, int val){
	if (tree == NULL) return 0;
	if (tree->val == val) return 1;
	if (tree->val > val) return find(tree->left, val);
	return find(tree->right, val);
}

struct tree_node* insert(struct tree_node* tree, int val){
	if (tree==NULL){
		struct tree_node* root = malloc(sizeof(struct tree_node));
		root->val = val;
		root->size = 1;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	if (tree->val > val) tree->left = insert(tree->left, val);
	if (tree->val < val) tree->right = insert(tree->right, val);
	tree->size = sz(tree->left) + sz(tree->right) + 1;
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
		if (tree->left == NULL) {
			struct tree_node* temp = tree->right;
			if (temp != NULL)
				temp->size = sz(tree)-1;
			free(tree);
			return temp;
		}
		else if (tree->right == NULL) {
			struct tree_node* temp = tree->left;
			temp->size = sz(tree)-1;
			free(tree);
			return temp;
		}
		struct tree_node* temp = min_tree(tree->right);
		tree->val = temp->val;
		tree->right = delete(tree->right, temp->val);
		tree->size = tree->size-1;
	}
	tree->size = sz(tree->left) + sz(tree->right) + 1;
	return tree;
}

int count_(struct tree_node* tree, int begin, int end, int il, int ir){
	if (tree==NULL) return 0;
	if (il&&ir) return tree->size;
	if (end <= tree->val) return count_(tree->left, begin, end, il, ir);
	if (begin > tree->val) return count_(tree->right, begin, end, il, ir);

	int lc = count_(tree->left, begin, end, il, 1);
	int rc = count_(tree->right, begin, end, 1, ir);

	return 1+lc+rc;
}

int count(struct tree_node* tree, int begin, int end) {
	return count_(tree, begin, end, 0, 0);
}

int main() {
	int n, o, i;
	scanf("%d%d", &n, &o);
	int* data = malloc(sizeof(int)*n);
	for (i=0; i<n; i++) {
		scanf("%d", &data[i]);
	}
	struct tree_node* vals = build_tree(data, 0, n);
	for (i=0; i<o; i++) {
		char op;
		int num, num2;
		scanf(" %c%d", &op, &num);
		if (op == 'f') {
			printf("%d\n", find(vals, num));
		} else if (op == 'i') {
			vals = insert(vals, num);
		} else if (op == 'd') {
			vals = delete(vals, num);
		} else if (op == 'r') {
			scanf("%d", &num2);
			printf("%d\n", count(vals, num, num2));
		}
	}
	return 0;
}
