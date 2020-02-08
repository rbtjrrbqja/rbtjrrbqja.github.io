// 2020-02-08
// 인접리스트를 이용한 그래프 (양방향)
// 깊이 우선 탐색
// 알고리즘 문제해결 전략 P827

#include <iostream>
#include <vector>
#include <list>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void dfs(int here)
{
	cout << "DFS visits " << here << endl;
	visited[here] = true;

	for (int i = 0; i < adj[here].size(); i++)
	{
		int there = adj[here][i];

		if (!visited[there])
			dfs(there);
	}
}

void dfsAll()
{
	visited = vector<bool>(adj.size(), false);

	for (int i = 0; i < adj.size(); i++)
		if (!visited[i])
			dfs(i);
}

int main()
{
	int N, V;
	cout << "정점의 개수 N 입력 (0 ~ N-1): "; cin >> N;
	adj.resize(N);
	cout << "간선의 개수 V 입력: "; cin >> V;

	for (int i = 0; i < 9; i++)
	{
		cout << "간선의 시작(a)과 끝(b) 정점 번호 입력: ";
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfsAll();

	return 0;
}

/*
10
9
0 1
0 2
2 3
2 4
2 5
5 6
1 7
7 8
7 9
*/