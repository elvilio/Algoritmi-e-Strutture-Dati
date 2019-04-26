#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int PRIME = 1000000007;

typedef struct _list_t_ {
	int val;
	struct _list_t_ *next;
} list_t;

typedef struct _hash_table {
	int a, b;
	int n_bucket;
	list_t** table;
} hash_table;

int hash(hash_table* ht, int val) {
	return ((((ht->a*(long long)val+ht->b) % PRIME) + PRIME ) % PRIME) % ht->n_bucket;
}

hash_table* create_hash_table(int expected_size) {
	if (expected_size<1) return NULL;
	hash_table* root = malloc(sizeof(hash_table));
	root->table = malloc(sizeof(list_t *) * expected_size);
	root->a = (rand()%(RAND_MAX-1))+1;
	root->b = (rand()%(RAND_MAX-1))+1;

	int i;
	for(i=0; i<expected_size; i++) root->table[i] = NULL;

	root->n_bucket = expected_size;
	return root;
}

int find(hash_table* ht, int val) {
	int temp_pos = hash(ht, val);
	list_t* temp_list = ht->table[temp_pos];

	while(temp_list!=NULL){
		if(temp_list->val == val) return 1;
		temp_list = temp_list->next;
	}
	return 0;
}

void insert(hash_table* ht, int val) {
	int temp_pos = hash(ht, val);
	list_t* new_list = malloc(sizeof(list_t));
	new_list->val = val;
	new_list->next = NULL;

	list_t* current = ht->table[temp_pos];
	if (current == NULL){
		ht->table[temp_pos] = new_list;
		return;
	}
	if(current->val == val) return;
	while(current->next!=NULL){
		if (current->val == val) return;
		current=current->next;
	}
	if (current->val != val){
		new_list->next = current->next;
		current->next = new_list;
	}
}

void delete(hash_table* ht, int val) {
	int temp_pos = hash(ht, val);
	list_t* current_node = ht->table[temp_pos];
	if(current_node == NULL)
		return;
	if (current_node->val == val){
		if (current_node->next == NULL) {
			ht->table[temp_pos] = NULL;
			free(current_node);
			return;
		}
		ht->table[temp_pos] = current_node->next;
		free(current_node);
		return;
	}
	if(current_node->next == NULL)
		return;
	do {
		if(current_node->next->val == val){
			list_t* to_free = current_node->next;
			current_node->next = to_free->next;
			free(to_free);
			return;
		}
		current_node = current_node->next;
	} while(current_node->next != NULL);
}

void print_table(hash_table* ht, int expected_size){
	int i=0;
	for(;i<expected_size;i++) {
		list_t* temp_list = ht->table[i];
		printf("Position: %d%s", i, (temp_list==NULL)? "\n": "\t");
		while(temp_list!=NULL){
			if(temp_list->next == NULL){
				printf("%d\n", temp_list->val);
			}
			else{
				printf("%d - ", temp_list->val);
			}
			temp_list = temp_list->next;
		}
	}
}

int main() {
	srand(time(NULL));
	int o, i;
	scanf("%d", &o);
	hash_table* ht = create_hash_table(o);
	for (i=0; i<o; i++) {
		char op;
		int num;
		scanf(" %c%d", &op, &num);
		switch(op){
			case 'f':
				printf("%d\n", find(ht, num));
				break;
			case 'i':
				insert(ht, num);
				break;
			case 'd':
				delete(ht,num);
				break;
		}
		// print_table(ht,o);
	}
	return 0;
}