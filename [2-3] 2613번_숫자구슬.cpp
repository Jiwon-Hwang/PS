#include <iostream>
using namespace std;

int arr[300] = {0,};
int groups_marble_num[300] = {0,}; // 각 그룹의 구슬 개수들
int group_idx = 0; // 총 그룹 개수
//int group_max = 0;

void count_marble_num(int num, int n, int m) {
	int rest = num;
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (rest - arr[i] < 0) {
			rest = num;
			rest -= arr[i];
			groups_marble_num[group_idx++] = j;
			j = 1;
			continue;
		}
		rest -= arr[i];
		j++;
	}
}

// M개로 나눌 수 있는가?(count수와 그룹수m 비교)
// 가능하면? => 더 작은 최대값 구하고 판단하기 + 그룹 중 최대값으로 mid 갱신
// 불가능하면? => 더 큰 최대값 구하고 판단하기
bool isPossible(int mid, int n, int m) { 
	int count = 0; // 나누는 횟수 (m-1과 비교)
	int rest = mid; // 빼고 남은 나머지
	for (int i = 0; i < n; i++) {
		if (rest - arr[i] < 0) {
			count++; // 그룹 나누기, ***나누고 나서는 뺄 필요 x!! 새로운 값으로 ㄱㄱ니까 continue!!***
			rest = mid;
			rest -= arr[i];
			continue; // 못 빼는 경우에도, 여기에서 충전 후 다시 빼줬으므로 밑에는 실행 안하도록 continue
			//int x = mid - (rest + arr[i]);
			//group_max = group_max > x ? group_max : x;
		}
		// 뺄 수 있으면 빼기 (rest = arr[i] 여도)
		rest -= arr[i]; 
	}
	
	if (count <= m - 1) {
		return true;
	}
	else {
		return false;
	}
}

int binary_search(int min, int max, int n, int m) {
	if (min == max) {
		count_marble_num(min, n, m);
		return min;
	}
	else {
		int mid = (min + max) / 2;

		if (isPossible(mid, n, m)) {
			//mid = group_max;
			return binary_search(min, mid, n, m);
		}
		else {
			return binary_search(mid + 1, max, n, m);
		}
	}
}

int main() {
	int n, m; // 1 <= m <= n <= 300
	int min = 1;
	int max = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		min = min > arr[i] ? min : arr[i];
		max += arr[i];
	}
	
	int result = binary_search(min, max, n, m);
	printf("%d\n", result);
	for (int i = 0; i <= group_idx; i++) {
		printf("%d ", groups_marble_num[i]);
	}

	system("pause");

	return 0;
}