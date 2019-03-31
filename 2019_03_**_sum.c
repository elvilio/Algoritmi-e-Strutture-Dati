#include <stdio.h>
#include <stdlib.h>

int get_int();
int summ(int *x, int dim);

int main() {
	int n=0;
	n = get_int();
	int x[n];
	int i=0;
	while(i++<n){
		x[i] = get_int();
	}
	printf("%d\n", summ(x, n));
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


int summ(int *x, int dim){
	int ret=0;
	do{
		ret+=x[dim];
	}while(--dim>0);
	return ret;
}