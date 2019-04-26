#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define ARR_LEN(ARR) (sizeof ARR / sizeof *ARR)

int get_int();
void radix_sort(int *x, const size_t n);
static void rad_sort_u(unsigned *from, unsigned *to, unsigned bit);
static void swap(unsigned *a, unsigned *b);

int main() {
	size_t n=0;
	n = get_int();
	size_t m = n;
	int x[n];
	while(m-->0){
		x[m] = get_int();
	}
	radix_sort(x, n);

	m=0;
	while(m<n){
		(n-m!=1)? printf("%d ", x[m]): printf("%d\n", x[m]);
		m++;
	}
	return 0;
}

void radix_sort(int *a, const size_t n){
	size_t i;
	unsigned *x = (unsigned*) a;
	for (i = 0; i < n; i++)
		x[i] ^= INT_MIN;
	rad_sort_u(x, x + n, INT_MIN);
	for (i = 0; i < n; i++)
        x[i] ^= INT_MIN;
}

static void rad_sort_u(unsigned *from, unsigned *to, unsigned bit){
	if (!bit || to < from + 1) return;
	unsigned *ll = from, *rr = to - 1;
	for (;;) {
		while (ll < rr && !(*ll & bit)) ll++;
		while (ll < rr &&  (*rr & bit)) rr--;
		if (ll >= rr) break;
		swap(ll, rr);
	}

	if (!(bit & *ll) && ll < to) ll++;
	bit >>= 1;
 
	rad_sort_u(from, ll, bit);
	rad_sort_u(ll, to, bit);
}

static void swap(unsigned *a, unsigned *b) {
    unsigned tmp = *a;
    *a = *b;
    *b = tmp;
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