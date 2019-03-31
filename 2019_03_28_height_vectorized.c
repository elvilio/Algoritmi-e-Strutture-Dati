#include <stdio.h>
#include <stdlib.h>

int get_int();
int height(int (*x)[3], int start);
int max(int x, int y);

int main() {
	int n=0;
	n = get_int();
	int x[n][3];
	int start = get_int();
	int i=0;
	while (i++<n){
		x[i][0] = get_int();
		x[i][1] = get_int();
		x[i][2] = get_int();
	}
	printf("%d\n", height(x,start));
	return 0;
}

int height(int (*x)[3], int start){
	int dx = x[start+1][1];
	int sx = x[start+1][2];

	if (dx!=-1 && sx!= -1){
		return 1+max(height(x, dx), height(x, sx));
	}
	else if (dx != -1){
		return 1+height(x, dx);
	}
	else if (sx != -1){
		return 1+height(x, sx);
	}
	else {
		return 0;
	}
}

int max(int x, int y){
	return (x<y)? y: x;
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