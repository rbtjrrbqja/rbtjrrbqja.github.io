// 2020-02-08
// ��������Ʈ�� �̿��� �׷��� (DAG)
// ��������
// �˰��� �����ذ� ���� P829

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
	cout << "������ ���� N �Է� (0 ~ N - 1): "; cin >> N;
	adj.resize(N);
	cout << "������ ���� V �Է�: "; cin >> V;

	for (int i = 0; i < 9; i++)
	{
		cout << "������ ����(a)�� ��(b) ���� ��ȣ �Է�: ";
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