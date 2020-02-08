// 2020-02-08
// 인접리스트를 이용한 그래프 (DAG)
// 위상정렬
// 알고리즘 문제해결 전략 P829

#include <iostream>
#include <vector>
#include <list>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> order;

void dfs(int here)
{
	cout << "DFS visits " << here + 1 << endl;
	visited[here] = true;

	for (int i = 0; i < adj[here].size(); i++)
	{
		int there = adj[here][i];

		if (!visited[there])
			dfs(there);
	}

	order.push_back(here + 1);
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
	cout << "정점의 개수 N 입력 (0 ~ N - 1): "; cin >> N;
	adj.resize(N);
	cout << "간선의 개수 V 입력: "; cin >> V;

	for (int i = 0; i < 9; i++)
	{
		cout << "간선의 시작(a)과 끝(b) 정점 번호 입력: ";
		int a, b; cin >> a >> b;
		adj[a - 1].push_back(b - 1);
	}

	dfsAll();

	reverse(order.begin(), order.end());

	for (int i = 0; i < order.size(); i++)
		cout << order[i] << " ";
	cout << endl;

	return 0;
}

/*
10
11
6 7
7 1
1 2
2 3
3 4
4 5
6 8
8 2
6 9
9 4
10 3
*/