#include <iostream>
using namespace std;

int arr[300] = {0,};
int groups_marble_num[300] = {0,}; // 각 그룹의 구슬 개수들
int group_idx = 0; // 총 그룹 개수

void count_marble_num(int num, int n, int m) {
	int sum = 0;
	for (int i = 0; i < n; i++) {       
		if (sum + arr[i] <= num) { // 담을 수 있으면
			sum += arr[i]; // 담기
			groups_marble_num[group_idx]++; 
			//printf("새로 더한 구슬 값 arr[i] : %d, ", arr[i]);
			//printf("groups_marble_num : %d\n", groups_marble_num[group_idx]);
			continue;
		}
		groups_marble_num[++group_idx]++; // 다음 그룹으로 넘어가면서 개수 1개 추가
		//printf("group_idx : %d, groups_marble_num : %d\n", group_idx, groups_marble_num[group_idx]);
		sum = arr[i]; // 9
	}

	// ***예외처리 부분*** : m개의 그룹보다 덜 쪼개졌을 때, m개 꼭 맞춰서 다시 더 쪼개주기!!
	int idx = group_idx;
	for (int i = 0; m - (idx + 1) - i > 0; i++) {
		for (int j = 0; j <= idx; j++) {
			if (groups_marble_num[idx - j] == 1) { // 그룹의 구슬 개수가 1개면 넘어가기(뒤부터 확인)
				continue;
			} 
			else { // 2개 이상이면 더 쪼개주기 ==> ***결국 각 그룹의 합이 아닌, '개수'만 구하면 됨!!***				
				groups_marble_num[idx - j]--;
				groups_marble_num[++group_idx] = 1;
				break; // 한 번 쪼개고 나서 바깥 for문 확인(m개의 그룹이 됐는지 확인)
			}
		}
		
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