#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
/*참조 호출을 하기 위해서는 &주소 연산자를 써야 함
-> 참고) 단순히 배열의 값만 호출할 경우에는 주소 연산자를 붙이지 않아도 됨 다만 배열에다 원소를 추가하거니 기존에 있던 vector의 내용을 변경해야 한다면 주소를 호출하는 것이 맞음
&연산자를 빼면 에라토스 테네스의 체 함수를 호출하더라도 prime_list배열에 소수가 들어오지 않고 초기화한 0으로만 되어 있음*/
int eratosChe(vector<int> &prime_list, int num);
/*벡터 자료구조는 <vector>라는 헤더파일을 선언해야함*/
int main() {
	//n과 n개의 숫자 입력받아서 배열에 저장, 그 중 max값 구하기
	int n = 0;
	scanf("%d", &n);
	int max_val = 0;
	/*메모리 초과를 고려해 n행 1000000만큼 동적 할당
	2차원 벡터의 자료구조는 이렇게 선언함. 동적 할당이 가능한 자료구조 인터넷에 2차원 배열 선언방법 치면 대충 어떻게 선언하는지 나와 있으니 참고*/
	vector<vector<int>>prime_fact_list(n + 1, vector<int>(100000, 0));
	for (int i = 0; i < n; i++) {
		scanf("%d", &prime_fact_list[i][0]);
		max_val = prime_fact_list[i][0] > max_val ? prime_fact_list[i][0] : max_val;
	}
	/*메모리 초과를 고려해 max_val 만큼만 동적할당 - 1차원 배열 자료구조 할당법*/
	vector<int> prime_list(max_val);

	/*
	eratosChe함수로 리턴 -> 참조 호출이라고 하더라고 어차피 배열의 주소를 보내기 때문에 따로 &연산을 사용하지 않고 보내도 무관
	함수 매개변수에 &만 붙이면 알아서 해당 배열의 주소만 호출하니깐 선언할때와 호출할 때를 구별
	선언 - &연산자 사용  호출 - &연산 사용 X
	*/

	int length = eratosChe(prime_list, max_val);
	//소인수분해하고 개수들 저장
	for (int i = 0; i < n; i++) {
		int quotient = prime_fact_list[i][0];
		for (int j = 0; j<length; j++) {
			int count = 0;

			// 몫 == 소수 이면 1 채워주고 다음 num으로
			if (quotient == prime_list[j]) {
				prime_fact_list[i][j + 1] = ++count;
				break;
			}
			while ((quotient % prime_list[j]) == 0) {
				quotient /= prime_list[j];
				count++;
			}
			prime_fact_list[i][j + 1] = count;
		}
	}


	//(sum/n) : 배열의 마지막 행에 각 (소인수들 총개수/n) 저장, ***0열아니고 1열부터 채우기!***
	for (int i = 1; i < length + 1; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			sum += prime_fact_list[j][i];
		}
		prime_fact_list[n][i] = sum / n;
	}
	//최대공약수 구하기
	int result1 = 1;
	for (int i = 1; i < length + 1; i++) {
		// 각 숫자:가 최소 1개씩 인수로 갖고 있어야하므로, 평균 0개인건 제외 (사전에 쓰레기값 대신 배열 ***0으로 초기화*** 시켜둬야함)
		if (prime_fact_list[n][i] >= 1) {
			result1 *= pow(prime_list[i - 1], prime_fact_list[n][i]);
		}
	}
	//연산 횟수 구하기 : 차이 구하기(뺄셈 후 음수값들만 누적)
	int result2 = 0;
	for (int i = 1; i < length + 1; i++) {
		for (int j = 0; j < n; j++) {
			int sub = 0;
			sub = prime_fact_list[j][i] - prime_fact_list[n][i];
			if (sub < 0) {
				result2 += sub;
			}
		}
	}


	//최종 출력
	printf("%d %d \n", result1, -result2);

	return 0;
}

int eratosChe(vector<int> &prime_list, int num) {
	int length = 0;
	/*temp배열은 에라토스 테네스를 임시로 사용하고 num으로 들어온 수가 아마 max_value가 들어옴
	그렇기 때문에 max_value까지의 수까지의 소수를 구하는 것.
	즉, temp_list는 에라토스 테네스의 체를 사용하여 소수인 것만 prime_list에 할당하는 것임.*/
	vector<int> temp_list(num);
	// 입력받은 수 만큼 배열에 모두 초기화 해둔다
	for (int i = 2; i <= num; i++) {
		temp_list[i] = i;
	}

	/*제곱근 만큼만 확인하면 제곱근 보다 큰 소인수는 확인할 수 없게 되어서 이부분에서 sqrt함수를 사용한 부분을 지웠음*/
	for (int i = 2; i <= num; i++) {  //제곱근만큼만 확인해주면 됨.뒤에는 이미 0 되어있을건 되어있음.
		if (temp_list[i] == 0) { // 이미 체크된 수의 배수는 확인하지 않는다
								 /*소수를 체크하는 것을 temp_list 벡터로 사용*/
			continue;
		}
		/*temp 배열에서 걸러지지 않는 소수만 prime_list에 담고 length를 증가시킴*/
		prime_list[length++] = i;

		for (int j = i + i; j <= num; j += i) { // i를 제외한 i의 배수들은 0으로 체크.
			temp_list[j] = 0;
		}

	}

	/*메모리 문제가 발생해서 메모리를 다시 회수하는 코드 temp_list의 시작부터 끝까지 메모리를 회수하는 코드*/
	temp_list.erase(temp_list.begin(), temp_list.end());
	return length;/*prime_list의 길이를 담을 때 마다 증가시켰으므로 length를 그대로 리턴하게 되면 prime_list배열의 크기 만큼 리턴하게 됨*/
}