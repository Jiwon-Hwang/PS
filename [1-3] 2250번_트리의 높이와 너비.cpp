#include <iostream>
#include <algorithm>

using namespace std;

pair<int, int> nodes[10001]; //1<=N<=10000, 입력받는 배열. 인덱스 1부터 시작
bool grid[10002][10002] = {false, }; //전체 노드들(격자) 그려 넣을 배열
int max_level = 1;
int x = 1; //x의 인덱스가 1부터 시작하므로 1로 초기화


//grid에 노드 채우기 : 중위순회, dfs 
void dfs(int node_num, int level) {
	if (nodes[node_num].first != -1) {
		max_level = level+1 > max_level ? level+1 : max_level; //최종 레벨 갱신
		dfs(nodes[node_num].first, level + 1);
	}
	grid[level][x] = true; //격자에 노드 그려 넣기, ***인덱스 순서 주의***
	x++; //x는 true로 격자에 노드 그릴때마다 하나씩 증가.(한 열에 한 노드만 존재 가능하므로)
	if (nodes[node_num].second != -1) {
		max_level = level+1 > max_level ? level+1 : max_level; //최종 레벨 갱신
		dfs(nodes[node_num].second, level + 1);
	}
}


int main() {
	int N = 0;
	scanf_s("%d", &N);

	//pair로 각 parent 노드들 입력받기 & count수 세기
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


	//루트노드의 번호 구하기 : 한번만 입력된 번호의 노드(count == 1)
	int root_idx;
	for (int i = 1; i <= N; i++) {
		if (count[i] == 1) {
			root_idx = i;
			break;
		}
	}


	//중위순회(LVR) 반복하여 모든 노드의 (x,y)값 구하기 => 그리드(트리) 완성
	dfs(root_idx, 1);

	
	//각 레벨의 너비들 중 최대 너비와 해당 레벨값 구하기
	int level;
	int max_breadth = 0;
	int breadth;
	int min_x; 
	int max_x;

	for (int Y = 1; Y <= max_level; Y++) { //***루트노드가 자식 한개밖에 없을 때도 고려!! 2부터가 아니라 1부터!***
		min_x = 0; //초기 : false, 행마다 초기화
		max_x = 1;
		for (int X = 1; X <= N; X++) {
			if (grid[Y][X] == true) {
				if (min_x == 0) {
					min_x = X; // 처음 한번만(min_x 발견 시)
				}
				max_x = X > max_x ? X : max_x;
			}
		}
		breadth = max_x - min_x + 1;
		if (breadth > max_breadth) { //너비 같아도 갱신 안됨
			max_breadth = breadth;
			level = Y;
		}
	}

	printf("%d %d \n", level, max_breadth);
	
	
	//printf("%d", grid[4][2]); // grid에 잘 들어갔는지 확인

	system("pause");

	return 0;
}