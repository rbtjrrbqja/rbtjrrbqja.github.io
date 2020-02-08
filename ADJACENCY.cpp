// 2020-02-08
// ��������Ʈ�� �̿��� �׷��� (�����)
// ���� �켱 Ž��
// �˰��� �����ذ� ���� P827

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
	cout << "������ ���� N �Է� (0 ~ N-1): "; cin >> N;
	adj.resize(N);
	cout << "������ ���� V �Է�: "; cin >> V;

	for (int i = 0; i < 9; i++)
	{
		cout << "������ ����(a)�� ��(b) ���� ��ȣ �Է�: ";
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