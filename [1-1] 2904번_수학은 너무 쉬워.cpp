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

	//n�� n���� ���� �Է¹޾Ƽ� �迭�� ����, �� �� max�� ���ϱ�
	int n = 0;
	scanf("%d",&n);
	int max_val = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &prime_fact_list[i][0]);
		max_val = prime_fact_list[i][0] > max_val ? prime_fact_list[i][0] : max_val;
	}


	//�Ҽ� �Ǻ� �� �Ҽ� ����Ʈ�� ���� => ���⿡�� �ð�����..?��
	//***����*** ex) max_val=908963�̸� 2x2x2x113621�ε�, ���� ��Ʈ���������� �ִ� 1000�����ۿ� prime_list�� �ȵ�!!!
	//***���� �� �ִ� ������ 1000x2=2000��(ex)14=2x7����, �� 2���� ������ �����Ƿ�) ���϶��, ���μ� ���� 1000 �ȳѴ´ٴ� ���� �ƴϴ�!!!***
	//int max_sqrt = sqrt(max_val); => �߸��� ����!
	int length = 0;
	for (int i = 2; i < max_val; i++) {
		if (isPrime(i)) {
			prime_list[length++] = i; // ���� length : ������ �Ҽ� ��ü ����
		}
	}
	//printf("%d \n",prime_list[length-1]); //=> ������ ���� ū �Ҽ� ���(ok)
		
	
	//���μ������ϰ� ������ ����
	for (int i = 0; i < n; i++) {
		int quotient = prime_fact_list[i][0];
		for (int j = 0; j<length; j++) {
			int count = 0; 
			
			// �� == �Ҽ� �̸� 1 ä���ְ� ���� num����
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
	
	//(sum/n) : �迭�� ������ �࿡ �� (���μ��� �Ѱ���/n) ����, ***0���ƴϰ� 1������ ä���!***
	for (int i = 1; i < length+1; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			sum += prime_fact_list[j][i];
		}
		prime_fact_list[n][i] = sum/n; 
	}

	//�ִ����� ���ϱ�
	int result1 = 1;
	for (int i = 1; i < length+1; i++) {
		// �� ���ڰ� �ּ� 1���� �μ��� ���� �־���ϹǷ�, ��� 0���ΰ� ���� (������ �����Ⱚ ��� �迭 ***0���� �ʱ�ȭ*** ���ѵ־���)
		if (prime_fact_list[n][i] >= 1) { 
			result1 *= pow(prime_list[i-1], prime_fact_list[n][i]);
		}
	}

	//���� Ƚ�� ���ϱ� : ���� ���ϱ�(���� �� �������鸸 ����)
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

	//���� ���
	printf("%d %d \n", result1, -result2);
	
	system("pause"); //setting issue. ���߿� �����
	return 0;
}