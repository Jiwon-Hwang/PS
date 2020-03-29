#include <iostream>
using namespace std;

int arr[300] = {0,};
int groups_marble_num[300] = {0,}; // �� �׷��� ���� ������
int group_idx = 0; // �� �׷� ����
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

// M���� ���� �� �ִ°�?(count���� �׷��m ��)
// �����ϸ�? => �� ���� �ִ밪 ���ϰ� �Ǵ��ϱ� + �׷� �� �ִ밪���� mid ����
// �Ұ����ϸ�? => �� ū �ִ밪 ���ϰ� �Ǵ��ϱ�
bool isPossible(int mid, int n, int m) { 
	int count = 0; // ������ Ƚ�� (m-1�� ��)
	int rest = mid; // ���� ���� ������
	for (int i = 0; i < n; i++) {
		if (rest - arr[i] < 0) {
			count++; // �׷� ������, ***������ ������ �� �ʿ� x!! ���ο� ������ �����ϱ� continue!!***
			rest = mid;
			rest -= arr[i];
			continue; // �� ���� ��쿡��, ���⿡�� ���� �� �ٽ� �������Ƿ� �ؿ��� ���� ���ϵ��� continue
			//int x = mid - (rest + arr[i]);
			//group_max = group_max > x ? group_max : x;
		}
		// �� �� ������ ���� (rest = arr[i] ����)
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