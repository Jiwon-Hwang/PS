#include <iostream>
#include <vector>

using namespace std;

vector<int> arr(100000, 0);

bool isPossible(int mid, int m, int n) {
	int count = 1;
	int k = mid;

	for (int i = 0; i < n; i++) {
		/*
		if (k >= arr[i]) {
		k -= arr[i];
		}
		else {
		k = mid;
		k -= arr[i];
		count++;
		}
		*/
		if (k < arr[i]) {
			k = mid;
			count++;
		}
		k -= arr[i];
	}

	if (count <= m) {
		return true;
	}
	else {
		return false;
	}
}

int binary_search(int min, int max, int m, int n) {
	int mid = (min + max) / 2;
	if (min == max) {
		return min;
	}
	else if (isPossible(mid, m, n)) {
		return binary_search(min, mid, m, n);
	}
	else {
		return binary_search(mid + 1, max, m, n);
	}
}

int main()
{
	int n, m;
	int min = 1, max = 0;
	int answer;
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; i++) {
		int num;
		scanf("%d", &num);
		max += num;
		arr[i] = num;
		min = min > num ? min : num;
	}

	answer = binary_search(min, max, m, n);
	printf("%d\n", answer);
	return 0;
}