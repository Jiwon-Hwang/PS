#include <iostream>
#include <algorithm>

using namespace std;

pair<int, int> nodes[10001]; //1<=N<=10000, �Է¹޴� �迭. �ε��� 1���� ����
bool grid[10002][10002] = {false, }; //��ü ����(����) �׷� ���� �迭
int max_level = 1;
int x = 1; //x�� �ε����� 1���� �����ϹǷ� 1�� �ʱ�ȭ


//grid�� ��� ä��� : ������ȸ, dfs 
void dfs(int node_num, int level) {
	if (nodes[node_num].first != -1) {
		max_level = level+1 > max_level ? level+1 : max_level; //���� ���� ����
		dfs(nodes[node_num].first, level + 1);
	}
	grid[level][x] = true; //���ڿ� ��� �׷� �ֱ�, ***�ε��� ���� ����***
	x++; //x�� true�� ���ڿ� ��� �׸������� �ϳ��� ����.(�� ���� �� ��常 ���� �����ϹǷ�)
	if (nodes[node_num].second != -1) {
		max_level = level+1 > max_level ? level+1 : max_level; //���� ���� ����
		dfs(nodes[node_num].second, level + 1);
	}
}


int main() {
	int N = 0;
	scanf_s("%d", &N);

	//pair�� �� parent ���� �Է¹ޱ� & count�� ����
	int parent, lchild, rchild;
	int count[10000] = {0, };

	for (int i = 0; i < N; i++) {
		scanf_s("%d %d %d", &parent, &lchild, &rchild);
		count[parent]++;

		nodes[parent].first = lchild;
		if (lchild != -1) {
			count[lchild]++;
		}
		nodes[parent].second = rchild;
		if (rchild != -1) {
			count[rchild]++;
		}
	}


	//��Ʈ����� ��ȣ ���ϱ� : �ѹ��� �Էµ� ��ȣ�� ���(count == 1)
	int root_idx;
	for (int i = 1; i <= N; i++) {
		if (count[i] == 1) {
			root_idx = i;
			break;
		}
	}


	//������ȸ(LVR) �ݺ��Ͽ� ��� ����� (x,y)�� ���ϱ� => �׸���(Ʈ��) �ϼ�
	dfs(root_idx, 1);

	
	//�� ������ �ʺ�� �� �ִ� �ʺ�� �ش� ������ ���ϱ�
	int level;
	int max_breadth = 0;
	int breadth;
	int min_x; 
	int max_x;

	for (int Y = 1; Y <= max_level; Y++) { //***��Ʈ��尡 �ڽ� �Ѱ��ۿ� ���� ���� ���!! 2���Ͱ� �ƴ϶� 1����!***
		min_x = 0; //�ʱ� : false, �ึ�� �ʱ�ȭ
		max_x = 1;
		for (int X = 1; X <= N; X++) {
			if (grid[Y][X] == true) {
				if (min_x == 0) {
					min_x = X; // ó�� �ѹ���(min_x �߰� ��)
				}
				max_x = X > max_x ? X : max_x;
			}
		}
		breadth = max_x - min_x + 1;
		if (breadth > max_breadth) { //�ʺ� ���Ƶ� ���� �ȵ�
			max_breadth = breadth;
			level = Y;
		}
	}

	printf("%d %d \n", level, max_breadth);
	
	
	//printf("%d", grid[4][2]); // grid�� �� ������ Ȯ��

	system("pause");

	return 0;
}