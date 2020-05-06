#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;

struct edge
{
	int start;
	int end;
	int weight;
};

struct cmp {
	bool operator()(edge a, edge b)
	{
		return a.weight > b.weight;
	}
};

int T, N, parent[1001], treeSize[1001];
int price, commission;

int FindRoot(int u)
{
	if (parent[u] == u)
		return u;
	else
		return FindRoot(parent[u]);
}

void UpdateRoot(int u, int v)
{
	if (treeSize[u] < treeSize[v])
	{
		parent[u] = v;
		treeSize[v] += treeSize[u];
	}
	else
	{
		parent[v] = u;
		treeSize[u] += treeSize[v];
	}
}

int func(priority_queue<edge, vector<edge>, cmp>& edgeList)
{
	int subPrice = 0;

	while (!edgeList.empty())
	{
		edge current = edgeList.top();
		edgeList.pop();

		int startN = FindRoot(current.start);
		int endN = FindRoot(current.end);

		if (startN == endN)
			continue;

		UpdateRoot(startN, endN);
		subPrice += current.weight;
	}

	return subPrice;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> T;

	while (T--)
	{
		cin >> N;
		priority_queue<edge, vector<edge>, cmp> edgeList;

		for (int i = 0; i <= N; i++)
		{
			parent[i] = i;
			treeSize[i] = 1;
		}

		int sum = 0;

		for (int i = 1; i <= N; i++)
		{
			cin >> price >> commission;

			edgeList.push(edge{0, i, price});
			
			if (i != 1)
				edgeList.push(edge{i - 1, i, commission});

			sum += price;
		}

		cout << sum + func(edgeList) << endl;
	}

	return 0;
}