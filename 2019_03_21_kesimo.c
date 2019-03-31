#include <stdio.h>
#include <stdlib.h>

int nextInt();
int quicky(int *v, int len, int k);


int main()
{
	int N, NN, K;
	scanf("%d", &N);
	NN = N;
	scanf("%d", &K);
	int v[N];
	while(N-->0){
		v[N] = nextInt();
	}
	printf("%d\n", quicky(v, NN, K));
	return 0;
}

int quicky(int *v, int len, int k){
	#define SWAP(a, b) { tmp = v[a]; v[a] = v[b]; v[b] = tmp; }
	int i, st, tmp;
 
	for (st = i = 0; i < len - 1; i++) {
		if (v[i] > v[len-1]) continue;
		SWAP(i, st);
		st++;
	}
 
	SWAP(len-1, st);
 
	return k == st	?v[st] :st > k ? quicky(v, st, k) : quicky(v + st, len - st, k - st);
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
