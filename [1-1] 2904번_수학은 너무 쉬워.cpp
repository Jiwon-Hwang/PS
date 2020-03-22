#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
/*���� ȣ���� �ϱ� ���ؼ��� &�ּ� �����ڸ� ��� ��
-> ����) �ܼ��� �迭�� ���� ȣ���� ��쿡�� �ּ� �����ڸ� ������ �ʾƵ� �� �ٸ� �迭���� ���Ҹ� �߰��ϰŴ� ������ �ִ� vector�� ������ �����ؾ� �Ѵٸ� �ּҸ� ȣ���ϴ� ���� ����
&�����ڸ� ���� �����佺 �׳׽��� ü �Լ��� ȣ���ϴ��� prime_list�迭�� �Ҽ��� ������ �ʰ� �ʱ�ȭ�� 0���θ� �Ǿ� ����*/
int eratosChe(vector<int> &prime_list, int num);
/*���� �ڷᱸ���� <vector>��� ��������� �����ؾ���*/
int main() {
	//n�� n���� ���� �Է¹޾Ƽ� �迭�� ����, �� �� max�� ���ϱ�
	int n = 0;
	scanf("%d", &n);
	int max_val = 0;
	/*�޸� �ʰ��� ����� n�� 1000000��ŭ ���� �Ҵ�
	2���� ������ �ڷᱸ���� �̷��� ������. ���� �Ҵ��� ������ �ڷᱸ�� ���ͳݿ� 2���� �迭 ������ ġ�� ���� ��� �����ϴ��� ���� ������ ����*/
	vector<vector<int>>prime_fact_list(n + 1, vector<int>(100000, 0));
	for (int i = 0; i < n; i++) {
		scanf("%d", &prime_fact_list[i][0]);
		max_val = prime_fact_list[i][0] > max_val ? prime_fact_list[i][0] : max_val;
	}
	/*�޸� �ʰ��� ����� max_val ��ŭ�� �����Ҵ� - 1���� �迭 �ڷᱸ�� �Ҵ��*/
	vector<int> prime_list(max_val);

	/*
	eratosChe�Լ��� ���� -> ���� ȣ���̶�� �ϴ���� ������ �迭�� �ּҸ� ������ ������ ���� &������ ������� �ʰ� ������ ����
	�Լ� �Ű������� &�� ���̸� �˾Ƽ� �ش� �迭�� �ּҸ� ȣ���ϴϱ� �����Ҷ��� ȣ���� ���� ����
	���� - &������ ���  ȣ�� - &���� ��� X
	*/

	int length = eratosChe(prime_list, max_val);
	//���μ������ϰ� ������ ����
	for (int i = 0; i < n; i++) {
		int quotient = prime_fact_list[i][0];
		for (int j = 0; j<length; j++) {
			int count = 0;

			// �� == �Ҽ� �̸� 1 ä���ְ� ���� num����
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


	//(sum/n) : �迭�� ������ �࿡ �� (���μ��� �Ѱ���/n) ����, ***0���ƴϰ� 1������ ä���!***
	for (int i = 1; i < length + 1; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			sum += prime_fact_list[j][i];
		}
		prime_fact_list[n][i] = sum / n;
	}
	//�ִ����� ���ϱ�
	int result1 = 1;
	for (int i = 1; i < length + 1; i++) {
		// �� ����:�� �ּ� 1���� �μ��� ���� �־���ϹǷ�, ��� 0���ΰ� ���� (������ �����Ⱚ ��� �迭 ***0���� �ʱ�ȭ*** ���ѵ־���)
		if (prime_fact_list[n][i] >= 1) {
			result1 *= pow(prime_list[i - 1], prime_fact_list[n][i]);
		}
	}
	//���� Ƚ�� ���ϱ� : ���� ���ϱ�(���� �� �������鸸 ����)
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


	//���� ���
	printf("%d %d \n", result1, -result2);

	return 0;
}

int eratosChe(vector<int> &prime_list, int num) {
	int length = 0;
	/*temp�迭�� �����佺 �׳׽��� �ӽ÷� ����ϰ� num���� ���� ���� �Ƹ� max_value�� ����
	�׷��� ������ max_value������ �������� �Ҽ��� ���ϴ� ��.
	��, temp_list�� �����佺 �׳׽��� ü�� ����Ͽ� �Ҽ��� �͸� prime_list�� �Ҵ��ϴ� ����.*/
	vector<int> temp_list(num);
	// �Է¹��� �� ��ŭ �迭�� ��� �ʱ�ȭ �صд�
	for (int i = 2; i <= num; i++) {
		temp_list[i] = i;
	}

	/*������ ��ŭ�� Ȯ���ϸ� ������ ���� ū ���μ��� Ȯ���� �� ���� �Ǿ �̺κп��� sqrt�Լ��� ����� �κ��� ������*/
	for (int i = 2; i <= num; i++) {  //�����ٸ�ŭ�� Ȯ�����ָ� ��.�ڿ��� �̹� 0 �Ǿ������� �Ǿ�����.
		if (temp_list[i] == 0) { // �̹� üũ�� ���� ����� Ȯ������ �ʴ´�
								 /*�Ҽ��� üũ�ϴ� ���� temp_list ���ͷ� ���*/
			continue;
		}
		/*temp �迭���� �ɷ����� �ʴ� �Ҽ��� prime_list�� ��� length�� ������Ŵ*/
		prime_list[length++] = i;

		for (int j = i + i; j <= num; j += i) { // i�� ������ i�� ������� 0���� üũ.
			temp_list[j] = 0;
		}

	}

	/*�޸� ������ �߻��ؼ� �޸𸮸� �ٽ� ȸ���ϴ� �ڵ� temp_list�� ���ۺ��� ������ �޸𸮸� ȸ���ϴ� �ڵ�*/
	temp_list.erase(temp_list.begin(), temp_list.end());
	return length;/*prime_list�� ���̸� ���� �� ���� �����������Ƿ� length�� �״�� �����ϰ� �Ǹ� prime_list�迭�� ũ�� ��ŭ �����ϰ� ��*/
}