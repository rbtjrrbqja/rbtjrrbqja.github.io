#include <iostream>
#include <algorithm>
#include <memory.h>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> Pair;

const int MAXINT = 987654321;

class Graph
{
private:
	int vertaxSize;
	int edgeSize;
	int** edge;

public:
	Graph()
	{
		int inputVertaxSize;
		cout << "노드의 개수를 입력해 주세요 :"; cin >> inputVertaxSize;
		vertaxSize = inputVertaxSize;

		edge = new int* [vertaxSize];

		for (int i = 0; i < vertaxSize; i++)
			edge[i] = new int[vertaxSize];

		for (int i = 0; i < vertaxSize; i++)
			for (int j = 0; j < vertaxSize; j++)
				edge[i][j] = 0;

		int inputEdgeSize;
		cout << "간선의 개수를 입력해 주세요 :"; cin >> inputEdgeSize;
		edgeSize = inputEdgeSize;

		for (int i = 0; i < edgeSize; i++)
		{
			int s, e, w;
			cout << "간선의 정보를 입력해 주세요 :";
			cin >> s >> e >> w;

			edge[s][e] = edge[e][s] = w;
		}
	}

	void Dijkstra(int startVertax)
	{
		// U, T, F
		char* status = new char[vertaxSize];
		int* dist = new int[vertaxSize];

		for (int i = 0; i < vertaxSize; i++)
		{
			status[i] = 'U';
			dist[i] = MAXINT;
		}

		priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

		pq.push({ 0, startVertax });
		dist[startVertax] = 0;

		while (!pq.empty())
		{
			int currentVertax = pq.top().second;
			int currentWeight = pq.top().first;

			status[currentVertax] = 'T';

			pq.pop();

			for (int i = 0; i < vertaxSize; i++)
			{
				if (edge[i][currentVertax] != 0)
				{
					if (status[i] == 'U')
					{
						pq.push({ edge[i][currentVertax] + currentWeight, i });
						status[i] = 'F';
					}

					if (status[i] == 'F')
						dist[i] = min(dist[i], currentWeight + edge[i][currentVertax]);
				}
			}
		}

		for (int i = 0; i < vertaxSize; i++)
			cout << dist[i] << " ";
	}
};

int main()
{
	Graph g;
	g.Dijkstra(0);

	return 0;
}

// sample input
/*
9
15
0 1 2
0 5 9
0 6 5
1 2 4
1 6 6
2 3 2
2 7 5
3 4 1
3 7 1
4 5 6
4 8 3
5 8 1
6 7 5
6 8 2
7 8 4
*/