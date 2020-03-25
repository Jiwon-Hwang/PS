#include <iostream>
#define MAX_NUM	64
using namespace std;

char grid[MAX_NUM][MAX_NUM];

// ���� ���� : �迭 �� ������ �� ������ �� �� �ϳ� ����ϰ� ��
void quadTree(int x, int y, int n) {
	char start = grid[y][x];
	bool check = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[y+i][x+j] != start) {
				check = false;
				break;
			}
		}
		if (!check) {
			break;
		}
	}

	if (check) { // �� ����
		printf("%c",start);
	}
	else { // �ٸ��� �ִ�
		printf("(");
		quadTree(x, y, n / 2);
		quadTree(x + n / 2, y, n / 2);
		quadTree(x, y + n / 2, n / 2);
		quadTree(x + n / 2 , y + n / 2, n / 2);
		printf(")");
	}
	
}

int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%s", grid[i]);
	}

	quadTree(0, 0, n);
	
	printf("\n");

	system("pause");
	return 0;
}



/*
for (int i = 0; i < n; i++) {
printf("%s\n", test[i]);
}
printf("%c", test[0][0]);
*/