#include <iostream>

using namespace std;

char arr[3072][1644]; //5x1024+(1024-1) 이지만 가장 왼쪽에 한 칸 비워두기. (x좌표를 1부터 시작하기 위해서, 가운데를 n으로 하기 위해서)

void Divide(int n, int x, int y) { //맨 위 꼭지점이 (x,y)인 높이 n인 삼각형 그리기. *입력&출력 따로 만들기

	if (n == 3) { //초기조건, 종료조건 (기본 삼각형 별찍기)
		arr[x][y] = '*';
		arr[x-1][y+1] = '*';
		arr[x + 1][y + 1] = '*';
		for (int i = 0; i < 5; i++) {
			arr[x - 2 + i][y + 2] = '*';
		}

		return; // 강제종료 (if문을 포함하고있는, 호출했던 함수 종료.) 
	}

	int delta = n / 2; //n에 대한 관계식

	Divide(n / 2, x, y); //꼭지점 (x,y)인 높이 n/2인 중앙삼각형 그리기
	Divide(n / 2, x - delta, y + (n / 2)); //꼭지점 (x-delta, y-n/2)인 높이 n/2인 왼쪽 삼각형 그리기
	Divide(n / 2, x + delta, y + (n / 2)); //꼭지점 (x+delta, y+n/2)인 높이 n/2인 오른쪽 삼각형 그리기
	
}


int main() {
	// 행렬을 공백으로 초기화해두기 (cf. {' ', } 이렇게 전체 초기화는 선언과 함께..?)
	for (int i = 0; i < 3072; i++) {
		for (int j = 0; j < 1644; j++) {
			arr[i][j] = ' ';
		}
	}

	int N = 0; //N : 3×2k승 (3, 6, 12, 24, 48, ..., 3x1024) (k ≤ 10)
	scanf_s("%d", &N);

	// 꼭지점의 좌표이자, 배열에서의 인덱스
	int x = N;
	int y = 0;

	// 배열에 별 넣기
	Divide(N, x, y);

	// 별들 출력하기
	for (int i = 0; i < N; i++) {
		for (int j= 1; j < 2*N; j++) {
			printf("%c" ,arr[j][i]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}