#include <stdio.h>
#include <stdlib.h>

int nextInt();
long long inversions(int *v, int len);
long long merge_inv(int *v, int* temp, int left, int right);
long long merge(int* v, int* temp, int left, int mid, int right);

int main()
{
	int N, NN;
	scanf("%d", &N);
	NN = N;
	int v[N];
	while(N-->0){
		v[NN-N-1] = nextInt();
	}

	printf("%lld\n", inversions(v, NN));
	return 0;
}

long long inversions(int *v, int len){
	int* temp = (int*)malloc(sizeof(int) * len);
	return merge_inv(v, temp, 0, len-1);
}

long long merge_inv(int *v, int* temp, int left, int right){
	int mid;
	long long inv_count=0;
	if(right>left){
		mid = (right + left)/2;
		inv_count = merge_inv(v, temp, left, mid);
		inv_count += merge_inv(v, temp, mid+1, right);

		inv_count += merge(v, temp, left, mid+1, right);
	}

	return(inv_count);
}

long long merge(int* v, int* temp, int left, int mid, int right){
	int i = left, j = mid, k = left;
	long long inv_count=0;

	while((i <= mid - 1) && (j <= right))
		temp[k++] = (v[i] <= v[j] ? v[i++] : (inv_count = inv_count + (mid - i), v[j++]));

	while (i <= mid - 1)
		temp[k++] = v[i++];

	while (j <= right)
		temp[k++] = v[j++];

	for (i = left; i <= right; i++)
		v[i] = temp[i];

	return inv_count;
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
