#include <stdio.h>
#include <stdlib.h>

typedef struct _list {
	int val;
	struct _list *next;
} list;

typedef struct _table {
	int dim;
	list** vec_list;
} table;

table* create_table(int size);
void add_to_table(table* data, int from, int to);
void print_graph(table* data);
int nextInt();

int main(void) {
	int m;
	table* data=create_table(nextInt());
	m = nextInt();

	while(m-->0){
		add_to_table(data, nextInt(), nextInt());
	}

	print_graph(data);

	return 0;
}

table* create_table(int size){
	if (size<1) return NULL;
	table* new_table = malloc(sizeof(table));
	new_table->vec_list = malloc(sizeof(list)*size);
	new_table->dim = size;
	int i;
	for(i=0; i<size; i++) new_table->vec_list[i] = NULL;
	return new_table;
}

void add_to_table(table* data, int from, int to){
	if(data->vec_list[from]==NULL){
		data->vec_list[from] = malloc(sizeof(list));
		data->vec_list[from]->val = to;
		data->vec_list[from]->next = NULL;
		return;
	}

	if (data->vec_list[from]->val>to) {
		list* temp_2 = data->vec_list[from];
		data->vec_list[from] = malloc(sizeof(list));
		data->vec_list[from]->val = to;
		data->vec_list[from]->next = temp_2;
		return;
	}

	list* temp = data->vec_list[from];
	while(temp->next!=NULL){
		if (temp->next->val>to){
			list* temp_2 = temp->next;
			temp->next = malloc(sizeof(list));
			temp->next->val = to;
			temp->next->next = temp_2;
			return;
		}
		temp = temp->next;
	}
	temp->next = malloc(sizeof(list));
	temp->next->val = to;
	temp->next->next = NULL;
}

void print_graph(table* data){
	int i=0;
	for(;i<data->dim;i++){
		list* temp=data->vec_list[i];
		while(temp!=NULL){
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("\n");
	}
}

int nextInt() {
	int n = 0;
	int negative = 0;
	int c = getchar();
	while ((c < '0' || c > '9') && c != '-')
		c = getchar();
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