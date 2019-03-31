#include <stdio.h>
#include <stdlib.h>

int get_int();
long long maxsum(long long *x, int dim);

int main() {
	int n=0;
	n = get_int();
	int m = n;
	long long x[n];
	while(m-->0){
		x[m] = get_int();
	}
	printf("%lld\n", maxsum(x, n));
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

long long maxsum(long long *x, int dim){
	long long max = 0, this = 0;
	int j=0;
	for (;j<dim;j++) {
		this += x[j];
		if (this < 0) {
			this = 0;
		} else if (this > max) {
			max = this;
		}
	}
	return max;
}