#include "../VIMath.h"
int VIMath::combination(int n, int m) {
	int ret = 1;
	for (int i = 0; i < m; i++) {
		ret *= (n - i);
	}
	for (int i = 0; i < m; i++) {
		ret /= (m - i);
	}
	return ret;
}

int VIMath::permutation(int n, int m) {
	int ret = 1;
	for (int i = 0; i < m; i++) {
		ret *= (n - i);
	}
	return ret;
}