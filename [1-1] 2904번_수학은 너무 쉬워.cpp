#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

bool isPrime(int n) {
	for (int i = 2; i < n; i++) {
		if (n%i == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	int prime_fact_list[101][2000] = { 0, };
	int prime_list[2000] = { 0, };

	//n과 n개의 숫자 입력받아서 배열에 저장, 그 중 max값 구하기
	int n = 0;
	scanf("%d",&n);
	int max_val = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &prime_fact_list[i][0]);
		max_val = prime_fact_list[i][0] > max_val ? prime_fact_list[i][0] : max_val;
	}


	//소수 판별 후 소수 리스트에 저장 => 여기에서 시간제한..?ㅠ
	//***주의*** ex) max_val=908963이면 2x2x2x113621인데, 만약 루트씌워버리면 최대 1000까지밖에 prime_list에 안들어감!!!
	//***나올 수 있는 개수가 1000x2=2000개(ex)14=2x7에서, 각 2개씩 쌍으로 나오므로) 이하라고, 소인수 값이 1000 안넘는다는 말은 아니다!!!***
	//int max_sqrt = sqrt(max_val); => 잘못된 생각!
	int length = 0;
	for (int i = 2; i < max_val; i++) {
		if (isPrime(i)) {
			prime_list[length++] = i; // 최종 length : 가능한 소수 전체 개수
		}
	}
	//printf("%d \n",prime_list[length-1]); //=> 가능한 가장 큰 소수 출력(ok)
		
	
	//소인수분해하고 개수들 저장
	for (int i = 0; i < n; i++) {
		int quotient = prime_fact_list[i][0];
		for (int j = 0; j<length; j++) {
			int count = 0; 
			
			// 몫 == 소수 이면 1 채워주고 다음 num으로
			if (quotient == prime_list[j]) {
				prime_fact_list[i][j+1] = ++count;
				break;
			}

			while ((quotient % prime_list[j]) == 0) {
				quotient /= prime_list[j];
				count++;
			}
			prime_fact_list[i][j+1] = count;

			/*sol2)
			int count = 0;
			while (quotient % prime_list[j] == 0) {
			count++;
			quotient /= prime_list[j];
			}

			prime_fact_list[i][j + 1] = count;
			*/
		}
	}

	/*
	for (int i = 1; i < 2001; i++) {
		if (prime_fact_list[0][i] != 0) {
			printf("%d %d \n", prime_fact_list[0][i], prime_list[i-1]);
		}
	}
	*/
	
	//(sum/n) : 배열의 마지막 행에 각 (소인수들 총개수/n) 저장, ***0열아니고 1열부터 채우기!***
	for (int i = 1; i < length+1; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			sum += prime_fact_list[j][i];
		}
		prime_fact_list[n][i] = sum/n; 
	}

	//최대공약수 구하기
	int result1 = 1;
	for (int i = 1; i < length+1; i++) {
		// 각 숫자가 최소 1개씩 인수로 갖고 있어야하므로, 평균 0개인건 제외 (사전에 쓰레기값 대신 배열 ***0으로 초기화*** 시켜둬야함)
		if (prime_fact_list[n][i] >= 1) { 
			result1 *= pow(prime_list[i-1], prime_fact_list[n][i]);
		}
	}

	//연산 횟수 구하기 : 차이 구하기(뺄셈 후 음수값들만 누적)
	int result2 = 0;
	for (int i = 1; i < length+1; i++) {
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
	
	system("pause"); //setting issue. 나중에 지우기
	return 0;
}