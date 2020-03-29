#include <iostream>
using namespace std;

int arr[300] = {0,};
int groups_marble_num[300] = {0,}; // �� �׷��� ���� ������
int group_idx = 0; // �� �׷� ����

void count_marble_num(int num, int n, int m) {
	int sum = 0;
	for (int i = 0; i < n; i++) {       
		if (sum + arr[i] <= num) { // ���� �� ������
			sum += arr[i]; // ���
			groups_marble_num[group_idx]++; 
			//printf("���� ���� ���� �� arr[i] : %d, ", arr[i]);
			//printf("groups_marble_num : %d\n", groups_marble_num[group_idx]);
			continue;
		}
		groups_marble_num[++group_idx]++; // ���� �׷����� �Ѿ�鼭 ���� 1�� �߰�
		//printf("group_idx : %d, groups_marble_num : %d\n", group_idx, groups_marble_num[group_idx]);
		sum = arr[i]; // 9
	}

	// ***����ó�� �κ�*** : m���� �׷캸�� �� �ɰ����� ��, m�� �� ���缭 �ٽ� �� �ɰ��ֱ�!!
	int idx = group_idx;
	for (int i = 0; m - (idx + 1) - i > 0; i++) {
		for (int j = 0; j <= idx; j++) {
			if (groups_marble_num[idx - j] == 1) { // �׷��� ���� ������ 1���� �Ѿ��(�ں��� Ȯ��)
				continue;
			} 
			else { // 2�� �̻��̸� �� �ɰ��ֱ� ==> ***�ᱹ �� �׷��� ���� �ƴ�, '����'�� ���ϸ� ��!!***				
				groups_marble_num[idx - j]--;
				groups_marble_num[++group_idx] = 1;
				break; // �� �� �ɰ��� ���� �ٱ� for�� Ȯ��(m���� �׷��� �ƴ��� Ȯ��)
			}
		}
		
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
	printf("%d \n", result);
	for (int i = 0; i <= group_idx; i++) {
		printf("%d ", groups_marble_num[i]);
	}

	system("pause");

	return 0;
}